#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"
#include "../WriteToStream/Prediction.hpp"

void Hooks::DoAttackMelee(AssemblyCSharp::BaseMelee* _This)
{
	if (!InGame)
		return Hooks::DoAttackMeleehk.get_original< decltype(&DoAttackMelee)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::DoAttackMeleehk.get_original< decltype(&DoAttackMelee)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::DoAttackMeleehk.get_original< decltype(&DoAttackMelee)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::DoAttackMeleehk.get_original< decltype(&DoAttackMelee)>()(_This);
	}

	if (m_settings::LongMelee)
	{
		if (_This->maxDistance() != 3.f)
			_This->maxDistance() = 3.f;

		if (_This->attackRadius() != 3.f)
			_This->attackRadius() = 3.f;
	}

	Hooks::DoAttackMeleehk.get_original< decltype(&DoAttackMelee)>()(_This);

}