#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"
#include "../../Features/Notifications/Notifications.hpp"


void Hooks::OnAttacked(AssemblyCSharp::BasePlayer* instance, AssemblyCSharp::HitInfo* hitinfo)
{
	if (!InGame)
		return Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);

	if (m_settings::KillEffects) {
		if (hitinfo->DidHit()) {
			int selectedKillEffect = m_settings::SelectedKillEffect;

			switch (selectedKillEffect) {
			case 0:
				if (ExplosionAsset)
				{
					if (hitinfo->Initiator() == AssemblyCSharp::LocalPlayer::get_Entity() && UnityEngine::Time::get_realtimeSinceStartup() - instance->lastHeadshotSoundTime() > 0.01f)
					{
						auto camera = UnityEngine::Camera::get_main();
						if (IsAddressValid(camera)) {
							auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
							if (IsAddressValid(m_target.m_player))
							{
								ExplosionPrefab->set_active(true);
								UnityEngine::GameObject().Instantiate(ExplosionPrefab, m_target.m_position, m_target.m_player->eyes()->get_rotation());
							}
							else
							{
								ExplosionPrefab->set_active(false);
							}
						}
						else {
							ExplosionPrefab->set_active(false);
						}
						instance->lastHeadshotSoundTime() = UnityEngine::Time::get_realtimeSinceStartup();
					}

				}
				break;
			case 1:
				if (GhostAsset)
				{
					if (hitinfo->Initiator() == AssemblyCSharp::LocalPlayer::get_Entity() && UnityEngine::Time::get_realtimeSinceStartup() - instance->lastHeadshotSoundTime() > 0.01f)
					{
						auto camera = UnityEngine::Camera::get_main();
						if (IsAddressValid(camera)) {
							auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
							if (IsAddressValid(m_target.m_player))
							{
								GhostPrefab->set_active(true);
								UnityEngine::GameObject().Instantiate(GhostPrefab, m_target.m_position, m_target.m_player->eyes()->get_rotation());
							}
							else
							{
								GhostPrefab->set_active(false);
							}
						}
						else {
							GhostPrefab->set_active(false);
						}
						instance->lastHeadshotSoundTime() = UnityEngine::Time::get_realtimeSinceStartup();
					}

				}
				break;
			}
		}
	}


	if (m_settings::CustomHitSounds)
	{
		if (hitinfo->Initiator() == AssemblyCSharp::LocalPlayer::get_Entity() && UnityEngine::Time::get_realtimeSinceStartup() - instance->lastHeadshotSoundTime() > 0.01f)
		{
			typedef NTSTATUS(WINAPI* tPlaySoundW)(LPCWSTR, HMODULE, DWORD);
			tPlaySoundW PlaySoundW_ = nullptr;

			const auto image_winmm = GetImage(HASH(L"Winmm.dll"));

			if (IsAddressValid(image_winmm))
				PlaySoundW_ = (tPlaySoundW)(GetImageExport(image_winmm, HASH("PlaySoundW")));

			PlaySoundW_(XS(L"C:\\hitsound.wav"), NULL, 0x0001);
			instance->lastHeadshotSoundTime() = UnityEngine::Time::get_realtimeSinceStartup();
		}
	}

	if (m_settings::DisableHitSounds)
	{
		return;
	}

	if (m_settings::HitboxOverride)
	{
	//	LOG("[DEBUG] HITBONE - %d", hitinfo->HitBone());
		int selectedHitbox = m_settings::SelectedHitbox;

		if (selectedHitbox == 0)
		{
			hitinfo->HitBone() = 698017942;
			//head: 698017942
		}
	}


	/*
	Flesh - 1395914656
Glass - 432631845
Metal - 1632307590
Water - 188178580

	*/

	if (m_settings::HitMaterial == 0) //flesh
	{
		//auto stringpol = AssemblyCSharp::StringPool::Get(XS("Flesh"));
		hitinfo->HitMaterial() = 1395914656;
	}
	else if (m_settings::HitMaterial == 1) //glass
	{
		//auto stringpol = AssemblyCSharp::StringPool::Get(XS("Glass"));
		hitinfo->HitMaterial() = 432631845;
	}
	else if (m_settings::HitMaterial == 2) //metal
	{
		//auto stringpol = AssemblyCSharp::StringPool::Get(XS("Metal"));
		hitinfo->HitMaterial() = 1632307590;
	}
	else if (m_settings::HitMaterial == 3) //water
	{
		//auto stringpol = AssemblyCSharp::StringPool::Get(XS("Water"));
		hitinfo->HitMaterial() = 188178580;
	}


	Hooks::OnAttackedhk.get_original< decltype(&OnAttacked)>()(instance, hitinfo);
}