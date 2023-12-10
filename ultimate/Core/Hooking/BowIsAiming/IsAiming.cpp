#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

bool Hooks::IsAiming(AssemblyCSharp::BowWeapon* _This)
{
	if (!InGame)
		return Hooks::IsAiminghk.get_original< decltype(&IsAiming)>()(_This);

	if (!_This)
		return Hooks::IsAiminghk.get_original< decltype(&IsAiming)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::IsAiminghk.get_original< decltype(&IsAiming)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::IsAiminghk.get_original< decltype(&IsAiming)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::IsAiminghk.get_original< decltype(&IsAiming)>()(_This);
	}

	if (m_settings::Autoshoot)
		return true;

	return Hooks::IsAiminghk.get_original< decltype(&IsAiming)>()(_This);
}