#pragma once

#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"


class EyeHack {
public:
	static auto Instance() -> EyeHack*
	{
		EyeHack obj;
		return &obj;
	}
public:
	bool ValidateEyePos(AssemblyCSharp::BasePlayer* player, Vector3 eyePos, bool BulletTP = false);
	bool TestNoClippingNew(Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool sphereCast, UnityEngine::Collider*& collider, bool vehicleLayer = false, AssemblyCSharp::BaseEntity* ignoreEntity = nullptr);
	float NoClipRadius(float margin);
};