#include "../Includes/includes.hpp"

#include "../Utils/stb_sprintf.h"

inline int sprintf(char* buf, const char* fmt, ...) {
	va_list list{};
	va_start(list, fmt);
	auto result = stbsp_vsprintf(buf, fmt, list);
	va_end(list);

	return result;
}

#define _CRTALLOC(x) __declspec(allocate(x))

// C initializers
#pragma const_seg(".CRT$XIA")
extern _CRTALLOC( ".CRT$XIA" ) _PIFV __xi_a[] = { NULL };
#pragma const_seg(".CRT$XIZ")
extern _CRTALLOC( ".CRT$XIZ" ) _PIFV __xi_z[] = { NULL };
// C++ initializers
#pragma const_seg(".CRT$XCA")
extern _CRTALLOC( ".CRT$XCA" ) _PVFV __xc_a[] = { NULL };
#pragma const_seg(".CRT$XCZ")
extern _CRTALLOC( ".CRT$XCZ" ) _PVFV __xc_z[] = { NULL };
#pragma const_seg()
#pragma comment(linker, "/merge:.CRT=.rdata")

#define MALLOC_MAGIC 'MGIC'

typedef struct _ON_EXIT_ENTRY
{
	SLIST_ENTRY Entry;
	_PVFV func;
} ON_EXIT_ENTRY, * PON_EXIT_ENTRY;

SLIST_HEADER __onexithead;

#pragma function(memset)
void* __cdecl memset( void* s, int c, size_t len )
{
	unsigned char* dst = reinterpret_cast< unsigned char* >( s );
	while ( len > 0 )
	{
		*dst = ( unsigned char )c;
		dst++;
		len--;
	}
	return s;
}
#pragma function(wcslen)
size_t wcslen(const wchar_t* str) {
	size_t length = 0;
	while (*str != L'\0') {
		++length;
		++str;
	}
	return length;
}

#pragma function(memcpy)
void* memcpy( void* destination, const void* source, std::size_t size )
{
	char* pszDest = ( char* )destination;
	const char* pszSource = ( const char* )source;
	if ( ( pszDest != NULL ) && ( pszSource != NULL ) )
	{
		while (size)
		{
			*( pszDest++ ) = *( pszSource++ );
			--size;
		}
	}
	return destination;
}

#pragma function(memcmp)
int memcmp(const void* buf1, const void* buf2, size_t len) {
	return crt::memcmp(buf1, buf2, len);
}

#pragma function(memchr)
const void* memchr(const void* src, int chr, size_t len) {
	return crt::memchr(src, chr, len);
}

#pragma function(memmove)
void* memmove( void* dest, const void* src, size_t n )
{
	signed char operation;
	size_t end;
	size_t current;

	if ( dest != src ) {
		if ( dest < src ) {
			operation = 1;
			current = 0;
			end = n;
		}
		else {
			operation = -1;
			current = n - 1;
			end = -1;
		}

		for ( ; current != end; current += operation ) {
			*( ( ( unsigned char* )dest ) + current ) = *( ( ( unsigned char* )src ) + current );
		}
	}
	return dest;
}

#pragma function(strcmp)
int strcmp( const char* s1, const char* s2 )
{
	while ( *s1 && ( *s1 == *s2 ) )
	{
		s1++;
		s2++;
	}
	return *( const unsigned char* )s1 - *( const unsigned char* )s2;
}

#pragma function(strcpy)
char* strcpy( char* _dst, const char* _src )
{
	while ( ( *_dst++ = *_src++ ) );
	return _dst;
}

#pragma function(strncpy)
char* strncpy( char* _dst, const char* _src, size_t _n )
{
	size_t i = 0;
	while ( i++ != _n && ( *_dst++ = *_src++ ) );
	return _dst;
}

#pragma function(strlen)
size_t strlen( const char* str )
{
	const char* s;

	for ( s = str; *s; ++s );

	return ( s - str );
}


typedef struct _MALLOC_HEADER
{
	ULONG32 Magic;
	ULONG32 _Resv0;
	ULONG_PTR Size;
} MALLOC_HEADER, * PMALLOC_HEADER;
C_ASSERT( sizeof( MALLOC_HEADER ) % sizeof( void* ) == 0 );

PMALLOC_HEADER GET_MALLOC_HEADER( PVOID ptr )
{
	return ( MALLOC_HEADER* )( ( PUCHAR )ptr - sizeof( MALLOC_HEADER ) );
}

PVOID GET_MALLOC_ADDRESS( PMALLOC_HEADER header )
{
	return ( PVOID )( ( PUCHAR )header + sizeof( MALLOC_HEADER ) );
}

ULONG_PTR GET_MALLOC_SIZE( PVOID ptr )
{
	PMALLOC_HEADER header = GET_MALLOC_HEADER( ptr );

	if ( header->Magic != MALLOC_MAGIC )
	{
		__debugbreak();
		RtlRaiseException( nullptr );
	}

	return header->Size;
}

void* __cdecl malloc( size_t size )
{
	PMALLOC_HEADER mhdr = NULL;
	const size_t new_size = size + sizeof( MALLOC_HEADER );

	mhdr = ( PMALLOC_HEADER )RtlAllocateHeap( NtCurrentPeb()->ProcessHeap, HEAP_ZERO_MEMORY, new_size );
	if ( mhdr )
	{
		mhdr->Magic = MALLOC_MAGIC;
		mhdr->Size = size;
		return GET_MALLOC_ADDRESS( mhdr );
	}

	return NULL;
}

void __cdecl free( void* ptr )
{
	if ( ptr )
	{
		MALLOC_HEADER* mhdr = GET_MALLOC_HEADER( ptr );

		if ( mhdr->Magic != MALLOC_MAGIC )
		{
			__debugbreak();
			return RtlRaiseException( nullptr );
		}
		RtlFreeHeap( NtCurrentPeb()->ProcessHeap, NULL, mhdr );
	}
}

void* __cdecl realloc( void* ptr, size_t new_size )
{
	if ( !ptr )
	{
		return malloc( new_size );
	}
	else if ( new_size == 0 )
	{
		free( ptr );
		return NULL;
	}
	else
	{
		size_t old_size = GET_MALLOC_SIZE( ptr );

		if ( new_size <= old_size ) {
			return ptr;
		}
		else {
			void* new_ptr = malloc( new_size );

			if ( new_ptr ) {
				memcpy( new_ptr, ptr, old_size );
				free( ptr );
				return new_ptr;
			}
		}
	}
	return NULL;
}

char _CRT_CWD[ 260 ] = { 0 };

const char* _get_cwd()
{
	return _CRT_CWD;
}

void _set_cwd( const char* path )
{
	strncpy( _CRT_CWD, path, _countof( _CRT_CWD ) );
}

BOOLEAN _init_cwd()
{
	_set_cwd( XS( "C:\\WINDOWS\\System32" ) );
	return TRUE;
}

void __cdecl _cinitfs( void )
{
	_init_cwd();
}

void _initterm( _PVFV* pfbegin, _PVFV* pfend )
{
	/*
	* walk the table of function pointers from the bottom up, until
	* the end is encountered.  Do not skip the first entry.  The initial
	* value of pfbegin points to the first valid entry.  Do not try to
	* execute what pfend points to.  Only entries before pfend are valid.
	*/
	while ( pfbegin < pfend )
	{
		/*
		* if current table entry is non-NULL, call thru it.
		*/
		if ( *pfbegin != NULL )
			( **pfbegin )( );
		++pfbegin;
	}
}

int __cdecl _cinit( void )
{
	_cinitfs();
	RtlInitializeSListHead( &__onexithead );

	/*
	* do C++ initializations
	*/
	_initterm( __xc_a, __xc_z );

	return 0;
}

_PVFV _onexit( _PVFV lpfn )
{
	PON_EXIT_ENTRY _Entry = ( PON_EXIT_ENTRY )malloc( sizeof( ON_EXIT_ENTRY ) );

	if ( !_Entry )
		return NULL;

	_Entry->func = lpfn;
	RtlInterlockedPushEntrySList( &__onexithead, &_Entry->Entry );
	return lpfn;
}

int __cdecl atexit( _PVFV func )
{
	return ( _onexit( func ) == NULL ) ? -1 : 0;
}

void doexit( int code, int quick, int retcaller )
{
	UNREFERENCED_PARAMETER( code );
	UNREFERENCED_PARAMETER( retcaller );

	if ( !quick )
	{
		while ( auto _Entry = RtlInterlockedPopEntrySList( &__onexithead ) )
		{
			PON_EXIT_ENTRY Entry = ( PON_EXIT_ENTRY )_Entry;

			Entry->func();
			free( Entry );
		}
	}
}

void __cdecl _cexit( void )
{
	doexit( 0, 0, 1 );    /* full term, return to caller */
}

//////////////////////////////////////////////////////////////////////////
// dummy
char* __cdecl getenv( char const* name )
{
	name;
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
// assert
void __cdecl _wassert( wchar_t const* _Message, wchar_t const* _File, unsigned _Line )
{
	_Message;
	_File;
	_Line;

	__debugbreak();
	RtlRaiseException( nullptr );
}

void* __cdecl operator new( size_t size )
{
	return malloc( size );
}

void* __cdecl operator new[]( size_t size )
{
	return malloc( size );
}

void __cdecl operator delete( void* ptr )
{
	free( ptr );
}

void __cdecl operator delete( void* ptr, size_t )
{
	free( ptr );
}

void __cdecl operator delete[]( void* ptr )
{
	free( ptr );
}

void* operator new[]( size_t size, const char*, int, unsigned, const char*, int )
{
	return malloc( size );
}

void* operator new[]( size_t size, size_t, size_t, const char*, int, unsigned, const char*, int )
{
	return malloc( size );
}

float __cdecl fmaxf( float left, float right )
{
	return ( left > right ) ? left : right;
}

float __cdecl fminf( float left, float right )
{
	return ( left < right ) ? left : right;
}

void __cdecl std::_Xlength_error( char const* )
{
	return;
}

void __cdecl std::_Xbad_function_call( void )
{
	return;
}

void __cdecl std::_Xout_of_range( char const* )
{
	return;
}

EXTERN_C
_ACRTIMP void __cdecl _invoke_watson(
	_In_opt_z_ wchar_t const* _Expression,
	_In_opt_z_ wchar_t const* _FunctionName,
	_In_opt_z_ wchar_t const* _FileName,
	_In_       unsigned int _LineNo,
	_In_       uintptr_t _Reserved )
{
}

namespace std { _Prhand _Raise_handler; }

extern "C"
{

	EXCEPTION_DISPOSITION __C_specific_handler(PEXCEPTION_RECORD ExceptionRecord, PVOID EstablisherFrame, PCONTEXT ContextRecord, PDISPATCHER_CONTEXT DispatcherContext)
	{
		return {};
	}

}
extern "C" void __cdecl
_invalid_parameter(
	wchar_t const* const expression,
	wchar_t const* const function_name,
	wchar_t const* const file_name,
	unsigned int   const line_number,
	uintptr_t      const reserved )
{

}

extern "C" void __cdecl
_invalid_parameter_noinfo( void )
{

}

extern "C" __declspec( noreturn ) void __cdecl
_invalid_parameter_noinfo_noreturn( void )
{

}

//#pragma function(_ftol2)
//extern "C" __declspec( naked ) void _ftol2()
//{
//	__asm
//	{
//		fistp qword ptr[ esp - 8 ]
//		mov   edx, [ esp - 4 ]
//		mov   eax, [ esp - 8 ]
//		ret
//	}
//}
//
//#pragma function(_ftol2_sse)
//extern "C" __declspec( naked ) void _ftol2_sse()
//{
//	__asm
//	{
//		fistp dword ptr[ esp - 4 ]
//		mov   eax, [ esp - 4 ]
//		ret
//	}
//}

#pragma function(_purecall)
extern "C" int _purecall( void )
{
	return 0;
}