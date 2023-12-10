#pragma once

#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

#define M_PI_2 1.57079632679489661923

class Features {
public:
	static auto Instance() -> Features*
	{
		Features obj;
		return &obj;
	}
public:

	auto FindManipulationAngles(float MaxDesyncValue) -> void;
	auto FindBulletTPAngles(float MaxDesyncValue) -> void;
	Vector3 GetManipulationAngle();
	auto AutoShoot(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;
	auto FastBullet(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;
	auto BulletQueue(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;
	auto AutoReload(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void;

	auto RemoveCollision() -> void;
public:
	static inline AssemblyCSharp::BasePlayer* LocalPlayer;
	static inline Vector3 ManipulationAngle;
	static inline bool PointVisible = false;
	static inline Vector3 TempCachedPoint;
	static inline Vector3 CachedManipPoint;
	static inline uint64_t TargetID;
	static inline Vector3 BulletTPAngle;
	static inline bool PositionVisible = false;
	static inline Vector3 BTPSeperator;
	static inline AssemblyCSharp::BaseProjectile* BaseProjectile;

	//bullettp

	static inline Vector3 CachedBulletTPPosition;
	static inline bool BulletTPPointVisible = false;


	//magic cache
	static inline bool GeneratedPoints = false;
	static inline bool ConstantLOSCheck = false;
	static inline bool VerifiedLOSPoint = false;
	static inline Vector3 LOSPoint;
	static inline uint64_t LOSTargetID;

	//static inline bool HasLOS = false;

	//static
	inline static std::vector<Vector3> cachedPoints;
};

static inline Vector3 SavedWorldPos;
static inline Vector3 SavedHousePos;