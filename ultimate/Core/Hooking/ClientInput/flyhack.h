#pragma once

#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../../SDK/UnityEngine/UnityEngine.hpp"


inline float flyhackPauseTime;
inline float flyhackDistanceVertical = 0.f;
inline float flyhackDistanceHorizontal = 0.f;
inline bool TestFlying(AssemblyCSharp::BasePlayer* _This, Vector3 oldPos, Vector3 newPos)
{
	if (!InGame)
		return false;

	if (!IsAddressValid(_This))
		return false;

	if (const auto LocalPlayer = _This)
	{
		flyhackPauseTime = maxx(0.f, flyhackPauseTime - UnityEngine::Time::get_fixedDeltaTime());
		bool inAir = false;

		float radius = LocalPlayer->GetRadius();
		float height = LocalPlayer->GetHeight(false);

		Vector3 vector = (oldPos + newPos) * 0.5f;
		Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
		Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
		float radius2 = radius - 0.05f;

		bool a = UnityEngine::Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, RustStructs::Ignore);
		inAir = !a;

		if (inAir)
		{
			bool flag = false;

			Vector3 vector4 = newPos - oldPos;
			float num3 = Math::abs(vector4.y);
			float num4 = vector4.Magnitude2D();

			if (vector4.y >= 0.f) {
				flyhackDistanceVertical += vector4.y;
				flag = true;
			}
			if (num3 < num4) {
				flyhackDistanceHorizontal += num4;
				flag = true;
			}
			if (flag) {
				float num5 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num6 = _This->GetJumpHeight() + num5 + 3.2f;
				if (flyhackDistanceVertical > num6) {
					return true;
				}
				float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num8 = 5.f + num7 + 3.2f;
				if (flyhackDistanceHorizontal > num8) {
					return true;
				}
			}
		}
		else
		{
			flyhackDistanceHorizontal = 0.f;
			flyhackDistanceVertical = 0.f;
		}
	}
	return false;
}

inline bool CheckFlyhack(AssemblyCSharp::BasePlayer* _This, bool PreventFlyhack)
{
	if (!InGame)
		return false;

	if (!IsAddressValid(_This))
		return false;

	bool result;

	if (!IsAddressValid(_This->lastSentTick()))
		return false;

	if (!IsAddressValid(_This->get_transform()))
		return false;

	if (auto LocalPlayer = _This)
	{
		if (auto Transform = LocalPlayer->get_transform())
		{
			if (!_This->IsDead() && !_This->IsSleeper())
			{
				if (IsAddressValid(LocalPlayer->lastSentTick()) && IsAddressValid(LocalPlayer->get_transform()))
				{
					Vector3 oldPos = LocalPlayer->lastSentTick()->position();

					Vector3 modelPos = LocalPlayer->get_transform()->get_position();

					result = TestFlying(LocalPlayer, oldPos, modelPos);

					float num5 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num6 = _This->GetJumpHeight() + num5 + 3.2f;

					m_settings::MaxVerticalFlyhack = num6;
					m_settings::VerticalFlyhack = flyhackDistanceVertical;

					float num7 = maxx((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
					float num8 = 5.f + num7;

					m_settings::MaxHorisontalFlyhack = num8 + 3.2f;
					m_settings::HorisontalFlyhack = flyhackDistanceHorizontal;

					if (result && PreventFlyhack)
					{
						const auto last_sent_tick = LocalPlayer->lastSentTick();
						const auto player_movement = LocalPlayer->movement();
						if (IsAddressValid(player_movement) && IsAddressValid(last_sent_tick)) {
							auto LastSentTickPos = last_sent_tick->position();
							reinterpret_cast<AssemblyCSharp::BaseMovement*>(player_movement)->set_TargetMovement(Vector3());
							reinterpret_cast<AssemblyCSharp::BaseMovement*>(player_movement)->TeleportTo(Vector3(LastSentTickPos.x, LastSentTickPos.y - 0.001, LastSentTickPos.z), LocalPlayer);
							if (const auto rigid_body = player_movement->body()) {
								rigid_body->set_velocity(Vector3());
							}
						}
					}
					return result;
				}
			}
		}
	}

	return false;
}