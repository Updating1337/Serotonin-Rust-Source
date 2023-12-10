#include "../Hooks.hpp"




void Hooks::SteamPlatformUpdate(RustPlatformSteam::SteamPlatform* _This)
{
	Hooks::SteamPlatformUpdatehk.get_original< decltype(&SteamPlatformUpdate)>()(_This);

	if (m_settings::NameSpoofer)
	{
		unsigned random_number = (my_rand() % 100) + 1;
		_This->set_UserName(Facepunch::RandomUsernames().Get(random_number));
	}

}