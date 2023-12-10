#include "../Hooks.hpp"

inline AssemblyCSharp::ExplosionsFPS* Instance2 = 0;

void Hooks::Update_(AssemblyCSharp::MainMenuSystem* _This)
{
	if (Instance2 == 0)
		Instance2 = reinterpret_cast<AssemblyCSharp::ExplosionsFPS*>(_This->get_gameObject()->AddComponent(FPSystem::Type::PostProcessDebug()));

	return Hooks::Update_hk.get_original< decltype(&Update_)>()(_This);
}