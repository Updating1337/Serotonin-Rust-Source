#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::PPA_WriteToStream(ProtoBuf::PlayerProjectileAttack* _This, ProtoBuf::Stream* Stream)
{
	if (!InGame)
		return Hooks::PPA_WriteToStreamhk.get_original< decltype(&PPA_WriteToStream)>()(_This, Stream);

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return Hooks::PPA_WriteToStreamhk.get_original< decltype(&PPA_WriteToStream)>()(_This, Stream);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::PPA_WriteToStreamhk.get_original< decltype(&PPA_WriteToStream)>()(_This, Stream);

	if (!_This || !Stream)
	{
		return Hooks::PPA_WriteToStreamhk.get_original< decltype(&PPA_WriteToStream)>()(_This, Stream);
	}

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::PPA_WriteToStreamhk.get_original< decltype(&PPA_WriteToStream)>()(_This, Stream);
	}


	auto PlayerAttack = _This->playerAttack();

	if (IsAddressValid(PlayerAttack)) {
		auto attack = PlayerAttack->attack();

		if (IsAddressValid(attack))
		{
			auto camera = UnityEngine::Camera::get_main();
			if (IsAddressValid(camera)) {

				auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
				if (IsAddressValid(AimbotTarget.m_player)) {
					if (!AimbotTarget.m_heli)
					{


						if (m_settings::HitboxOverride)
						{

							int selectedHitbox = m_settings::SelectedHitbox;
							switch (selectedHitbox) {
							case 0: // Head
								attack->hitBone() = 698017942;
								attack->hitPartID() = 2173623152;
								break;
							case 1: // pelvis
								attack->hitBone() = 1031402764;
								attack->hitPartID() = 1750816991;
								break;
							case 2: // Random hitbox
								int randomIndex = my_rand() % 9;
								switch (randomIndex) {
								case 0: // Head
									attack->hitBone() = 698017942;
									attack->hitPartID() = 2173623152;
									break;
								case 1: // pelvis
									attack->hitBone() = 2811218643;
									attack->hitPartID() = 1750816991;
									break;
								case 2: // r_hip
									attack->hitBone() = 2331610670;
									attack->hitPartID() = 1750816991;
									break;
								case 3: // r_foot
									attack->hitBone() = 920055401;
									attack->hitPartID() = 1750816991;
									break;
								case 4: // spine1
									attack->hitBone() = 3771021956;
									attack->hitPartID() = 1750816991;
									break;
								case 5: // l_hand
									attack->hitBone() = 736328754;
									attack->hitPartID() = 1750816991;
									break;
								case 6: // r_upperarm
									attack->hitBone() = 3901657145;
									attack->hitPartID() = 1750816991;
									break;
								case 7: // l_knee
									attack->hitBone() = 3892428003;
									attack->hitPartID() = 1750816991;
									break;
								case 8: // spine4
									attack->hitBone() = 827230707;
									attack->hitPartID() = 1750816991;
									break;
								}
								break;
							}

							attack->hitPositionLocal() = { -.1f, -.1f, 0 };
							attack->hitNormalLocal() = { 0, -1, 0 };
						}

					}
					else
					{

						if (m_settings::HeliHitboxOverride)
						{
							auto weakspots = AimbotTarget.m_player->weakspots();
							if (weakspots)
							{


								bool tail_alive = false;
								bool main_alive = false;
								for (int i = 0; i < weakspots->size; i++) {
									auto weakspot = weakspots->items[i];
									if (!weakspot)
										continue;


									auto health = weakspot->health();
									if (health > 0) {
										if (i == 0) {
											main_alive = true;
										}
										else {
											tail_alive = true;
										}
									}
								}

								if (tail_alive) {
									attack->hitBone() = 2699525250;
									attack->hitPartID() = 2306822461;
									attack->hitPositionLocal() = { .9f, -.4f, .1f };
									attack->hitNormalLocal() = { .9f, -.4f, .1f };
								}
								else if (main_alive) {
									attack->hitBone() = 224139191;
									attack->hitPartID() = 2306822461;
									attack->hitPositionLocal() = { .9f, -.4f, .1f };
									attack->hitNormalLocal() = { .9f, -.4f, .1f };
								}
							}
						}
					}
				}
			}
		}
	}

	return Hooks::PPA_WriteToStreamhk.get_original< decltype(&PPA_WriteToStream)>()(_This, Stream);
}