#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"
#include "../../Features/Visuals/Visuals.hpp"

void Hooks::OnNetworkMessage(AssemblyCSharp::Client* _This, Network::Message* message)
{
	if (!InGame)
		return Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);
	}

	Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);

	if (message->type() == MessageType::Effect)
	{
		if (m_settings::RaidESP)
		{
			auto EffectNetworkClass = CIl2Cpp::FindClass(XS(""), XS("EffectNetwork"));
			if (!EffectNetworkClass)
				return Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);


			auto effect = *reinterpret_cast<AssemblyCSharp::Effect**>((uintptr_t)EffectNetworkClass + 0xB8);
			if (!IsAddressValid(effect))
			{
				return Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);
			}

			effect = *reinterpret_cast<AssemblyCSharp::Effect**>(effect);
			if (!IsAddressValid(effect))
			{
				return Hooks::OnNetworkMessagehk.get_original< decltype(&OnNetworkMessage)>()(_This, message);
			}

			auto pos = effect->worldPos();
			if (pos.IsZero())
				pos = effect->origin();

			if (effect->pooledstringid() == 1798302402 && m_settings::ShowExplosiveAmmo)
				LogSystem::LogExplosion(XS("Explosive Ammo"), pos);
			else if (effect->pooledstringid() == 857997843 && m_settings::ShowC4)
				LogSystem::LogExplosion(XS("C4"), pos);
			else if (effect->pooledstringid() == 1289728008 && m_settings::ShowSatchel)
				LogSystem::LogExplosion(XS("Satchel"), pos);
			else if (effect->pooledstringid() == -1241151013 && m_settings::ShowRocket)
			{
				LogSystem::LogExplosion(XS("Rocket"), pos);
			}
		}
	}

}
