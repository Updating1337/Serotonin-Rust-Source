#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::BlockSprint(AssemblyCSharp::BasePlayer* _This, float duration)
{
	if (!InGame)
		return Hooks::BlockSprinthk.get_original< decltype(&BlockSprint)>()(_This, duration);

	if (!_This)
		return Hooks::BlockSprinthk.get_original< decltype(&BlockSprint)>()(_This, duration);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::BlockSprinthk.get_original< decltype(&BlockSprint)>()(_This, duration);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::BlockSprinthk.get_original< decltype(&BlockSprint)>()(_This, duration);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::BlockSprinthk.get_original< decltype(&BlockSprint)>()(_This, duration);
	}

	//CanAttack
	if (m_settings::NoAttackRestrictions)
		return;

	return Hooks::BlockSprinthk.get_original< decltype(&BlockSprint)>()(_This, duration);
}