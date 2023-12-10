#pragma once
#include "../Utils/hash.hpp"
#include "../Utils/crc32.hpp"
#include "../Utils/lazy.hpp"

extern int sprintf(char* buf, const char* fmt, ...);

extern "C" void* __cdecl memset( void*, int, size_t );
#pragma intrinsic(memset)


#define maxx( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define minm( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#define CIRCLE_AUTO_SEGMENT_MIN 4
#define CIRCLE_AUTO_SEGMENT_MAX 512
#define CIRCLE_AUTO_SEGMENT_MAXERROR 0.3f
#define CLAMP(val, min, max) ((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val))
#define ROUNDUP_TO_EVEN(_V) ((((_V) + 1) / 2) * 2)
#define M_PI 3.14159265358979323846f
#define M_PI_F ((float)(M_PI))
#define DEG2RAD(val) ((float)(val) * (float)(M_PI_F / 180.0f))
#define RAD2DEG(val) ((float)(val) * (float)(180.0f / M_PI_F))

static inline float Max3(float f1, float f2, float f3)
{
    return maxx(maxx(f1, f2), f3);
}

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	int __cdecl _cinit( void );
	void __cdecl _cexit( void );
	void __cdecl _cinitfs( void );

	typedef void( __cdecl* _PVFV )( void );
	typedef int( __cdecl* _PIFV )( void );

	int __cdecl atexit( _PVFV func );

	void  __cdecl free( void* ptr );
	void* __cdecl malloc( size_t size ); // PagedPool

#ifdef __cplusplus
}
#endif // __cplusplus



inline std::size_t crt_wcslen(const wchar_t* const string)
{
	std::size_t length = 0;

	while (string[length] != L'\0')
		length++;

	return length;

}

struct ImageParameters
{
	std::uint64_t m_hash = 0;		// 0x0000
	std::uintptr_t m_base = 0;	// 0x0008
	std::size_t m_size = 0;			// 0x0010
};
// sizeof( ImageParameters ) = 0x0018

struct SectionParameters
{
	std::uint64_t m_hash = 0;		// 0x0000
	std::uint32_t m_base = 0;		// 0x0008
	std::uint32_t m_size = 0;		// 0x000C
};
// sizeof( SectionParameters ) = 0x0010

struct ExportParameters
{
	std::uint64_t m_hash = 0;			// 0x0000
	std::uint16_t m_ordinal = 0;	// 0x0008
	std::uintptr_t m_address = 0;	// 0x0010
};

using OnImageEntryFn = bool(*)(ImageParameters* parameters, LDR_DATA_TABLE_ENTRY* entry);
using OnImageSectionFn = bool(*)(SectionParameters* parameters, IMAGE_SECTION_HEADER* section);
using OnImageExportFn = bool(*)(ExportParameters* parameters, std::uintptr_t address, std::uint16_t ordinal, const char* const name);

inline bool EnumerateImages(OnImageEntryFn enumerate, ImageParameters* parameters /*= nullptr*/)
{
	if ((enumerate))
	{
		const auto peb = NtCurrentPeb();

		if ((peb))
		{
			const auto peb_ldr_data = peb->Ldr;

			if ((peb_ldr_data))
			{
				const auto list_head = &peb_ldr_data->InLoadOrderModuleList;

				for (auto list_entry = list_head->Flink; list_entry != list_head; list_entry = list_entry->Flink)
				{
					const auto entry = CONTAINING_RECORD(list_entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

					if ((entry))
					{
						if (enumerate(parameters, entry))
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

template< typename Type = std::uintptr_t >
inline Type GetImage(std::uint64_t hash, std::size_t size = 0)
{
	auto enumerate = [](ImageParameters* parameters, LDR_DATA_TABLE_ENTRY* entry)
	{
		if ((parameters))
		{
			if (parameters->m_hash)
			{
				const auto& base_name = entry->BaseDllName;

				if (base_name.Length)
				{
					if (Hash(base_name, true) == parameters->m_hash)
					{
						parameters->m_base = (uintptr_t)(entry->DllBase);
						parameters->m_size = static_cast<std::size_t>(entry->SizeOfImage);
						return true;
					}
				}
			}
			else
			{
				parameters->m_base = (uintptr_t)(entry->DllBase);
				parameters->m_size = static_cast<std::size_t>(entry->SizeOfImage);
				return true;
			}
		}

		return false;
	};

	ImageParameters parameters = { };
	parameters.m_hash = hash;

	if (EnumerateImages(enumerate, &parameters))
	{
		(size) = parameters.m_size;

		return Type(parameters.m_base);
	}

	return { };
}

template< typename Type = std::uintptr_t >
inline Type GetImage(const wchar_t* const name, std::size_t size = 0)
{
	std::uint64_t hash = Hash(name, true);


	return GetImage< Type >(hash, size);
}


inline IMAGE_DOS_HEADER* GetImageDosHeader(std::uintptr_t image)
{
	if ((image))
	{
		const auto image_dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(image);

		if (image_dos_header->e_magic == IMAGE_DOS_SIGNATURE)
		{
			return image_dos_header;
		}
	}

	return nullptr;
}

inline IMAGE_NT_HEADERS* GetImageNtHeaders(std::uintptr_t image)
{
	const auto image_dos_header = GetImageDosHeader(image);

	if ((image_dos_header))
	{
		const auto image_nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(image + image_dos_header->e_lfanew);

		if (image_nt_headers->Signature == IMAGE_NT_SIGNATURE)
		{
			return image_nt_headers;
		}
	}

	return nullptr;
}

inline IMAGE_DATA_DIRECTORY* GetImageDataDirectory(std::uintptr_t image, std::uint16_t directory)
{
	if (directory < IMAGE_NUMBEROF_DIRECTORY_ENTRIES)
	{
		const auto image_nt_headers = GetImageNtHeaders(image);

		if ((image_nt_headers))
		{
			return &image_nt_headers->OptionalHeader.DataDirectory[directory];
		}
	}

	return nullptr;
}

template< typename Type = std::uintptr_t >
inline Type GetImageDataDirectory(std::uintptr_t image, std::uint16_t directory, std::size_t* size = nullptr)
{
	const auto image_data_directory = GetImageDataDirectory(image, directory);

	if ((image_data_directory))
	{
		(*size) = static_cast<std::size_t>(image_data_directory->Size);

		return Type(image + image_data_directory->VirtualAddress);
	}

	return { };
}

inline bool EnumerateImageExports(std::uintptr_t image, OnImageExportFn enumerate, ExportParameters* parameters /*= nullptr*/)
{
	if ((enumerate))
	{
		std::size_t image_export_directory_size = 0;
		const auto image_export_directory = GetImageDataDirectory< IMAGE_EXPORT_DIRECTORY* >(image, IMAGE_DIRECTORY_ENTRY_EXPORT,
			&image_export_directory_size);

		if ((image_export_directory))
		{
			if (image_export_directory->AddressOfFunctions &&
				image_export_directory->AddressOfNames &&
				image_export_directory->AddressOfNameOrdinals)
			{
				const auto functions = reinterpret_cast<const std::uint32_t*>(image + image_export_directory->AddressOfFunctions);
				const auto names = reinterpret_cast<const std::uint32_t*>(image + image_export_directory->AddressOfNames);
				const auto ordinals = reinterpret_cast<const std::uint16_t*>(image + image_export_directory->AddressOfNameOrdinals);

				for (std::uint32_t index = 0; index < image_export_directory->NumberOfNames; index++)
				{
					const auto ordinal = ordinals[index];
					const auto displacement = functions[ordinal];

					if (displacement)
					{
						const auto address = (image + displacement);
						const auto name_displacement = names[index];

						if (name_displacement)
						{
							const auto name = reinterpret_cast<const char*>(image + name_displacement);

							if (enumerate(parameters, address, ordinal, name))
							{
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

template< typename Type = std::uintptr_t >
inline Type GetImageExport(std::uintptr_t image, std::uint64_t hash)
{
	auto enumerate = [](ExportParameters* parameters, std::uintptr_t address, std::uint16_t ordinal, const char* const name)
	{
		if ((parameters))
		{
			const auto hash = Hash(name, true);

			if (hash == parameters->m_hash)
			{
				parameters->m_address = address;
				parameters->m_ordinal = ordinal;
				return true;
			}
		}

		return false;
	};

	ExportParameters parameters = { };
	parameters.m_hash = hash;

	if (EnumerateImageExports(image, enumerate, &parameters))
	{
		return Type(parameters.m_address);
	}

	return { };
}

template< typename T, typename... ArgPack >
inline FORCEINLINE T Call(std::uintptr_t address, ArgPack... arg_pack)
{
	using Fn = T(*)(ArgPack...);
	const auto procedure = reinterpret_cast<Fn>(address);

	if (!(procedure))
	{
		return std::invoke_result_t< Fn, ArgPack... >();
	}

	return procedure(arg_pack...);
}

constexpr inline std::uintptr_t MinimumUserAddress = 0x0000000000010000;
constexpr inline std::uintptr_t MaximumUserAddress = 0x00007FFFFFFFFFFF;

inline std::uintptr_t ToAddress(const void* pointer)
{
	return reinterpret_cast<std::uintptr_t>(pointer);
}

inline void* ToPointer(std::uintptr_t address)
{
	return reinterpret_cast<void*>(address);
}

inline bool IsUserAddress(std::uintptr_t address)
{
    return (address >= MinimumUserAddress &&
        address <= MaximumUserAddress &&
        address != 0);
}


inline bool IsAddressValid(std::uintptr_t address)
{
    return IsUserAddress(address);
}

inline bool IsAddressValid(const void* pointer)
{
    const auto address = ToAddress(pointer);
    return IsAddressValid(address);
}

#define IN_RANGE( x, a, b )	( x >= a && x <= b )
#define GET_BITS( x )		( IN_RANGE( x, '0', '9' ) ? ( x - '0' ) : ( ( x & ( ~0x20 ) ) - 'A' + 0x0A ) )
#define GET_BYTE( x )		( GET_BITS( x[ 0 ] ) << 4 | GET_BITS( x[ 1 ] ) )


template< typename Type >
inline constexpr bool IsQuestion(const Type character)
{
    return (character == static_cast<const Type>(63));
}


inline std::uintptr_t ScanRegionInternal(const std::uint8_t* region_begin, const std::uint8_t* region_end, const char* signature)
{
    if (!IsAddressValid(region_begin))
    {
        return 0;
    }

    if (!IsAddressValid(region_end))
    {
        return 0;
    }

    if (!IsAddressValid(signature))
    {
        return 0;
    }

    auto scan_result = static_cast<std::uintptr_t>(0);
    auto scan_compare = reinterpret_cast<const std::uint8_t*>(signature);

    const auto scan_begin = region_begin;
    const auto scan_end = region_end;

    for (auto scan_current = scan_begin; scan_current < scan_end; scan_current++)
    {
        if (IsTerminator(scan_compare[0]))
        {
            return scan_result;
        }

        if (IsAddressValid(const_cast<std::uint8_t*>(scan_current)))
        {
            if (IsQuestion(scan_compare[0]) || scan_current[0] == GET_BYTE(scan_compare))
            {
                if (!IsAddressValid(scan_result))
                {
                    scan_result = ToAddress(scan_current);
                }

                if (IsTerminator(scan_compare[2]))
                {
                    return scan_result;
                }

                const bool question[2] =
                {
                    IsQuestion(scan_compare[0]),
                    IsQuestion(scan_compare[1]),
                };

                if ((question[0] && question[1]) || (!question[0]))
                {
                    scan_compare = (scan_compare + 3);
                }
                else
                {
                    scan_compare = (scan_compare + 2);
                }
            }
            else
            {
                scan_compare = reinterpret_cast<const std::uint8_t*>(signature);
                scan_result = 0;
            }
        }
    }

    return 0;
}


inline std::uintptr_t ScanImageInternal(std::uintptr_t image, const char* signature)
{
    const auto image_nt_headers = GetImageNtHeaders(image);

    if (!IsAddressValid(image_nt_headers))
    {
        return 0;
    }

    const auto region_begin = reinterpret_cast<const std::uint8_t*>(image);
    const auto region_end = reinterpret_cast<const std::uint8_t*>(image + image_nt_headers->OptionalHeader.SizeOfImage);

    return ScanRegionInternal(region_begin, region_end, signature);
}



inline std::uintptr_t GetAbsoluteAddressInternal(std::uintptr_t address, std::size_t opcode_count)
{
    if (!IsAddressValid(address))
    {
        return 0;
    }

    const auto disp = *reinterpret_cast<std::int32_t*>(address + opcode_count);

    if (disp == 0)
    {
        return 0;
    }

    return (address + opcode_count + disp + sizeof(disp));
}
template< typename Type = std::uintptr_t >
FORCEINLINE Type ScanImage(std::uintptr_t image, const char* signature)
{
    return Type(ScanImageInternal(image, signature));
}
inline unsigned short lfsr = 0xACE1u;
inline unsigned int bit = 0;

inline unsigned my_rand()
{
	if (!lfsr) {
		lfsr = 0xACE1u; bit = 0;
	}
	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}

typedef struct _KSYSTEM_TIME {
    unsigned long LowPart;
    long High1Time;
    long High2Time;
} KSYSTEM_TIME, * PKSYSTEM_TIME;

typedef struct _KUSER_SHARED_DATA {
    unsigned long TickCountLowDeprecated;
    unsigned long TickCountMultiplier;

    volatile KSYSTEM_TIME InterruptTime;
    volatile KSYSTEM_TIME SystemTime;
    volatile KSYSTEM_TIME TimeZoneBias;
} KUSER_SHARED_DATA, * PKUSER_SHARED_DATA;

inline float system_time() {
    LARGE_INTEGER systime;
    auto& usrhd_systemtime = ((KUSER_SHARED_DATA*)(0x7ffe0000))->SystemTime;

    do {
        systime.HighPart = usrhd_systemtime.High1Time;
        systime.LowPart = usrhd_systemtime.LowPart;
    } while (systime.HighPart != usrhd_systemtime.High2Time);

    constexpr auto MSPERSEC = 1000ll;
    constexpr auto SECSPERDAY = 86400ll;
    constexpr auto TICKSPERSEC = 10000000ll;
    constexpr auto TICKSPERMSEC = 10000ll;

    auto ms_sincestart = systime.QuadPart / TICKSPERMSEC;
    auto weekly_time = ms_sincestart % (SECSPERDAY * MSPERSEC * 7);
    return weekly_time / 1000.f;
}


namespace crt {
    __forceinline const void* memchr(const void* src, int chr, size_t len) {
        auto _src = static_cast<const unsigned char*>(src);

        while (len-- > 0) {
            if (*_src == chr) {
                return static_cast<const void*>(_src);
            }

            _src++;
        }

        return 0;
    }

    __forceinline int memcmp(const void* buf1, const void* buf2, size_t len) {
        auto char_buf1 = static_cast<const unsigned char*>(buf1);
        auto char_buf2 = static_cast<const unsigned char*>(buf2);

        for (size_t i = 0; i < len; i++) {
            if (char_buf1[i] < char_buf2[i]) {
                return -1;
            }
            else if (char_buf1[i] > char_buf2[i]) {
                return 1;
            }
        }

        return 0;
    }
};

namespace String {

    inline int wcscmp(const wchar_t* const left, const wchar_t* const right)
    {
        std::size_t i = 0;

        while (left[i] == right[i])
        {
            if (left[i] == L'\0')
                return 0;

            i++;
        }

        return (left[i] - right[i]);
    }

#pragma region wstring
    inline int wtoupper(int c)
    {
        if (c >= L'a' && c <= L'z') return c - L'a' + L'A';
        if (c >= L'?' && c <= L'?') return c - L'?' + L'?';
        if (c == L'?') return L'?';
        return c;
    }
    inline  int wtolower(int c)
    {
        if (c >= L'A' && c <= L'Z') return c - L'A' + L'a';
        if (c >= L'?' && c <= L'?') return c - L'?' + L'?';
        if (c == L'?') return L'?';
        return c;
    }
    inline int wstrlen(const wchar_t* s)
    {
        int cnt = 0;
        if (!s) return 0;
        for (; *s != 0; ++s) ++cnt;
        return cnt;
    }
    inline int wstrcmp(const wchar_t* cs, const wchar_t* ct)
    {
        if (cs && ct)
        {
            while (*cs == *ct)
            {
                if (*cs == 0 && *ct == 0) return 0;
                if (*cs == 0 || *ct == 0) break;
                cs++;
                ct++;
            }
            return *cs - *ct;
        }
        return -1;
    }
    inline  int wstricmp(const wchar_t* cs, const wchar_t* ct)
    {
        if (cs && ct)
        {
            while (wtolower(*cs) == wtolower(*ct))
            {
                if (*cs == 0 && *ct == 0) return 0;
                if (*cs == 0 || *ct == 0) break;
                cs++;
                ct++;
            }
            return wtolower(*cs) - wtolower(*ct);
        }
        return -1;
    }
    inline  wchar_t* wstrstr(const wchar_t* s, const wchar_t* find)
    {
        wchar_t c, sc;
        if ((c = *find++) != 0)
        {
            do
            {
                do
                {
                    if ((sc = *s++) == 0)
                        return 0;
                } while (sc != c);
            } while (wstricmp(s, find) != 0);
            s--;
        }
        return (wchar_t*)s;
    }
    inline wchar_t* wstrset(wchar_t* szToFill, int szFill)
    {
        wchar_t* t = szToFill;
        while (*szToFill != 0)
        {
            *szToFill = szFill;
            szToFill++;
        }
        return t;
    }
    inline wchar_t* wstrnset(wchar_t* szToFill, int szFill, unsigned __int64 sizeMaxFill)
    {
        wchar_t* t = szToFill;
        int i = 0;
        while (*szToFill != 0 && i < (int)sizeMaxFill)
        {
            *szToFill = szFill;
            szToFill++;
            i++;
        }
        return t;
    }
    inline  wchar_t* wstrrev(wchar_t* s)
    {
        wchar_t a, * b, * e;
        b = e = s;
        while (*e) e++;
        e--;
        while (b < e)
        {
            a = *b;
            *b = *e;
            *e = a;
            b++;
            e--;
        }
        return s;
    }
    inline int wstrnicmp(const wchar_t* s1, const wchar_t* s2, unsigned __int64 n)
    {
        if (n == 0) return 0;
        do
        {
            if (wtoupper(*s1) != wtoupper(*s2++)) return wtoupper(*(unsigned const char*)s1) - wtoupper(*(unsigned const char*)--s2);
            if (*s1++ == 0) break;
        } while (--n != 0);
        return 0;
    }
    inline wchar_t* wstrlwr(wchar_t* x)
    {
        wchar_t* y = x;
        while (*y)
        {
            *y = wtolower(*y);
            y++;
        }
        return x;
    }
    inline  wchar_t* wstrchr(const wchar_t* s, wchar_t c)
    {
        wchar_t cc = c;
        const wchar_t* sp = (wchar_t*)0;
        while (*s)
        {
            if (*s == cc) sp = s;
            s++;
        }
        if (cc == 0) sp = s;
        return (wchar_t*)sp;
    }
    inline  wchar_t* wstrtok_s(wchar_t* str, const wchar_t* delim, wchar_t** ctx)
    {
        if (!str) str = *ctx;
        while (*str && wstrchr(delim, *str)) str++;
        if (!*str)
        {
            *ctx = str;
            return 0;
        }
        *ctx = str + 1;
        while (**ctx && !wstrchr(delim, **ctx)) (*ctx)++;
        if (**ctx) *(*ctx)++ = 0;
        return str;
    }
    inline bool wisdigit(wchar_t c) { return c >= L'0' && c <= L'9'; }
    inline __int64 watoi64(const wchar_t* nptr)
    {
        wchar_t* s = (wchar_t*)nptr;
        __int64 acc = 0;
        int neg = 0;
        if (nptr == 0) return 0;
        while (*s = L' ') s++;
        if (*s == L'-')
        {
            neg = 1;
            s++;
        }
        else if (*s == L'+') s++;
        while (wisdigit(*s))
        {
            acc = 10 * acc + (*s - L'0');
            s++;
        }
        if (neg) acc *= -1;
        return acc;
    }
    inline int watoi(const wchar_t* nptr)
    {
        wchar_t* s = (wchar_t*)nptr;
        int acc = 0;
        int neg = 0;
        if (nptr == 0) return 0;
        while (*s = L' ') s++;
        if (*s == L'-')
        {
            neg = 1;
            s++;
        }
        else if (*s == L'+') s++;
        while (wisdigit(*s))
        {
            acc = 10 * acc + (*s - L'0');
            s++;
        }
        if (neg) acc *= -1;
        return acc;
    }
    inline wchar_t* itow(int number, wchar_t* destination, int base)
    {
        int count = 0;
        do
        {
            int digit = number % base;
            destination[count++] = (digit > 9) ? digit - 10 + L'A' : digit + L'0';
        } while ((number /= base) != 0);
        destination[count] = 0;
        int i;
        for (i = 0; i < count / 2; ++i)
        {
            wchar_t symbol = destination[i];
            destination[i] = destination[count - i - 1];
            destination[count - i - 1] = symbol;
        }
        return destination;
    }
#pragma endregion

#pragma region string
    inline int toupper(int c)
    {
        if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
        if (c >= '?' && c <= '?') return c - '?' + '?';
        if (c == '?') return '?';
        return c;
    }
    inline int tolower(int c)
    {
        if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
        if (c >= '?' && c <= '?') return c - '?' + '?';
        if (c == '?') return '?';
        return c;
    }
    inline unsigned __int64 strlen(const char* s)
    {
        int cnt = 0;
        if (!s) return 0;
        for (; *s != 0; ++s) ++cnt;
        return cnt;
    }
#ifndef strcmp
    inline int strcmp(const char* cs, const char* ct)
    {
        if (cs && ct)
        {
            while (*cs == *ct)
            {
                if (*cs == 0 && *ct == 0) return 0;
                if (*cs == 0 || *ct == 0) break;
                cs++;
                ct++;
            }
            return *cs - *ct;
        }
        return -1;
    }
#endif
    inline  int stricmp(const char* cs, const char* ct)
    {
        if (cs != 0 && ct != 0 && cs[0] != 0 && ct[0] != 0)
        {
            while (tolower(*cs) == tolower(*ct))
            {
                if (*cs == 0 && *ct == 0) return 0;
                if (*cs == 0 || *ct == 0) break;
                cs++;
                ct++;
            }
            return tolower(*cs) - tolower(*ct);
        }
        return -1;
    }
#ifndef strstr
    inline char* strstr(const char* s, const char* find)
    {
        if (s == 0 || find == 0) return 0;
        if (s[0] == 0 || find[0] == 0) return 0;

        char c, sc;
        if ((c = *find++) != 0)
        {
            do
            {
                do
                {
                    if ((sc = *s++) == 0)
                        return 0;
                } while (sc != c);
            } while (stricmp(s, find) != 0);
            s--;
        }
        return (char*)s;
    }
#endif
    inline char* strset(char* szToFill, int szFill)
    {
        char* t = szToFill;
        while (*szToFill != 0)
        {
            *szToFill = szFill;
            szToFill++;
        }
        return t;
    }
    inline char* strnset(char* szToFill, int szFill, unsigned __int64 sizeMaxFill)
    {
        char* t = szToFill;
        int i = 0;
        while (*szToFill != 0 && i < (int)sizeMaxFill)
        {
            *szToFill = szFill;
            szToFill++;
            i++;
        }
        return t;
    }
    inline  char* strrev(char* s)
    {
        char a, * b, * e;
        b = e = s;
        while (*e) e++;
        e--;
        while (b < e)
        {
            a = *b;
            *b = *e;
            *e = a;
            b++;
            e--;
        }
        return s;
    }
    inline int strnicmp(const char* s1, const char* s2, unsigned __int64 n)
    {
        if (n == 0) return 0;
        do
        {
            if (toupper(*s1) != toupper(*s2++)) return toupper(*(unsigned const char*)s1) - toupper(*(unsigned const char*)--s2);
            if (*s1++ == 0) break;
        } while (--n != 0);
        return 0;
    }
    inline char* strlwr(char* x)
    {
        char* y = x;
        while (*y)
        {
            *y = tolower(*y);
            y++;
        }
        return x;
    }
    inline char* strchr(const char* s, char c)
    {
        char cc = c;
        const char* sp = (char*)0;
        while (*s)
        {
            if (*s == cc) sp = s;
            s++;
        }
        if (cc == 0) sp = s;
        return (char*)sp;
    }
    inline 
        char* strtok_s(char* str, const char* delim, char** ctx)
    {
        if (!str) str = *ctx;
        while (*str && strchr(delim, *str)) str++;
        if (!*str)
        {
            *ctx = str;
            return 0;
        }
        *ctx = str + 1;
        while (**ctx && !strchr(delim, **ctx)) (*ctx)++;
        if (**ctx) *(*ctx)++ = 0;
        return str;
    }
    inline  bool isdigit(char c) { return c >= '0' && c <= '9'; }
    inline  __int64 atoi64(const char* nptr)
    {
        char* s = (char*)nptr;
        __int64 acc = 0;
        int neg = 0;
        if (nptr == 0) return 0;
        while (*s = ' ') s++;
        if (*s == '-')
        {
            neg = 1;
            s++;
        }
        else if (*s == '+') s++;
        while (isdigit(*s))
        {
            acc = 10 * acc + (*s - '0');
            s++;
        }
        if (neg) acc *= -1;
        return acc;
    }
    inline  int atoi(const char* nptr)
    {
        char* s = (char*)nptr;
        int acc = 0;
        int neg = 0;
        if (nptr == 0) return 0;
        while (*s = ' ') s++;
        if (*s == '-')
        {
            neg = 1;
            s++;
        }
        else if (*s == '+') s++;
        while (isdigit(*s))
        {
            acc = 10 * acc + (*s - '0');
            s++;
        }
        if (neg) acc *= -1;
        return acc;
    }
    inline char* itoa(int number, char* destination, int base)
    {
        int count = 0;
        do
        {
            int digit = number % base;
            destination[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
        } while ((number /= base) != 0);
        destination[count] = 0;
        int i;
        for (i = 0; i < count / 2; ++i)
        {
            char symbol = destination[i];
            destination[i] = destination[count - i - 1];
            destination[count - i - 1] = symbol;
        }
        return destination;
    }
#pragma endregion

#pragma region convert
    inline  char wtoc(wchar_t w)
    {
        if (w == L'?') return '?';
        if (w == L'?') return '?';
        if (w >= L'?' && w <= L'?') return w - L'?' + '?';
        if (w >= L'?' && w <= L'?') return w - L'?' + '?';
        return (char)w;
    }
    inline  wchar_t ctow(char w)
    {
        if (w == '?') return L'?';
        if (w == '?') return L'?';
        if (w >= '?' && w <= '?') return w - '?' + L'?';
        if (w >= '?' && w <= '?') return w - '?' + L'?';
        return w;
    }
    inline int mbstowcs(wchar_t* Dest, const char* Source, unsigned __int64 MaxCount)
    {
        int result = -1;
        if (Dest && !MaxCount) return 0;
        if (MaxCount > 0x7FFFFFFF) return -1;
        if (Dest)
        {
            do Dest[result] = ctow(Source[result]);
            while (Source[++result]);
        }
        else
        {
            do ++result;
            while (Source[result]);
        }
        return result;
    }
    inline int wcstombs(char* Dest, const wchar_t* Source, unsigned __int64 MaxCount)
    {
        int result = -1;
        if (Dest && !MaxCount) return 0;
        if (MaxCount > 0x7FFFFFFF) return -1;
        if (Dest)
        {
            do Dest[result] = wtoc(Source[result]);
            while (Source[++result]);
        }
        else
        {
            do ++result;
            while (Source[result]);
        }
        return result;
    }

    inline int towupper(int c)
	{
		if (c >= L'a' && c <= L'z') return c - L'a' + L'A';
		if (c >= L'?' && c <= L'?') return c - L'?' + L'?';
		if (c == L'?') return L'?';
		return c;
	}
    inline int towlower(int c)
	{
		if (c >= L'A' && c <= L'Z') return c - L'A' + L'a';
		if (c >= L'?' && c <= L'?') return c - L'?' + L'?';
		if (c == L'?') return L'?';
		return c;
	}
	
	
    inline bool iswdigit(wchar_t c) { return c >= L'0' && c <= L'9'; }
    inline __int64 wtoi64(const wchar_t* nptr)
	{
		wchar_t* s = (wchar_t*)nptr;
		__int64 acc = 0;
		int neg = 0;
		if (nptr == 0) return 0;
		while (*s = L' ') s++;
		if (*s == L'-')
		{
			neg = 1;
			s++;
		}
		else if (*s == L'+') s++;
		while (iswdigit(*s))
		{
			acc = 10 * acc + (*s - L'0');
			s++;
		}
		if (neg) acc *= -1;
		return acc;
	}
    inline int wtoi(const wchar_t* nptr)
	{
		wchar_t* s = (wchar_t*)nptr;
		int acc = 0;
		int neg = 0;
		if (nptr == 0) return 0;
		while (*s = L' ') s++;
		if (*s == L'-')
		{
			neg = 1;
			s++;
		}
		else if (*s == L'+') s++;
		while (iswdigit(*s))
		{
			acc = 10 * acc + (*s - L'0');
			s++;
		}
		if (neg) acc *= -1;
		return acc;
	}

}
