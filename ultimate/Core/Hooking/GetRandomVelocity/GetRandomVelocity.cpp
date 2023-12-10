#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

float Hooks::GetRandomVelocity(AssemblyCSharp::ItemModProjectile* _This)
{
	LOG(XS("[DEBUG] GetRandomVelocity Hooked"));

	if (!InGame)
		return Hooks::GetRandomVelocityhk.get_original< decltype(&GetRandomVelocity)>()(_This);

	if (!_This)
		return Hooks::GetRandomVelocityhk.get_original< decltype(&GetRandomVelocity)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::GetRandomVelocityhk.get_original< decltype(&GetRandomVelocity)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::GetRandomVelocityhk.get_original< decltype(&GetRandomVelocity)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::GetRandomVelocityhk.get_original< decltype(&GetRandomVelocity)>()(_This);
	}
	
	float Modifier = 1.f;
	//FastBullet
	if (m_settings::NormalFastBullet)
		Modifier += 0.4f;

	LOG(XS("[DEBUG] GetRandomVelocity Hooked"));

	return _This->GetRandomVelocity() * Modifier;
}