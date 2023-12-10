#include "EyeHack.hpp"
#include "../Features/Features.hpp"

float EyeHack::NoClipRadius(float margin)
{
	return 0.5f - margin;
}


bool EyeHack::TestNoClippingNew(Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool sphereCast, UnityEngine::Collider*& collider, bool vehicleLayer, AssemblyCSharp::BaseEntity* ignoreEntity)
{
	int num = 1537286401;
	if (!vehicleLayer)
	{
		num &= -8193;
	}

	Vector3 normalized = (newPos - oldPos).UnityNormalize();
	Vector3 vector = oldPos - normalized * backtracking;
	float magnitude = (newPos - vector).UnityMagnitude();
	UnityEngine::Ray ray(vector, normalized);
	UnityEngine::RaycastHit hitInfo;

	if (ignoreEntity == nullptr)
	{
		if (UnityEngine::Physics::Raycast(ray, hitInfo, magnitude + radius, num, RustStructs::QueryTriggerInteraction::Ignore))
		{
			collider = (UnityEngine::Collider*)hitInfo.m_Collider;
			return true;
		}
	}
	else
	{
		if (AssemblyCSharp::GamePhysics::Trace(ray, 0.f, hitInfo, magnitude + radius, num, RustStructs::QueryTriggerInteraction::Ignore, ignoreEntity))
		{
			collider = (UnityEngine::Collider*)hitInfo.m_Collider;
			return true;
		}
	}

	if (sphereCast)
	{
		if (AssemblyCSharp::GamePhysics::Trace(ray, radius, hitInfo, magnitude, num, RustStructs::QueryTriggerInteraction::Ignore, ignoreEntity))
		{
			collider = (UnityEngine::Collider*)hitInfo.m_Collider;
			return true;
		}
	}

	// No collision detected
	return false;
}
bool EyeHack::ValidateEyePos(AssemblyCSharp::BasePlayer* player, Vector3 eyePos, bool BulletTP)
{
	if (!IsAddressValid(player))
		return false;

	bool checkLineOfSight = true;
	bool flag = true;

	if (Vector3().IsNaNOrInfinity(eyePos) || !InGame || !player)
	{
		return false;
	}

	float num = 1.f + 0.5f;
	float eye_clientframes = 2.f;
	float eye_serverframes = 2.f;
	float num2 = eye_clientframes / 60.f;
	float num3 = eye_serverframes * Max3(UnityEngine::Time::get_deltaTime(), UnityEngine::Time::get_smoothDeltaTime(), UnityEngine::Time::get_fixedDeltaTime());
	float desyncTime = (UnityEngine::Time::get_realtimeSinceStartup() - AssemblyCSharp::LocalPlayer::get_Entity()->lastSentTickTime());
	float num4 = (desyncTime + num2 + num3) * num;

	float num8 = Math::abs(player->GetMountVelocity().y + player->GetParentVelocity().y);
	float num9 = player->BoundsPadding() + num4 * num8 + player->GetJumpHeight();
	float num10 = Math::abs(player->eyes()->get_position().y - eyePos.y);

	float num5 = player->MaxEyeVelocity() + player->GetParentVelocity().UnityMagnitude();
	float num6 = player->BoundsPadding() + num4 * num5;
	float num7 = Vector3().Distance(player->eyes()->get_position(), eyePos);
	if (!BulletTP)
	{
		if (num7 > num6)
		{
			return false;
		}
	}
	if (!BulletTP)
	{
		if (num10 > num9)
		{
			return false;
		}
	}


	if (checkLineOfSight)
	{
		int num11 = 2162688;
		num11 |= 8388608;

		Vector3 position2 = player->eyes()->get_position();
		float num12 = Vector3().Distance(position2, eyePos);

		float eye_noclip_cutoff = 0.06f;
		int noclip_protection = 3;
		UnityEngine::Collider* collider;

		if (num12 > eye_noclip_cutoff && TestNoClippingNew(position2, eyePos, NoClipRadius(0.21f), 0.01f, noclip_protection >= 2, collider, false, nullptr))
		{
			return false;
		}
		else if (num12 > 0.01f && TestNoClippingNew(position2, eyePos, 0.01f, 0.01f, noclip_protection >= 2, collider, false, nullptr))
		{
			return false;
		}
	}

	return flag;
}