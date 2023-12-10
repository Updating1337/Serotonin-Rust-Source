#include "Core/Core.hpp"

void cheat_main()
{
#ifndef DEBUG_MODE
    //fix_relocations();
#endif
	Core().Instance()->Init();
}

#ifdef DEBUG_MODE
BOOL DllMain(HINSTANCE instance, DWORD reason, void* reserved)
{
		switch (reason)
		{
			// Attach
		case DLL_PROCESS_ATTACH:
		{
			LI_FN(DisableThreadLibraryCalls)(instance);
			LI_FN(CreateThread).cached()(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&cheat_main), 0, 0, 0);
			break;
		}
		default:
			break;
		}
		return TRUE;
}
#else

extern "C" IMAGE_DOS_HEADER __ImageBase;

BOOL __stdcall DllMain(std::uintptr_t mod, std::uint32_t call_reason, std::uintptr_t reserved) {
    static bool thread_inited = false;

    if (call_reason == DLL_PROCESS_ATTACH)
    {
        const auto NtHeader = (PIMAGE_NT_HEADERS)(((PUINT8)&__ImageBase) + __ImageBase.e_lfanew);
        const auto EacBase = (PUINT8)mod;
        const auto EOS_Entry = &EacBase[NtHeader->OptionalHeader.AddressOfEntryPoint];

        if (!thread_inited)
        {
            LI_FN(CreateThread)(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(cheat_main), nullptr, 0, nullptr);
            thread_inited = true;
        }

        const auto eac_dll_fn =
            reinterpret_cast<decltype(&DllMain)>(EOS_Entry);

        const auto result = eac_dll_fn(mod, call_reason, reserved);
        return result;
    }

    return TRUE;
}
#endif
