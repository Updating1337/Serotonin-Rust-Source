#include "Includes/includes.hpp"


#ifndef NEW_EAC


struct eac_info
{
    uint32_t entry;
    uint32_t cheat_base;
};

namespace eac
{
    inline uint64_t base;
    inline uint64_t entry;
};

inline eac_info eac_data;

inline unsigned char _TAG[] = { 0xFF, 0xAC, 0x32, 0x4D, 0xAB, 0xAB, 0x88, 0x69 };

static void fix_relocations()
{
    uint64_t image_base = (eac::base + eac_data.cheat_base);
    PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(image_base);
    PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>((reinterpret_cast<LPBYTE>(image_base) + dos_header->e_lfanew));

    PIMAGE_BASE_RELOCATION BaseRelocation = reinterpret_cast<IMAGE_BASE_RELOCATION*>(eac::base + nt_headers->OptionalHeader.DataDirectory[5].VirtualAddress);

    DWORD RelocationSize = nt_headers->OptionalHeader.DataDirectory[5].Size;

    DWORD nBytes = 0;
    uint64_t delta = reinterpret_cast<uint64_t>(reinterpret_cast<LPBYTE>(image_base) - nt_headers->OptionalHeader.ImageBase);

    while (true)
    {
        uint64_t count = (BaseRelocation->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
        WORD* list = reinterpret_cast<WORD*>(BaseRelocation + 1);

        if (nBytes >= RelocationSize)
            break;

        for (uint64_t i = 0; i < count; i++)
        {
            if (list[i])
            {
                uint64_t* pointer = reinterpret_cast<uint64_t*>(eac::base + (BaseRelocation->VirtualAddress + (list[i] & 0xFFF)));
                *pointer += delta;
            };
        };

        nBytes += BaseRelocation->SizeOfBlock;
        BaseRelocation = reinterpret_cast<PIMAGE_BASE_RELOCATION>(reinterpret_cast<LPBYTE>(BaseRelocation) + BaseRelocation->SizeOfBlock);
    }
}


#endif


class Core {
public:
	static auto Instance() -> Core*
	{
		Core obj;
		return &obj;
	}


	void Init();
	void InitIl2Cpp();
};