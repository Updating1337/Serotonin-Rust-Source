#pragma once

#include "../../Includes/includes.hpp"
#include "../UnityEngine/UnityEngine.hpp"

struct ProjectileShoot_Shoot : Il2CppObject {
	IL2CPP_CLASS("ProjectileShoot.Projectile");
	IL2CPP_FIELD(int, projectileID);
	IL2CPP_FIELD(int, seed);

	IL2CPP_FIELD(Vector3, startPos);
	IL2CPP_FIELD(Vector3, startVel);
};

namespace ProtoBuf
{
	IL2CPP_NAME_SPACE("ProtoBuf");

	struct BasePlayer : Il2CppObject {
		IL2CPP_CLASS("BasePlayer");

		IL2CPP_FIELD(FPSystem::String*, name);

	};
	struct Entity : Il2CppObject {
		IL2CPP_CLASS("Entity");

		IL2CPP_FIELD(BasePlayer*, basePlayer);

	};
	struct CreateBuilding {
		IL2CPP_CLASS("CreateBuilding");


	};
	struct Stream {


	};
	struct Item : Il2CppObject {
		IL2CPP_CLASS("Item");

		IL2CPP_FIELD(uint64_t, skinid);

		static inline void(*WriteToStream_)(Item*, ProtoBuf::Stream*) = nullptr;

	};

	struct AutoTurret : Il2CppObject {
		IL2CPP_CLASS("AutoTurret");

		IL2CPP_FIELD(Vector3, aimPos);
		IL2CPP_FIELD(Vector3, aimDir);

	};

	struct PlayerProjectileUpdate : Il2CppObject {
		IL2CPP_CLASS("PlayerProjectileUpdate");


		IL2CPP_FIELD(int, projectileID);
		IL2CPP_FIELD(Vector3, curPosition);
		IL2CPP_FIELD(Vector3, curVelocity);
		IL2CPP_FIELD(float, travelTime);

		static inline void(*WriteToStream_)(PlayerProjectileUpdate*, ProtoBuf::Stream*) = nullptr;

	};

	struct PlayerProjectileRicochet : Il2CppObject {
		IL2CPP_CLASS("PlayerProjectileRicochet");
		IL2CPP_FIELD(int, projectileID);
		IL2CPP_FIELD(Vector3, hitPosition);
		IL2CPP_FIELD(Vector3, inVelocity);
		IL2CPP_FIELD(Vector3, outVelocity);
		IL2CPP_FIELD(Vector3, hitNormal);

		IL2CPP_FIELD(float, travelTime);
		IL2CPP_FIELD(bool, ShouldPool);
		IL2CPP_FIELD(bool, _disposed);

		static inline void(*WriteToStream_)(PlayerProjectileRicochet*, ProtoBuf::Stream*) = nullptr;

	};

	struct ProjectileShoot : Il2CppObject {
		IL2CPP_CLASS("ProjectileShoot");

		IL2CPP_FIELD(FPSystem::List<ProjectileShoot_Shoot*>*, projectiles);

		IL2CPP_FIELD(int, ammoType);

		static inline void(*WriteToStream_)(ProjectileShoot*, ProtoBuf::Stream*) = nullptr;

		//void WriteToStream(ProtoBuf::Stream* a1) {
		//	return spoof_call(WriteToStream_, this, a1);
		//}
	};

	struct MapNote : Il2CppObject
	{
		IL2CPP_CLASS("MapNote");
		IL2CPP_FIELD(Vector3, worldPosition);
	};

	struct Attack : Il2CppObject
	{
		IL2CPP_CLASS("Attack");
		IL2CPP_FIELD(Vector3, hitNormalLocal);
		IL2CPP_FIELD(Vector3, hitPositionLocal);
		IL2CPP_FIELD(Vector3, hitNormalWorld);
		IL2CPP_FIELD(Vector3, hitPositionWorld);

		IL2CPP_FIELD(Vector3, pointEnd);
		IL2CPP_FIELD(uint64_t, hitID);
		IL2CPP_FIELD(uint64_t, hitPartID);
		IL2CPP_FIELD(uint64_t, hitBone);
		IL2CPP_FIELD(uint64_t, hitMaterialID);
	};

	struct PlayerAttack : Il2CppObject
	{
		IL2CPP_CLASS("PlayerAttack");

		IL2CPP_FIELD(Attack*, attack);
		IL2CPP_FIELD(int, projectileID);


		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{
				
				return;
			}
		}
	};



	struct PlayerProjectileAttack : Il2CppObject
	{
		IL2CPP_CLASS("PlayerProjectileAttack");

		IL2CPP_FIELD(PlayerAttack*, playerAttack);
		IL2CPP_FIELD(float, hitDistance);
		IL2CPP_FIELD(Vector3, hitVelocity);
		IL2CPP_FIELD(float, travelTime);

		static inline void(*WriteToStream_)(PlayerProjectileAttack*, ProtoBuf::Stream*) = nullptr;
		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{
				
				return;
			}
		}
	};

	struct PlayerNameID : Il2CppObject
	{
		IL2CPP_CLASS("PlayerNameID");

		IL2CPP_FIELD(FPSystem::String*, username);
		IL2CPP_FIELD(uint64_t, userid);

	};


	struct BuildingPrivilege : Il2CppObject {
		IL2CPP_CLASS("BuildingPrivilege");

		IL2CPP_FIELD(FPSystem::List<ProtoBuf::PlayerNameID*>*, users);

	};
	struct NetworkableId {
		uint64_t Value; // 0x0
	};

	struct Minicopter : Il2CppObject
	{
		IL2CPP_CLASS("Minicopter");

		IL2CPP_FIELD(float, fuelFraction);
		IL2CPP_FIELD(NetworkableId*, fuelStorageID);

	};
	struct PlayerTeam : Il2CppObject
	{
		IL2CPP_CLASS("PlayerTeam");

		IL2CPP_FIELD(uint64_t, teamID);
	};
}