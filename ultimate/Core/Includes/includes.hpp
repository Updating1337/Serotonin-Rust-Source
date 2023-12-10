#pragma once

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#undef _HAS_EXCEPTIONS
#define _HAS_EXCEPTIONS 0

#ifndef __FLTUSED__
#define __FLTUSED__
extern "C" __declspec( selectany ) int _fltused = 1;
#endif

#define SAFE_RELEASE( x ) if( x ) { x->Release(); x = nullptr; }

#include <Windows.h>
#include <process.h>
#include <intrin.h>
#include <functional>
#include <vector>
#include <string>

#include "../CRT/memory.hpp"
#include "../CRT/ntwinddk.hpp"
#include "../Utils/xorstr.hpp"
#include "../CRT/crt.hpp"
#include "../Utils/lazy.hpp"
#include "../CRT/color.hpp"
#include "../CRT/math.hpp"

using namespace memory;

#define JOIN_IMPL( A, B )						A ## B
#define JOIN( A, B )								JOIN_IMPL( A, B )

#define FIELD_PAD( Size )						std::uint8_t JOIN( __pad, __COUNTER__ )[ Size ] = { }

#define IS_NULL_POINTER(ptr) ((ptr) == nullptr)


struct bounds_t {
	float left, right, top, bottom;
};


class Unity_String
{
public:
	char zpad[0x10]{ };
	int size{ };
	wchar_t buffer[128 + 1];
public:
	Unity_String(const wchar_t* st)
	{
		size = minm(crt_wcslen(st), 128);
		for (int idx = 0; idx < size; idx++)
		{
			buffer[idx] = st[idx];
		}
		buffer[size] = 0;
	}

	wchar_t* GetWchar()
	{
		return buffer;
	}
};

#include <map>

struct box_bounds {
	float left, right, top, bottom;

	bool empty() {
		if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
			return true;

		if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)
			return true;

		return false;
	}
	static box_bounds null() {
		return { 0, 0, 0, 0 };
	}
};

inline std::string xCheatsKey;
inline std::vector<const char*> xCheatsUserArr;

inline std::string GlobalMessage;
inline float LocalPosX;
inline float LocalPosY;
inline float LocalPosZ;
inline box_bounds LocalBoxBounds;

inline std::map<const char*, int> xCheatsMap;
inline std::vector<std::string> xCheatsArr;

inline std::wstring xChetasRecievedKey;
inline uint32_t xCheatsRecievedSteamID;
static inline bool HitPlayer = false;
#define DEBUG_MODE //comment out for EAC 

inline char buffer[512];

inline const char* LOG(const char* fmt, ...) {
#ifdef DEBUG_MODE
	va_list args;
	va_start(args, fmt);
	LI_FN(vsnprintf)(buffer, 512, fmt, args);
	va_end(args);

	LI_FN(OutputDebugStringA)(buffer);

	return buffer;
#else
	return XS("");
#endif
}

inline uintptr_t m_game_assembly;
inline uintptr_t m_steam_api;
inline uintptr_t m_steam_client;

inline static bool SteamConnectorError = false;
inline bool InGame = false;
inline bool ToBeCalled = false;
inline static bool HasSetAmbient = false;
inline static bool HasSetNightColor = false;
inline static bool HasSetSharpCloud = false;
inline static bool HasSetDayColor = false;
inline static bool StartShooting = false;

#include "../Il2Cpp/il2cpp-api.hpp"
#include "../Il2Cpp/il2cpp-api-types.hpp"
#include "../Il2Cpp/il2cpp-blob.hpp"
#include "../Il2Cpp/il2cpp-class-internals.hpp"
#include "../Il2Cpp/il2cpp-config.hpp"
#include "../Il2Cpp/il2cpp-config-api.hpp"
#include "../Il2Cpp/il2cpp-metadata.hpp"
#include "../Il2Cpp/il2cpp-object-internals.hpp"
#include "../Il2Cpp/il2cpp-runtime-metadata.hpp"