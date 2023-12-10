#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::TryToMove(AssemblyCSharp::ItemIcon* _This)
{
	if (!InGame)
		return Hooks::TryToMovehk.get_original< decltype(&TryToMove)>()(_This);

	if (!_This)
		return Hooks::TryToMovehk.get_original< decltype(&TryToMove)>()(_This);

	if(!IsAddressValid(Features().LocalPlayer))
		return Hooks::TryToMovehk.get_original< decltype(&TryToMove)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::TryToMovehk.get_original< decltype(&TryToMove)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::TryToMovehk.get_original< decltype(&TryToMove)>()(_This);
	}

	Hooks::TryToMovehk.get_original< decltype(&TryToMove)>()(_This);

	if (m_settings::InstantLoot) {

		if (_This->queuedForLooting())
		{
			_This->RunTimedAction();
		}
	}
}