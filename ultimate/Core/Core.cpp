#include "Core.hpp"
#include "CRT/crt.hpp"
#include "Il2Cpp/CIl2Cpp.hpp"
#include "SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "Hooking/Hooks.hpp"
#include "Net/net.h"


void Core::Init()
{
	_cinit();
#ifndef DEBUG_MODE
	LI_FN(Sleep)(30000);
#endif

	LOG(XS("[DEBUG] DLL Initialized!"));

	m_game_assembly = GetImage(XS(L"GameAssembly.dll"));

	if (!CIl2Cpp::CreateIL2CPP())
		return;

	//CIl2Cpp::il2cpp_thread_attach(CIl2Cpp::il2cpp_domain_get());

	//LOG(XS("[DEBUG] GameAssembly - %p"), m_game_assembly);


	//m_steam_api = GetImage(XS(L"steam_api64.dll"));
	//m_steam_client = (uintptr_t)GetImageExport(m_steam_api, HASH("SteamClient"));

	//net = new Net(m_steam_client);


	Hooks().Instance()->BeginHooks();
}