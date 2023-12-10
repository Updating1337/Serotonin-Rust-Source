#pragma once
#include "../UnityEngine/UnityEngine.hpp"
#include "../System/System.hpp"
#include "../../Includes/settings.hpp"
#include "../ProtoBuf/ProtoBuf.h"

struct weapon_stats_t {
	float initial_velocity;
	float gravity_modifier;
	float drag;
	float initial_distance;
};

enum AmmoType : int32_t {
	shotgun = -1685290200,
	shotgun_slug = -727717969,
	shotgun_fire = -1036635990,
	shotgun_handmade = 588596902,

	rifle_556 = -1211166256,
	rifle_556_hv = 1712070256,
	rifle_556_fire = 605467368,
	rifle_556_explosive = -1321651331,

	pistol = 785728077,
	pistol_hv = -1691396643,
	pistol_fire = 51984655,

	arrow_wooden = -1234735557,
	arrow_hv = -1023065463,
	arrow_fire = 14241751,
	arrow_bone = 215754713,

	nailgun_nails = -2097376851,

	rocket_hv = -1841918730,
	rocket_incen = 1638322904,
	rocket_basic = -742865266
};

enum weapon_types : int32_t {
	spear_stone = 1602646136,
	spear_wooden = 1540934679,
	hatchet = -1252059217,
	stonehatchet = -1583967946,
	pickaxe = -1302129395,
	stonepickaxe = 171931394,
	salvageaxe = -262590403,
	cleaver = -1978999529,
	hammer = -1506397857,
	icepick = -1780802565,
	sword = 1326180354,
	boneknife = 1814288539,
	butcherknife = -194509282,
	combatknife = 2040726127,
	rock = 963906841,
	snowball = -363689972
};

namespace Rust {
	IL2CPP_NAME_SPACE("Rust");


	struct DamageTypeList : Il2CppObject {
		IL2CPP_CLASS("DamageTypeList");


		float Total()
		{

			if (!this)return 0.f;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Total"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<float>(procedure, this);
			}


			return 0.f;
		}
	};
}

namespace AssemblyCSharp {
	static float crt_sqrt2(float number)
	{
		long        i;
		float       x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y; // floating point bit level hacking [sic]
		i = 0x5f3759df - (i >> 1); // Newton's approximation
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
		y = y * (threehalfs - (x2 * y * y)); // 2nd iteration

		return 1 / y;
	}
	inline float get_2d_dist(const Vector2& Src, const Vector3& Dst) {
		return crt_sqrt2(powFFFFFFFFFFFFFFFFFFFFFF(Src.x - Dst.x) + powFFFFFFFFFFFFFFFFFFFFFF(Src.y - Dst.y));
	}

	inline float get_fov(Vector3 Pos) {

		Vector3 ScreenPos = UnityEngine::Camera::get_main()->WorldToScreen(Pos);
		if (ScreenPos.IsZero())
			return 1000;

		return get_2d_dist(Vector2(screen_center.x, screen_center.y), ScreenPos);
	}

	struct InputMessage : Il2CppObject {
		IL2CPP_CLASS("InputMessage");

		IL2CPP_FIELD(Vector3, aimAngles);
		IL2CPP_FIELD(Vector3, mouseDelta);
	};

	struct InputState : Il2CppObject
	{
		IL2CPP_CLASS("InputState");

		IL2CPP_FIELD(InputMessage*, current);
		IL2CPP_FIELD(InputMessage*, previous);

		bool IsDown(RustStructs::BUTTON btn);
		bool WasJustPressed(RustStructs::BUTTON btn);
	};

	struct FacepunchBehaviour : UnityEngine::MonoBehaviour {
		IL2CPP_CLASS("FacepunchBehaviour");
	};

	struct BaseMonoBehaviour : FacepunchBehaviour {
		IL2CPP_CLASS("BaseMonoBehaviour");
	};

	struct BaseNetworkable : BaseMonoBehaviour
	{
		struct EntityRealm : Il2CppObject
		{
			using List = FPSystem::ListDictionary< std::uint32_t, BaseNetworkable* >;
			IL2CPP_FIELD(List*, entityList);
		};

		IL2CPP_CLASS("BaseNetworkable");
		IL2CPP_STATIC_FIELD(EntityRealm*, clientEntities);
		IL2CPP_FIELD(FPSystem::String*, _prefabName);
		IL2CPP_FIELD(FPSystem::String*, _prefabNameWithoutExtension);
		IL2CPP_PROPERTY(FPSystem::String*, PrefabName);
		IL2CPP_PROPERTY(FPSystem::String*, ShortPrefabName);

		IL2CPP_FIELD(std::uintptr_t*, net);

		IL2CPP_FIELD(uint64_t, prefabID);

		auto PlayerDestroyed() -> bool;
		bool PlayerValid();
	};

	struct Model : UnityEngine::MonoBehaviour
	{
		IL2CPP_FIELD(FPSystem::Array<FPSystem::String*>*, boneNames);
		IL2CPP_FIELD(FPSystem::Array<UnityEngine::Transform*>*, boneTransforms);

		IL2CPP_FIELD(UnityEngine::Transform*, headBone);
		IL2CPP_FIELD(UnityEngine::Transform*, rootBone);
		IL2CPP_FIELD(UnityEngine::Transform*, eyeBone);

	};


	struct ViewmodelSway : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("ViewmodelSway");

		IL2CPP_FIELD(float, positionalSwaySpeed);
		IL2CPP_FIELD(float, positionalSwayAmount);
		IL2CPP_FIELD(float, rotationSwaySpeed);
		IL2CPP_FIELD(float, rotationSwayAmount);
	};

	struct ViewmodelBob : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("ViewmodelBob");

		IL2CPP_FIELD(float, bobSpeedWalk);
		IL2CPP_FIELD(float, bobSpeedRun);
		IL2CPP_FIELD(float, leftOffsetRun);
		IL2CPP_FIELD(Vector4, bobAmountWalk);
		IL2CPP_FIELD(Vector4, bobAmountRun);
	};

	struct ViewModelLower : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("ViewModelLower");

		IL2CPP_FIELD(bool, lowerOnSprint);
		IL2CPP_FIELD(bool, lowerWhenCantAttack);
		IL2CPP_FIELD(bool, shouldLower);
	};

	struct ViewmodelPunch : Il2CppObject {
		IL2CPP_CLASS("ViewmodelPunch");


		IL2CPP_FIELD(float, punchDuration);
		IL2CPP_FIELD(float, punchStartTime);
		IL2CPP_FIELD(Vector3, punchDirection);

	};

	struct BaseViewModel : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("BaseViewModel");

		IL2CPP_STATIC_PROPERTY(BaseViewModel*, ActiveModel);

		IL2CPP_FIELD(ViewmodelSway*, sway);
		IL2CPP_FIELD(ViewModelLower*, lower);
		IL2CPP_FIELD(ViewmodelBob*, bob);
		IL2CPP_FIELD(bool, useViewModelCamera);
		IL2CPP_FIELD(UnityEngine::Animator*, animator);
		IL2CPP_FIELD(ViewmodelPunch*, punch);

	};

	struct BaseEntity : BaseNetworkable {
		IL2CPP_CLASS("BaseEntity");

		IL2CPP_FIELD(FPSystem::String*, _name);
		IL2CPP_FIELD(Model*, model);
		IL2CPP_FIELD(RustStructs::BaseEntity_Flags, flags);
		IL2CPP_FIELD(UnityEngine::Bounds, bounds);
		IL2CPP_FIELD(ULONG, skinID);

		void SetSkin(uint64_t skin_id);
		Vector3 ClosestPoint(Vector3 position);
		void ServerRPC(const char* msg);
		void SendSignalBroadcast(RustStructs::Signal a, char* str);
		auto GetParentVelocity() -> Vector3;
		void OnSignal(RustStructs::Signal a, char* str);
		auto GetWorldVelocity() -> Vector3;

		bool IsOnFire()
		{
			if (!this) return false;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsOnFire"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this);
			}


			return false;
		}
		Vector3 GetInheritedProjectileVelocity(Vector3 dir)
		{
			if (!this)return Vector3();
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetInheritedProjectileVelocity"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Vector3>(procedure, this, dir);
			}


			return Vector3();
		}

		Vector3 GetInheritedThrowVelocity(Vector3 dir)
		{
			if (!this)return Vector3();
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetInheritedThrowVelocity"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Vector3>(procedure, this, dir);
			}


			return Vector3();
		}


		float Distance(Vector3 pos)
		{
			if (!this)
				return 0.f;
			const auto is_dead = reinterpret_cast<float(*)(BaseEntity*, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("Distance"), 1)));
			return is_dead(this, pos);
		}

		void OnSkinRefreshStart()
		{
			if (!this)
				return;

			const auto is_dead = reinterpret_cast<void(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("OnSkinRefreshStart"), 0)));
			return is_dead(this);
		}

		void OnSkinRefreshEnd()
		{
			if (!this)
				return;

			const auto is_dead = reinterpret_cast<void(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("OnSkinRefreshEnd"), 0)));
			return is_dead(this);
		}

		void OnSkinChanged(uint64_t oldSkinID, uint64_t newSkinID)
		{
			if (!this)
				return;

			const auto is_dead = reinterpret_cast<void(*)(BaseEntity*, uint64_t, uint64_t)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("OnSkinChanged"), 2)));
			return is_dead(this, oldSkinID, newSkinID);
		}

		Vector3 PivotPoint()
		{
			if (!this)
				return Vector3();
			const auto is_dead = reinterpret_cast<Vector3(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("PivotPoint"), 0)));
			return is_dead(this);
		}

		float BoundsPadding()
		{
			if (!this)
				return 0.f;
			const auto is_dead = reinterpret_cast<float(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("BoundsPadding"), 0)));
			return is_dead(this);
		}

		float MaxVelocity()
		{
			if (!this)
				return 0.f;
			const auto is_dead = reinterpret_cast<float(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("MaxVelocity"), 0)));
			return is_dead(this);
		}
	};

	struct ResourceEntity : BaseEntity
	{
		IL2CPP_CLASS("ResourceEntity");

		IL2CPP_FIELD(bool, isKilled);
		IL2CPP_FIELD(float, health);
		IL2CPP_FIELD(float, startHealth);
	};


	struct CollectibleEntity : BaseEntity
	{
		IL2CPP_CLASS("CollectibleEntity");
	};

	struct PlayerNameID;

	struct AutoTurret : BaseEntity
	{
		IL2CPP_CLASS("AutoTurret");

		IL2CPP_FIELD(float, sightRange);
		IL2CPP_FIELD(Vector3, aimDir);
		IL2CPP_FIELD(UnityEngine::Transform*, muzzlePos);
		IL2CPP_FIELD(FPSystem::List<PlayerNameID*>*, authorizedPlayers);
		IL2CPP_FIELD(bool, wasTurning);
	};


	struct BearTrap : BaseEntity
	{
		IL2CPP_CLASS("BearTrap");
	};

	struct FlameTurret : BaseEntity
	{
		IL2CPP_CLASS("FlameTurret");
	};

	struct Landmine : BaseEntity
	{
		IL2CPP_CLASS("Landmine");
	};

	struct SamSite : BaseEntity
	{
		IL2CPP_CLASS("SamSite");
	};

	struct GamePhysics
	{
		IL2CPP_CLASS("GamePhysics");


		static auto LineOfSightRadius(Vector3 p0, Vector3 p1, int layerMask, float radius, float padding, BaseEntity* ignoreEntity) -> bool;
		static auto LineOfSightRadius_3(Vector3 p0, Vector3 p1, int layerMask, float padding, BaseEntity* ignoreEntity) -> bool;

		static auto Trace(UnityEngine::Ray ray, float radius, UnityEngine::RaycastHit hitInfo, float maxDistance, int layerMask, RustStructs::QueryTriggerInteraction triggerInteraction, BaseEntity* ignoreEntity) -> bool;
		static auto LineOfSight(Vector3 p0, Vector3 p1, int layerMask, BaseEntity* ignoreEntity) -> bool;
		static auto Trace2(UnityEngine::Ray* ray, float radius, UnityEngine::RaycastHit hitInfo, float maxDistance, int layerMask, RustStructs::QueryTriggerInteraction triggerInteraction, BaseEntity* ignoreEntity) -> bool;


		static bool Verify(UnityEngine::RaycastHit hit, AssemblyCSharp::BaseEntity* ignoreEntity)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Verify"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, hit, ignoreEntity);
			}


			return false;
		}
	};

	inline bool IsVisible(Vector3 source, Vector3 destination, int p1 = 0.2f) {

		int mask = m_settings::PierceMaterials ? 10551296 : 1503731969;

		return GamePhysics::LineOfSightRadius_3(source, destination, mask, p1, nullptr);
	}
	inline bool IsVisible_2(Vector3 source, Vector3 destination, int layerm, int p1 = 0.2f) {
		int mask = m_settings::PierceMaterials ? 10551296 : 1503731969;

		return GamePhysics::LineOfSightRadius_3(source, destination, mask, p1, nullptr);
	}
	inline bool IsVisible_3(Vector3 source, Vector3 destination) {
		int mask = m_settings::PierceMaterials ? 10551296 : 1503731969;

		return GamePhysics::LineOfSight(source, destination, mask, nullptr);
	}
	
	struct BaseCombatEntity : BaseEntity {
		IL2CPP_CLASS("BaseCombatEntity");

		IL2CPP_FIELD(float, _health);
		IL2CPP_FIELD(float, _maxHealth);
		IL2CPP_FIELD(RustStructs::LifeState, lifestate);

		bool IsDead();
		bool IsAlive();
	};

	struct SleepingBag : BaseCombatEntity
	{
		IL2CPP_CLASS("SleepingBag");

		IL2CPP_FIELD(unsigned long, deployerUserID);
	};

	enum PlayerModelMountPoses // TypeDefIndex: 1518
	{
		// Fields
		Chair = 0,
		Driving = 1,
		Horseback = 2,
		HeliUnarmed = 3,
		HeliArmed = 4,
		HandMotorBoat = 5,
		MotorBoatPassenger = 6,
		SitGeneric = 7,
		SitRaft = 8,
		StandDrive = 9,
		SitShootingGeneric = 10,
		SitMinicopter_Pilot = 11,
		SitMinicopter_Passenger = 12,
		ArcadeLeft = 13,
		ArcadeRight = 14,
		SitSummer_Ring = 15,
		SitSummer_BoogieBoard = 16,
		SitCarPassenger = 17,
		SitSummer_Chair = 18,
		SitRaft_NoPaddle = 19,
		Sit_SecretLab = 20,
		Sit_Workcart = 21,
		Sit_Cardgame = 22,
		Sit_Crane = 23,
		Sit_Snowmobile_Shooting = 24,
		Sit_RetroSnowmobile_Shooting = 25,
		Driving_Snowmobile = 26,
		ZiplineHold = 27,
		Sit_Locomotive = 28,
		Sit_Throne = 29,
		Standing = 128
	};

	struct CargoShip {
		IL2CPP_CLASS("CargoShip");
	};


	struct BaseMountable : BaseCombatEntity
	{
		IL2CPP_CLASS("BaseMountable");

		IL2CPP_FIELD(bool, canWieldItems);
		IL2CPP_FIELD(PlayerModelMountPoses, mountPose);
	};

	struct BaseHeliWeakSpot : Il2CppObject {
		IL2CPP_CLASS("PatrolHelicopter.weakspot");


		IL2CPP_FIELD(float, maxHealth);
		IL2CPP_FIELD(float, health);

	};

	struct PatrolHelicopter : BaseCombatEntity {
		IL2CPP_CLASS("PatrolHelicopter");
		IL2CPP_FIELD(FPSystem::c_system_array< BaseHeliWeakSpot*>*, weakspots);
		IL2CPP_FIELD(UnityEngine::GameObject*, mainRotor);


		//IL2CPP_FIELD(FPSystem::Array< BaseHeliWeakSpot*>*, weakspots);

	};

	struct TranslatePhrase : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TranslatePhrase");
		IL2CPP_FIELD(FPSystem::String*, english);
	};

	struct Item;
	struct ItemDefinition : UnityEngine::MonoBehaviour
	{

		IL2CPP_CLASS("ItemDefinition");
		IL2CPP_FIELD(std::int32_t, itemid);
		IL2CPP_FIELD(FPSystem::String*, shortname);
		IL2CPP_FIELD(RustStructs::ItemCategory, category);
		IL2CPP_FIELD(TranslatePhrase*, displayName);

		FPSystem::String* GetDisplayName(Item* item);
		UnityEngine::Sprite* FindIconSprite(int id);

	};
	struct BaseEntity;
	struct ViewModel : BaseMonoBehaviour
	{
		IL2CPP_CLASS("ViewModel");
		IL2CPP_FIELD(BaseEntity*, instance);
		void Play(const char* name, int layer);
	};
	struct BasePlayer;

	struct HeldEntityPunchEntry : Il2CppObject {
		IL2CPP_CLASS("HeldEntity.PunchEntry");


		IL2CPP_FIELD(Vector3, amount);
		IL2CPP_FIELD(float, duration);
		IL2CPP_FIELD(float, startTime);
		IL2CPP_FIELD(Vector3, amountAdded);

	};

	struct HeldEntity : BaseEntity
	{
		IL2CPP_CLASS("HeldEntity");
		IL2CPP_FIELD(ViewModel*, viewModel);
		IL2CPP_FIELD(Vector3, punchAdded);
		IL2CPP_FIELD(FPSystem::List<HeldEntityPunchEntry*>*, _punches);

		IL2CPP_FIELD(float, lastPunchTime);

		BasePlayer* GetOwnerPlayer()
		{
			if (!this)
				return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetOwnerPlayer"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<BasePlayer*>(procedure, this);
			}
			else
			{

				return {};
			}
		}
	};

	struct AttackEntity : HeldEntity
	{
		IL2CPP_CLASS("AttackEntity");
		IL2CPP_FIELD(float, aiAimSwayOffset);
		IL2CPP_FIELD(float, aiAimCone);
		IL2CPP_FIELD(float, repeatDelay);
		IL2CPP_FIELD(float, timeSinceDeploy);
		IL2CPP_FIELD(float, deployDelay);
		IL2CPP_FIELD(float, nextAttackTime);

		ItemDefinition* GetOwnerItemDefinition();

		bool IsFullyDeployed();
		bool HasAttackCooldown();
		auto StartAttackCooldown(float coolDown) -> void;
	};

	struct ResourceDispenserGatherPropertyEntry : Il2CppObject {
		IL2CPP_CLASS("ResourceDispenser.GatherPropertyEntry");

		IL2CPP_FIELD(float, gatherDamage);
	};

	struct ResourceDispenserGatherProperties : Il2CppObject {
		IL2CPP_CLASS("ResourceDispenser.GatherProperties");

		IL2CPP_FIELD(ResourceDispenserGatherPropertyEntry*, Tree);
		IL2CPP_FIELD(ResourceDispenserGatherPropertyEntry*, Ore);
		IL2CPP_FIELD(ResourceDispenserGatherPropertyEntry*, Flesh);

	};
	struct DamageProperties;
	struct ItemModProjectile;
	struct HitTest;
	struct BasePlayer;
	struct BaseMelee : AttackEntity {
		IL2CPP_CLASS("BaseMelee");

		IL2CPP_FIELD(float, maxDistance);
		IL2CPP_FIELD(float, attackRadius);

		IL2CPP_FIELD(DamageProperties*, damageProperties);
		IL2CPP_FIELD(ResourceDispenserGatherProperties*, gathering);
		IL2CPP_FIELD(bool, canThrowAsProjectile);

		uintptr_t CreateProjectile(const char* prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity)
		{
			if (!this)
				return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CreateProjectile"),4);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<uintptr_t>(procedure, this, CIl2Cpp::il2cpp_string_new(prefabPath), pos, forward, velocity);
			}
			else
			{

				return {};
			}
		}

		void DoThrow();
		void ProcessAttack(HitTest* hit);
		void ClientAttack();
		Vector3 GetInheritedVelocity(BasePlayer* player, Vector3 dir);

		/*	void DoThrowRecreation()
			{
				if (!this->canThrowAsProjectile())
					return;

				auto ownerPlayer = this->GetOwnerPlayer();
				if (!ownerPlayer)
					return;

				auto Item = this->GetOwnerItemDefinition();
				if (!Item)
					return;

				ItemModProjectile* component = Item->GetComponent<AssemblyCSharp::ItemModProjectile>(FPSystem::Type::ItemModProjectile());
				if (!component)
					return;


			}*/
	};


	struct RecoilProperties : UnityEngine::Object
	{
		IL2CPP_CLASS("RecoilProperties");

		IL2CPP_FIELD(RecoilProperties*, newRecoilOverride);
		IL2CPP_FIELD(float, recoilYawMin);
		IL2CPP_FIELD(float, recoilYawMax);
		IL2CPP_FIELD(float, recoilPitchMin);
		IL2CPP_FIELD(float, recoilPitchMax);
		IL2CPP_FIELD(float, aimconeCurveScale);

		IL2CPP_FIELD(float, timeToTakeMin);
		IL2CPP_FIELD(float, timeToTakeMax);
		IL2CPP_FIELD(float, ADSScale);
		IL2CPP_FIELD(float, movementPenalty);
		IL2CPP_FIELD(float, clampPitch);
	};
	struct DamageProperties : Il2CppObject {
		IL2CPP_CLASS("DamageProperties");

	};

	struct BaseEntity;
	struct Projectile;

	

	struct HitInfo : Il2CppObject {
		IL2CPP_CLASS("HitInfo");
		IL2CPP_FIELD(Rust::DamageTypeList*, damageTypes);

		IL2CPP_FIELD(float, ProjectileDistance);
		IL2CPP_FIELD(float, ProjectileIntegrity);
		IL2CPP_FIELD(float, ProjectileTravelTime);
		IL2CPP_FIELD(Vector3, ProjectileVelocity);
		IL2CPP_FIELD(bool, DidHit);
		IL2CPP_FIELD(Projectile*, ProjectilePrefab);
		IL2CPP_FIELD(bool, IsPredicting);
		IL2CPP_FIELD(AttackEntity*, WeaponPrefab);
		IL2CPP_FIELD(bool, DoDecals);

		IL2CPP_FIELD(uint64_t, HitMaterial);
		IL2CPP_FIELD(uint64_t, HitBone);
		IL2CPP_FIELD(uint64_t, ProjectileID);
		IL2CPP_FIELD(BaseEntity*, Initiator);
		IL2CPP_FIELD(BaseEntity*, HitEntity);

		IL2CPP_FIELD(Vector3, HitPositionWorld);
		IL2CPP_FIELD(Vector3, PointStart);

		Vector3 PositionOnRay(Vector3 pos)
		{
			if (!this)
				return Vector3();

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("PositionOnRay"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Vector3>(procedure, this, pos);
			}
			else
			{

				return Vector3();
			}
		}

		void LoadFromAttack(ProtoBuf::Attack* atk, bool serverSide)
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("LoadFromAttack"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, atk, serverSide);
			}
			else
			{

				return;
			}
		}
	};

	struct HitTest : Il2CppObject {
		IL2CPP_CLASS("HitTest");
		IL2CPP_FIELD(Il2CppString*, HitMaterial);
		IL2CPP_FIELD(bool, DidHit);
		IL2CPP_FIELD(bool, BestHit);

		IL2CPP_FIELD(UnityEngine::Ray, AttackRay);
		IL2CPP_FIELD(float, Radius);
		IL2CPP_FIELD(float, Forgiveness);
		IL2CPP_FIELD(float, MaxDistance);
		IL2CPP_FIELD(float, HitDistance);
		IL2CPP_FIELD(int, type);
		IL2CPP_FIELD(int, HitPart);
		IL2CPP_FIELD(UnityEngine::Collider*, collider);
		IL2CPP_FIELD(UnityEngine::GameObject*, gameObject);

		IL2CPP_FIELD(BaseEntity*, HitEntity);
		IL2CPP_FIELD(BaseEntity*, ignoreEntity);

		IL2CPP_FIELD(Vector3, HitPoint);
		IL2CPP_FIELD(Vector3, HitNormal);
		IL2CPP_FIELD(DamageProperties*, damageProperties);

		IL2CPP_FIELD(UnityEngine::Transform*, HitTransform);



		Vector3 HitPointWorld();
		Vector3 HitNormalWorld();

		ProtoBuf::Attack* BuildAttackMessage(BasePlayer* attackingEntity)
		{

			if (!this)
				return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("BuildAttackMessage"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<ProtoBuf::Attack*>(procedure, this, attackingEntity);
			}
			else
			{

				return {};
			}
		}


		void Clear()
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Clear"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}
		}


	};

	class Object {
	public:

	};
	struct GameManifest
	{
		IL2CPP_CLASS("GameManifest");

		static Object* GUIDToObject(FPSystem::String* guid);
	};
	template<typename T = Object>
	class ResourceRef {
	public:
		T* Get() {
			if (!this) return nullptr;
			FPSystem::String* guid = *reinterpret_cast<FPSystem::String**>(this + 0x10);
			T* _cachedObject = (T*)GameManifest::GUIDToObject(guid);

			return _cachedObject;
		}
	};
	struct ItemModProjectile : public UnityEngine::Component {
		IL2CPP_CLASS("ItemModProjectile");
		IL2CPP_FIELD(ResourceRef<UnityEngine::GameObject>*, projectileObject);
		IL2CPP_FIELD(float, projectileVelocity);
		IL2CPP_FIELD(float, projectileSpread);
		IL2CPP_FIELD(float, projectileVelocitySpread);

		IL2CPP_FIELD(int, numProjectiles);

		float GetRandomVelocity();
		float GetMinVelocity();
		float GetMaxVelocity();

	};
	struct BasePlayer;

	struct RaycastHitEx : Il2CppObject {
		IL2CPP_CLASS("RaycastHitEx");


		static BaseEntity* GetEntity(UnityEngine::RaycastHit  hit)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetEntity"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<BaseEntity*>(procedure, hit);
			}
			else
			{

				return {};
			}
		}
	};

	struct ServerProjectile : BaseMonoBehaviour
	{
		IL2CPP_CLASS("ServerProjectile");


		IL2CPP_FIELD(Vector3, initialVelocity);
		IL2CPP_FIELD(float, drag);
		IL2CPP_FIELD(float, gravityModifier);
		IL2CPP_FIELD(float, speed);
		IL2CPP_FIELD(float, scanRange);
		IL2CPP_FIELD(float, radius);

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}
	};

	struct Projectile : BaseMonoBehaviour
	{
		IL2CPP_CLASS("Projectile");
		IL2CPP_FIELD(float, thickness);
		IL2CPP_FIELD(Vector3, currentPosition);
		IL2CPP_FIELD(Vector3, sentPosition);
		IL2CPP_FIELD(bool, invisible);

		IL2CPP_FIELD(Vector3, currentVelocity);
		IL2CPP_FIELD(Vector3, initialVelocity);
		IL2CPP_FIELD(Vector3, previousPosition);
		IL2CPP_FIELD(Vector3, previousVelocity);
		IL2CPP_FIELD(HitTest*, hitTest);
		IL2CPP_FIELD(Projectile*, sourceProjectilePrefab);

		IL2CPP_FIELD(float, traveledTime);
		IL2CPP_FIELD(float, traveledDistance);
		IL2CPP_FIELD(float, gravityModifier);
		IL2CPP_FIELD(float, drag);
		IL2CPP_FIELD(float, closeFlybyDistance);
		IL2CPP_FIELD(float, tumbleSpeed);
		IL2CPP_FIELD(float, maxDistance);
		IL2CPP_FIELD(bool, createDecals);
		IL2CPP_FIELD(Vector3, tumbleAxis);
		IL2CPP_FIELD(float, previousTraveledTime);
		IL2CPP_FIELD(float, launchTime);
		IL2CPP_FIELD(Vector3, swimScale);
		IL2CPP_FIELD(float, penetrationPower);
		IL2CPP_FIELD(int, seed);
		IL2CPP_FIELD(float, flybySoundDistance);

		IL2CPP_FIELD(int, projectileID);
		IL2CPP_FIELD(ItemModProjectile*, mod);
		IL2CPP_FIELD(float, initialDistance);
		//IL2CPP_FIELD(ItemModProjectile*, mod);
		IL2CPP_FIELD(float, integrity);
		IL2CPP_FIELD(BasePlayer*, owner);
		IL2CPP_FIELD(bool, isRicochet);
		IL2CPP_FIELD(AttackEntity*, sourceWeaponPrefab);
		IL2CPP_FIELD(DamageProperties*, damageProperties);
		IL2CPP_FIELD(float, ricochetChance);

		void DoHitSpoof(HitTest* test, Vector3 point, Vector3 normal)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DoHit"), 3);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, test, point, normal);
			}
			else
			{

				return;
			}
		}

		void DoMovement(float deltaTime)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DoMovement"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, deltaTime);
			}
			else
			{

				return;
			}
		}

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}
		}

		bool IsAlive();
		void UpdateVelocity(float deltaTime);
		bool DoRicochet(HitTest* test, Vector3 point, Vector3 normal);
		bool DoHit(HitTest* test, Vector3 point, Vector3 normal);
		auto Retire() -> void;
		auto get_isAlive() -> bool;
		auto isAuthoritative() -> bool;

		static bool IsWaterMaterial(Il2CppString* name);

		bool Reflect(int seed, Vector3 point, Vector3 normal);

		void FixedUpdate()
		{

			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("FixedUpdate"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}


		void Update()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Update"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}

		void AdjustVelocity(Vector3 delta)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("AdjustVelocity"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, delta);
			}


			return;
		}

		void Launch()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Launch"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}

		float CalculateEffectScale()
		{
			if (!this) return 0.f;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CalculateEffectScale"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<float>(procedure, this);
			}


			return 0.f;
		}

		void DoFlybySound()
		{
			if (!this)return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DoFlybySound"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}

		void SetEffectScale(float eScale)
		{
			if (!this)return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetEffectScale"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, eScale);
			}


			return;
		}

	};


	enum AmmoTypes // TypeDefIndex: 13573
	{
		// Fields
		PISTOL_9MM = 1,
		RIFLE_556MM = 2,
		SHOTGUN_12GUAGE = 4,
		BOW_ARROW = 8,
		HANDMADE_SHELL = 16,
		ROCKET = 32,
		NAILS = 64,
		AMMO_40MM = 128,
		SNOWBALL = 256,
		SPEARGUN_BOLT = 512,
		TORPEDO = 1024,
		MLRS_ROCKET = 2048,
		MISSILE_SEEKING = 4096
	};

	struct BaseProjectileMagazineDefinition : Il2CppObject {
		IL2CPP_CLASS("BaseProjectile.Magazine.Definition");

		IL2CPP_FIELD(AmmoTypes, ammoTypes);
	};

	struct Magazine : AttackEntity {

		IL2CPP_CLASS("BaseProjectile.Magazine");
		IL2CPP_FIELD(ItemDefinition*, ammoType);
		IL2CPP_FIELD(BaseProjectileMagazineDefinition*, definition);

		IL2CPP_FIELD(int, contents);
		IL2CPP_FIELD(int, capacity);

		bool CanReload(BasePlayer* owner)
		{
			if (!this)return false;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CanReload"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this, owner);
			}


			return false;
		}
	};

	struct BaseProjectile : AttackEntity
	{
		IL2CPP_CLASS("BaseProjectile");
		IL2CPP_FIELD(bool, automatic);
		IL2CPP_FIELD(bool, aiming);

		IL2CPP_FIELD(float, reloadTime);
		IL2CPP_FIELD(float, stancePenalty);
		IL2CPP_FIELD(float, reloadPressTime);
		IL2CPP_FIELD(float, aimconePenalty);

		IL2CPP_FIELD(float, sightAimConeScale);
		IL2CPP_FIELD(float, sightAimConeOffset);

		IL2CPP_FIELD(float, hipAimConeScale);
		IL2CPP_FIELD(float, hipAimConeOffset);


		IL2CPP_FIELD(float, aimCone);
		IL2CPP_FIELD(float, hipAimCone);

		IL2CPP_FIELD(float, aimconePenaltyRecoverTime);
		IL2CPP_FIELD(float, aimconePenaltyRecoverDelay);


		IL2CPP_FIELD(float, aimConePenaltyMax);
		IL2CPP_FIELD(float, stancePenaltyScale);
		IL2CPP_FIELD(float, aimconePenaltyPerShot);
		IL2CPP_FIELD(float, deployDelay);
		IL2CPP_FIELD(float, animationDelay);
		IL2CPP_FIELD(UnityEngine::Transform*, MuzzlePoint);
		IL2CPP_FIELD(FPSystem::List<Projectile*>*, createdProjectiles);
		IL2CPP_FIELD(RecoilProperties*, recoil);
		IL2CPP_FIELD(float, aimSway);
		IL2CPP_FIELD(float, aimSwaySpeed);
		IL2CPP_FIELD(Magazine*, primaryMagazine);
		IL2CPP_FIELD(float, projectileVelocityScale);
		IL2CPP_FIELD(float, lastShotTime);
		IL2CPP_FIELD(float, nextReloadTime);
		IL2CPP_FIELD(bool, triggerReady);
		IL2CPP_FIELD(bool, manualCycle);
		IL2CPP_FIELD(bool, needsCycle);
		IL2CPP_PROPERTY(bool, isSemiAuto);
		IL2CPP_FIELD(bool, UsingInfiniteAmmoCheat);
		IL2CPP_FIELD(bool, isReloading);
		IL2CPP_FIELD(bool, fractionalReload);
		IL2CPP_FIELD(bool, isCycling);

		weapon_stats_t get_stats(int32_t weapon_id) {
			const auto primary_magazine = this->primaryMagazine();

			if (!primary_magazine)
				return weapon_stats_t{ (1000) };

			float velocity = (1000);
			float gravity_modifier = (1);
			float drag = (.001f);
			float distance = (0);

			auto velocity_scale = (1);
			bool scale_velocity = false;

			const auto ammo_definition = *reinterpret_cast<uintptr_t*>((uintptr_t)primary_magazine + 0x20);
			//auto ammo_definition = primary_magazine->ammoType();//*reinterpret_cast<uintptr_t*>((uintptr_t)primary_magazine + 0x20);
			if (ammo_definition) {
				// itemid
				//const auto ammo_id = ammo_definition->itemid;//*reinterpret_cast<int32_t*>((uintptr_t)ammo_definition + 0x18);
				const auto ammo_id = *reinterpret_cast<int32_t*>((uintptr_t)ammo_definition + 0x18);

				if (ammo_id)
				{
					switch (ammo_id) {
					case rocket_basic:
						drag = (0.1f);
						gravity_modifier = (10.f);
						break;
					case rocket_hv:
						drag = (0.f);
						gravity_modifier = (0.f);
						break;
						break;
					case rocket_incen:
						drag = (0.1f);
						gravity_modifier = (10.f);
						break;
						break;
					case shotgun:
						velocity = (225);
						drag = (1);
						distance = (3);
						break;
					case shotgun_slug:
						velocity = (225);
						drag = (1);
						distance = (10);
						break;
					case shotgun_fire:
						velocity = 100;
						drag = 1;
						distance = 3;
						break;
					case shotgun_handmade:
						velocity = 100;
						drag = 1;
						distance = 0;
						break;
					case rifle_556:
						velocity = 375;
						drag = .6;
						distance = 15;
						break;
					case rifle_556_hv:
						velocity = 450;
						drag = .6;
						distance = 15;
						break;
					case rifle_556_fire:
						velocity = 225;
						drag = .6;
						distance = 15;
						break;
					case rifle_556_explosive:
						velocity = 225;
						gravity_modifier = 1.25;
						drag = .6;
						distance = 15;
						break;
					case pistol:
						velocity = 300;
						drag = .7;
						distance = 15;
						break;
					case pistol_hv:
						velocity = 400;
						drag = .7;
						distance = 15;
						break;
					case pistol_fire:
						velocity = 225;
						drag = .7;
						distance = 15;
						break;
					case arrow_wooden:
						velocity = 50;
						gravity_modifier = .75;
						drag = .005;
						break;
					case arrow_hv:
						velocity = 80;
						gravity_modifier = .5;
						drag = .005;
						break;
					case arrow_fire:
						velocity = 40;
						gravity_modifier = 1;
						drag = .01;
						break;
					case arrow_bone:
						velocity = 45;
						gravity_modifier = .75;
						drag = .01;
						break;
					case nailgun_nails:
						velocity = 50;
						gravity_modifier = .75;
						drag = .005;
						break;
					}
				}

				scale_velocity = true;
				velocity_scale =
					GetProjectileVelocityScale(false);
			}

			switch (weapon_id) {
			case spear_wooden:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case spear_stone:
				velocity = 30;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case hatchet:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case stonehatchet:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case pickaxe:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case stonepickaxe:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case salvageaxe:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case cleaver:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case hammer:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case icepick:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case sword:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case boneknife:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case butcherknife:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case combatknife:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case rock:
				velocity = 15;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			case snowball:
				velocity = 25;
				scale_velocity = false;
				gravity_modifier = 2;
				drag = .1f;
				distance = .25f;
				break;
			}

			if (scale_velocity && (velocity_scale != 0))
				velocity *= velocity_scale;

			return { velocity, gravity_modifier, drag, distance };
		}


		bool HasReloadCooldown();
		float GetProjectileVelocityScale(bool max);

		void ShotFired();
		void BeginCycle();
		void DidAttackClientside();
		void UpdateAmmoDisplay();
		void LaunchProjectile();

		void DoAttack();

		float GetAimCone()
		{
			if (!this) return 0.f;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetAimCone"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<float>(procedure, this);
			}
			else
			{

				return 0.f;
			}

		}

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}
		}

		void LaunchProjectileClientside(ItemDefinition* ammo, int projectileCount, float projSpreadaimCone)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("LaunchProjectileClientside"), 3);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, ammo, projectileCount, projSpreadaimCone);
			}
			else
			{
				return;
			}
		}

		void LaunchRecreation()
		{
			if (!this->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
				return;

			ItemModProjectile* component = this->primaryMagazine()->ammoType()->GetComponent<ItemModProjectile>(FPSystem::Type::ItemModProjectile());
			if (!component)
				return;

			this->LaunchProjectileClientside(this->primaryMagazine()->ammoType(), component->numProjectiles(), this->aimCone());
		}

		void DoAttackRecreation()
		{
			if (!this->IsA(AssemblyCSharp::BaseProjectile::StaticClass()))
				return;
			//if (this->IsA(AssemblyCSharp::BaseLauncher::StaticClass()))
			//	return;

			auto ownerPlayer = this->GetOwnerPlayer();
			if (!ownerPlayer)
				return;

			if (this->HasReloadCooldown())
				return;

			if (this->timeSinceDeploy() < this->deployDelay())
				return;

			this->triggerReady() = true;

			if (this->manualCycle() && this->needsCycle())
			{
				this->BeginCycle();
				return;
			}

			if (this->HasAttackCooldown())
			{
				return;
			}

			if (this->get_isSemiAuto())
			{
				this->triggerReady() = false;
			}
			if (this->primaryMagazine()->contents() <= 0)
			{
				return;
			}

			this->SendSignalBroadcast(RustStructs::Signal::Attack, XS(""));
		
			this->primaryMagazine()->contents()--;

			this->LaunchProjectile();
			this->UpdateAmmoDisplay();
			this->ShotFired();
			this->DidAttackClientside();
			if (!this->manualCycle())
			{
				this->BeginCycle();
				return;
			}
			this->needsCycle() = true;
		}
	};
	struct TimedExplosive : BaseMelee {
		IL2CPP_CLASS("TimedExplosive");

	};

	struct JackHammer : BaseMelee {
		IL2CPP_CLASS("JackHammer");

	};
	struct TorchWeapon : BaseMelee {
		IL2CPP_CLASS("TorchWeapon");

		IL2CPP_FIELD(bool, ExtinguishUnderwater);
	};

	struct ThrownWeapon : AttackEntity {
		IL2CPP_CLASS("ThrownWeapon");
		IL2CPP_FIELD(float, maxThrowVelocity);
		IL2CPP_FIELD(float, tumbleVelocity);
		IL2CPP_FIELD(Vector3, overrideAngle);

		Vector3 GetInheritedVelocity(BasePlayer* ply, Vector3 dir);
	};

	struct FlameThrower : AttackEntity {
		IL2CPP_CLASS("FlameThrower");

	};
	struct BowWeapon : BaseProjectile {
		IL2CPP_CLASS("BowWeapon");

		IL2CPP_FIELD(bool, attackReady);
		IL2CPP_FIELD(float, arrowBack);


		void TryReload()
		{
			if (!this)return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("TryReload"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}
	};

	struct SnowballGun : AttackEntity {
		IL2CPP_CLASS("SnowballGun");


	};

	struct CompoundBowWeapon : AttackEntity {
		IL2CPP_CLASS("CompoundBowWeapon");

		IL2CPP_FIELD(float, stringHoldDurationMax);
		IL2CPP_FIELD(float, movementPenalty);
		IL2CPP_FIELD(float, currentHoldProgress);
	};


	struct CrossbowWeapon : AttackEntity {
		IL2CPP_CLASS("CrossbowWeapon");

	};

	struct FlintStrikeWeapon : BaseProjectile {
		IL2CPP_CLASS("FlintStrikeWeapon");

		IL2CPP_FIELD(float, successFraction);
		IL2CPP_FIELD(bool, _isStriking);
		IL2CPP_FIELD(bool, _didSparkThisFrame);
		IL2CPP_FIELD(int, strikes);


	};

	struct Chainsaw : BaseMelee {
		IL2CPP_CLASS("Chainsaw");

	};

	struct Tugboat : BaseCombatEntity {
		IL2CPP_CLASS("Tugboat");

	};

	struct MiniCopter : BaseCombatEntity {
		IL2CPP_CLASS("MiniCopter");

		IL2CPP_FIELD(float, rotorSpeed);
		IL2CPP_FIELD(float, cachedPitch);
		IL2CPP_FIELD(float, cachedYaw);
		IL2CPP_FIELD(float, cachedRoll);
	};

	struct AttackHelicopter : BaseCombatEntity {
		IL2CPP_CLASS("AttackHelicopter");
	};

	struct MedicalTool : AttackEntity {
		IL2CPP_CLASS("MedicalTool");

		IL2CPP_FIELD(float, healDurationSelf);
	};

	struct BaseLauncher : AttackEntity {
		IL2CPP_CLASS("BaseLauncher");

	};
	struct BaseVehicle : BaseEntity {
		IL2CPP_CLASS("BaseVehicle");

	};

	struct Parachute : BaseVehicle {
		IL2CPP_CLASS("Parachute");

		IL2CPP_FIELD(float, ConstantForwardForce);
		IL2CPP_FIELD(float, ForwardTiltAcceleration);
		IL2CPP_FIELD(float, TurnForce);

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}
	};

	struct Item : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("Item");
		IL2CPP_FIELD(std::uint32_t, uid);
		IL2CPP_FIELD(ItemDefinition*, info);
		IL2CPP_FIELD(HeldEntity*, heldEntity);
		IL2CPP_FIELD(ULONG, skin);
		IL2CPP_FIELD(std::uint32_t, amount);
		IL2CPP_FIELD(float, _condition);
		IL2CPP_FIELD(float, _maxCondition);

		//template<typename T = void*>
		//T* HeldEntityCast() {
		//	if (!IsAddressValid(this)) return nullptr;
		//	return *reinterpret_cast<T**>(this->heldEntity());
		//}


		void MarkDirty()
		{
			if (!this)return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("MarkDirty"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}

		BaseEntity* GetHeldEntity();

		IL2CPP_PROPERTY(UnityEngine::Sprite*, iconSprite);

		FPSystem::String* GetItemName();
		wchar_t* GetItemName2();
		wchar_t* get_weapon_name();
		FPSystem::String* GetItemShortName();

		void SetSkin(uint64_t skin_id);
	};
	struct TOD_AtmosphereParameters : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_AtmosphereParameters");

		IL2CPP_FIELD(float, RayleighMultiplier); //Intensity of the atmospheric Rayleigh scattering
		IL2CPP_FIELD(float, MieMultiplier); //Intensity of the atmospheric Mie scattering
		IL2CPP_FIELD(float, Brightness); //Overall brightness of the atmosphere
		IL2CPP_FIELD(float, Contrast); //Overall contrast of the atmosphere
		IL2CPP_FIELD(float, Directionality); //Directionality factor that determines the size of the glow around the sun
		IL2CPP_FIELD(float, Fogginess); //Density of the fog covering the sky
	};

	struct Gradient : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("Gradient");

		IL2CPP_FIELD(Vector4, m_Ptr); //0x10
	};

	struct TOD_DayParameters : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_DayParameters");

		IL2CPP_FIELD(Gradient*, SkyColor); //Intensity of the light source
		IL2CPP_FIELD(float, LightIntensity); //Intensity of the light source
		IL2CPP_FIELD(float, ShadowStrength); //Opacity of the shadows dropped by the light source
		IL2CPP_FIELD(float, AmbientMultiplier); //Brightness multiplier of the ambient light
		IL2CPP_FIELD(float, ReflectionMultiplier); //Brightness multiplier of the reflection probe

	};

	struct TOD_NightParameters : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_NightParameters");

		IL2CPP_FIELD(float, LightIntensity); //Intensity of the light source
		IL2CPP_FIELD(float, ShadowStrength); //Opacity of the shadows dropped by the light source
		IL2CPP_FIELD(float, AmbientMultiplier); //Brightness multiplier of the ambient light
		IL2CPP_FIELD(float, ReflectionMultiplier); //Brightness multiplier of the reflection probe

		IL2CPP_FIELD(uintptr_t, AmbientColor); //Brightness multiplier of the reflection probe
		IL2CPP_FIELD(uintptr_t, CloudColor); //Brightness multiplier of the reflection probe
		IL2CPP_FIELD(uintptr_t, SkyColor); //Brightness multiplier of the reflection probe
	};

	struct TOD_StarParameters : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_StarParameters");

		IL2CPP_FIELD(float, Size); //Size of the stars
		IL2CPP_FIELD(float, Brightness); //Brightness of the stars
	};

	struct TOD_CloudParameters : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_CloudParameters");

		IL2CPP_FIELD(float, Size); //Size of the clouds
		IL2CPP_FIELD(float, Opacity); //Opacity of the clouds
		IL2CPP_FIELD(float, Coverage); //How much sky is covered by clouds
		IL2CPP_FIELD(float, Sharpness); //Sharpness of the cloud to sky transition
		IL2CPP_FIELD(float, SharColoringpness); //Coloring of the clouds
		IL2CPP_FIELD(float, Attenuation); //Amount of skylight that is blocked
		IL2CPP_FIELD(float, Brightness); //Brightness of the clouds
	};
	struct TOD_SunParameters : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_SunParameters");

		IL2CPP_FIELD(float, MeshSize); //Brightness of the sun
		IL2CPP_FIELD(float, MeshBrightness); //Brightness of the sun
		IL2CPP_FIELD(float, MeshContrast); //Contrast of the sun
	};

	struct TOD_AmbientParameters : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_AmbientParameters");

		IL2CPP_FIELD(float, Saturation); //Saturation of the ambient light
		IL2CPP_FIELD(float, UpdateInterval); //Refresh interval of the ambient light probe in seconds
	};
	struct TOD_Scattering : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_Scattering");
		IL2CPP_FIELD(UnityEngine::Shader*, ScatteringShader);
	};

	struct TOD_Components : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_Components");

		IL2CPP_PROPERTY(UnityEngine::Material*, MoonMaterial); //	private TOD_Components <Components>k__BackingField; // 0xA8
		IL2CPP_FIELD(UnityEngine::Component*, Atmosphere);

		UnityEngine::Renderer* MoonRenderer()
		{
			if (!this)return nullptr;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("<CloudRenderer>k__BackingField"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<UnityEngine::Renderer*>(procedure, this);
			}


			return nullptr;
		}

		void set_CloudMaterial(UnityEngine::Material* Material)
		{
			if (!this)return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_CloudMaterial"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, Material);
			}


			return;
		}

		inline UnityEngine::Material* AtmosphereMaterials()
		{
			if (!this) return {};

			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<AtmosphereMaterial>k__backingfield"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<UnityEngine::Material**>(ToAddress(this) + offset);
			//<Resources>k__backingfield
		}

		inline TOD_Scattering* Skattering()
		{
			if (!this) return {};

			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<BillboardMaterials>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<TOD_Scattering**>(ToAddress(this) + offset);
			//<Resources>k__backingfield
		}
		inline FPSystem::Array<UnityEngine::Renderer*>* BillboardRenderers()
		{
			if (!this) return {};

			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<BillboardRenderers>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<FPSystem::Array<UnityEngine::Renderer*>**>(ToAddress(this) + offset);
			//<Resources>k__backingfield
		}

		inline FPSystem::Array<UnityEngine::Material*>* BillboardMaterials()
		{
			if (!this) return {};

			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<BillboardMaterials>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<FPSystem::Array<UnityEngine::Material*>**>(ToAddress(this) + offset);
			//<Resources>k__backingfield
		}

		inline FPSystem::Array<UnityEngine::Material*>* SunMaterials()
		{
			if (!this) return {};

			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<SunMaterial>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<FPSystem::Array<UnityEngine::Material*>**>(ToAddress(this) + offset);
			//<Resources>k__backingfield
		}
	};

	struct TOD_Resources : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_Resources");

		IL2CPP_FIELD(UnityEngine::Material*, Skybox);
	};

	struct WaterCollision : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("WaterCollision");
	};

	struct WaterSystem : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("WaterSystem");


		inline static WaterCollision* Collision()
		{
			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(StaticClass(), HASH("<Collision>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<WaterCollision**>(ToAddress(StaticClass()) + offset);
			//<Resources>k__backingfield
		}
	};

	struct TOD_Sky : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("TOD_Sky");

		IL2CPP_PROPERTY(TOD_Components*, Components);

		IL2CPP_STATIC_FIELD(FPSystem::List<TOD_Sky*>*, instances);

		IL2CPP_STATIC_PROPERTY(TOD_Sky*, Instance);

		IL2CPP_FIELD(TOD_AtmosphereParameters*, Atmosphere);
		IL2CPP_FIELD(TOD_DayParameters*, Day);
		IL2CPP_FIELD(TOD_NightParameters*, Night);
		IL2CPP_FIELD(TOD_StarParameters*, Stars);
		IL2CPP_FIELD(TOD_CloudParameters*, Clouds);
		IL2CPP_FIELD(TOD_AmbientParameters*, Ambient);
		IL2CPP_FIELD(TOD_SunParameters*, Sun);

		inline TOD_Resources* Resources()
		{
			if (!this) return {};

			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<Resources>k__backingfield"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<TOD_Resources**>(ToAddress(this) + offset);
			//<Resources>k__backingfield
		}

		inline static TOD_Sky* GetClassReference()
		{
			static TOD_Sky* stored_pointer = nullptr;
			if (stored_pointer == nullptr)
			{
				const auto instances_field = instances();

				if (!IsAddressValid(instances_field))
				{
					return nullptr;
				}

				if (instances_field->_size > 0)
				{
					const auto items = instances_field->_items;
					if (IsAddressValid(items))
					{
						const auto first_instance = items->m_Items[0];
						if (IsAddressValid(first_instance))
						{
							stored_pointer = first_instance;
						}
					}
				}
			}

			return stored_pointer;
		}
	};

	struct TOD_Camera : Il2CppObject
	{
		IL2CPP_CLASS("TOD_Camera");

		IL2CPP_FIELD(TOD_Sky*, sky);
	};

	struct ItemContainerId // TypeDefIndex: 9515
	{
		// Fields
		unsigned long Value; // 0x0
	};

	struct ItemContainer : Item {
		IL2CPP_CLASS("ItemContainer");
		IL2CPP_FIELD(FPSystem::List<Item*>*, itemList);

		IL2CPP_FIELD(ItemContainerId, uid);

		Item* GetItem(int id);
	};

	struct ItemId2 {
		uint32_t Value; // 0x0
	};


	struct PlayerInventory : Il2CppObject {
		IL2CPP_CLASS("PlayerInventory");

		IL2CPP_FIELD(ItemContainer*, containerMain);
		IL2CPP_FIELD(ItemContainer*, containerBelt);
		IL2CPP_FIELD(ItemContainer*, containerWear);

		Item* FindItemUID(ItemId2* id);
		ItemContainer* get_belt();

		bool HasAmmo(AmmoTypes ammo)
		{
			if (!this)
				return false;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("HasAmmo"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this, ammo);
			}


			return false;
		}
	};

	struct SkinnedMultiMesh : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("SkinnedMultiMesh");

		IL2CPP_PROPERTY(FPSystem::List<UnityEngine::Renderer*>*, Renderers);
	};

	struct PlayerModel : FacepunchBehaviour
	{

		IL2CPP_CLASS("PlayerModel");
		IL2CPP_FIELD(SkinnedMultiMesh*, _multiMesh);
		IL2CPP_FIELD(bool, isLocalPlayer);
		IL2CPP_FIELD(bool, visible);
		IL2CPP_FIELD(uintptr_t, modelState);

		IL2CPP_FIELD(UnityEngine::Vector3, velocity);
		IL2CPP_FIELD(UnityEngine::Vector3, newVelocity);
		//IL2CPP_FIELD(UnityEngine::BoxCollider*, collision);
		IL2CPP_PROPERTY(bool, IsNpc);
		IL2CPP_FIELD(Vector3, position);
		IL2CPP_FIELD(UnityEngine::GameObject*, headBone);
		IL2CPP_STATIC_FIELD(int, hasParachute);
		IL2CPP_STATIC_FIELD(int, sitReaction);
		IL2CPP_STATIC_FIELD(int, waterlevel);
		IL2CPP_STATIC_FIELD(int, nonGroundedTime);
		IL2CPP_STATIC_FIELD(int, deployParachuteTrigger);

		IL2CPP_PROPERTY(UnityEngine::Animator*, animator);

		bool isNpc();


		void FrameUpdate()
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("FrameUpdate"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}

		static void RebuildAll()
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("RebuildAll"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure);
			}


			return;
		}
	};

	struct PlayerEyes : UnityEngine::Component {
		IL2CPP_CLASS("PlayerEyes");

		IL2CPP_FIELD(Vector3, viewOffset);
		IL2CPP_STATIC_FIELD(Vector3, EyeOffset);
		IL2CPP_PROPERTY(Vector3, position);
		IL2CPP_PROPERTY(Vector3, center);
		IL2CPP_PROPERTY(Vector4, rotation);

		void set_position(Vector3 pos);
		Vector3 MovementRight();
		Vector3 MovementForward();
		Vector4 bodyRotation();
		Vector3 BodyForward();
		Vector3 BodyRight();
		Vector3 HeadForward();

		void SetBodyRotation(Vector4 rot);

		Vector3 get_BodyLeanOffset()
		{
			if (!this)
				return Vector3();

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_BodyLeanOffset"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Vector3>(procedure, this);
			}


			return Vector3();
		}

		void DoFirstPersonCamera(UnityEngine::Camera* cam) {
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DoFirstPersonCamera"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, cam);
			}


			return;
		}

		UnityEngine::Ray* BodyRay()
		{

			if (!this)
				return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("BodyRay"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<UnityEngine::Ray*>(procedure, this);
			}


			return {};
		}
	};
	struct ModelState : Il2CppObject
	{
		IL2CPP_CLASS("ModelState");

		IL2CPP_FIELD(float, waterLevel);
		IL2CPP_FIELD(int, flags);
		IL2CPP_FIELD(int, poseType);

		IL2CPP_PROPERTY(bool, mounted);

		auto SetMounted(bool value) -> void;
		auto get_ducked() -> bool;

		auto SetOnLadder(bool value) -> void;

		void SetSprinting(bool Value);




		void remove_flag(RustStructs::ModelState_Flag flag);
		void set_flag(RustStructs::ModelState_Flag flag);


	};

	struct PlayerInput : Il2CppObject {
		IL2CPP_CLASS("PlayerInput");


		IL2CPP_FIELD(InputState*, state);
		IL2CPP_FIELD(Vector3, bodyAngles);
		IL2CPP_FIELD(Vector2, recoilAngles);
		IL2CPP_FIELD(Vector3, offsetAngles);
		IL2CPP_FIELD(Vector2, viewDelta);

	};

	struct OBB // TypeDefIndex: 12983
	{
		// Fields
		Vector4 rotation; // 0x0
		Vector3 position; // 0x10
		Vector3 extents; // 0x1C
		Vector3 forward; // 0x28
		Vector3 right; // 0x34
		Vector3 up; // 0x40
	};


	struct BaseMovement : UnityEngine::MonoBehaviour
	{
		IL2CPP_CLASS("BaseMovement");

		IL2CPP_FIELD(bool, adminCheat);
		IL2CPP_FIELD(float, adminSpeed);

		IL2CPP_PROPERTY(Vector3, TargetMovement);

		void set_Grounded(float value);
		void set_TargetMovement(Vector3 value);
		float Crawling();
		Vector3 InheritedVelocity();
		float ducking();
		void TeleportTo(Vector3 pos, BasePlayer* player);
	};

	struct PlayerWalkMovement : BaseMovement
	{
		IL2CPP_CLASS("PlayerWalkMovement");

		IL2CPP_FIELD(float, groundAngle);
		IL2CPP_FIELD(float, groundAngleNew);
		IL2CPP_FIELD(float, gravityMultiplier);
		IL2CPP_FIELD(float, maxAngleClimbing);
		IL2CPP_FIELD(float, maxAngleWalking);
		IL2CPP_FIELD(float, groundTime);
		IL2CPP_FIELD(bool, flying);
		IL2CPP_FIELD(bool, wasJumping);
		IL2CPP_FIELD(bool, swimming);
		IL2CPP_FIELD(bool, jumping);
		IL2CPP_FIELD(bool, sprintForced);
		IL2CPP_FIELD(float, WaterLevelHead);
		IL2CPP_FIELD(float, WaterLevelNeck);
	
		IL2CPP_FIELD(float, capsuleHeight);
		IL2CPP_FIELD(float, capsuleCenter);
		IL2CPP_FIELD(float, capsuleHeightDucked);
		IL2CPP_FIELD(float, capsuleCenterDucked);
		IL2CPP_FIELD(float, capsuleHeightCrawling);
		IL2CPP_FIELD(float, capsuleCenterCrawling);



		IL2CPP_FIELD(bool, grounded);

		IL2CPP_FIELD(float, jumpTime);
		IL2CPP_FIELD(float, landTRigidbodyime);
		IL2CPP_FIELD(float, landTime);

		IL2CPP_FIELD(UnityEngine::Rigidbody*, body);
		IL2CPP_FIELD(UnityEngine::CapsuleCollider*, capsule);

		void Jump(AssemblyCSharp::ModelState* ms);

		void TeleportTo(Vector3 pos, BasePlayer* player);
		Vector3 FallVelocity();
	};

	struct PlayerTick : Il2CppObject
	{
		IL2CPP_CLASS("PlayerTick");

		IL2CPP_FIELD(Vector3, position);
		IL2CPP_FIELD(Vector3, eyePos);
	};

	struct AssetNameCache : Il2CppObject {
		IL2CPP_CLASS("AssetNameCache");

		static FPSystem::String* GetName(uintptr_t a1)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetName"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, a1);
			}


			return {};
		}
	};
	struct ItemId// TypeDefIndex: 9516
	{
		// Fields
		unsigned long Value; // 0x0
	};

	struct PlayerBelt
	{
		IL2CPP_CLASS("PlayerBelt");

		Item* GetItemInSlot(int slot)
		{

			if (!this) return 0;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetItemInSlot"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Item*>(procedure, this, slot);
			}


			return 0;
		}

		void ChangeSelect(int iSlot, bool allowRunAction)
		{
			if (!this)return;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ChangeSelect"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, iSlot, allowRunAction);
			}

			return;
		}
	};

	struct LocalPlayer;
	struct BasePlayer : PatrolHelicopter
	{
		IL2CPP_CLASS("BasePlayer");
		IL2CPP_FIELD(PlayerModel*, playerModel);
		IL2CPP_FIELD(PlayerInventory*, inventory);
		IL2CPP_FIELD(std::uint32_t, playerFlags);
		IL2CPP_FIELD(float, lastSentTickTime);
		IL2CPP_FIELD(float, clientTickInterval);
		IL2CPP_FIELD(bool, wasDead);
		IL2CPP_FIELD(bool, clothingBlocksAiming);
		IL2CPP_FIELD(float, clothingMoveSpeedReduction);
		IL2CPP_FIELD(bool, lastHeadshotSoundTime);
		IL2CPP_FIELD(bool, clothingAccuracyBonus);
		IL2CPP_FIELD(int, selectedViewMode);

		IL2CPP_FIELD(PlayerEyes*, eyes);
		IL2CPP_FIELD(ModelState*, modelState);
		IL2CPP_FIELD(PlayerInput*, input);
		IL2CPP_FIELD(BaseMountable*, mounted);
		IL2CPP_FIELD(PlayerWalkMovement*, movement);
		IL2CPP_FIELD(PlayerTick*, lastSentTick);
		IL2CPP_FIELD(ItemId, clActiveItem);
		IL2CPP_FIELD(UnityEngine::Collider*, _lookingAtCollider);
		IL2CPP_FIELD(UnityEngine::CapsuleCollider*, playerCollider);
		IL2CPP_FIELD(FPSystem::List<ProtoBuf::MapNote*>*, ClientCurrentMapNotes);
		IL2CPP_FIELD(PlayerBelt*, Belt);

		bool IsPlayer() {
			if (!this) return false;
			return !strcmp(this->class_name(), XS("BasePlayer")) ||
				!strcmp(this->class_name(), XS("NPCPlayerApex")) ||
				!strcmp(this->class_name(), XS("NPCMurderer")) ||
				!strcmp(this->class_name(), XS("NPCPlayer")) ||
				!strcmp(this->class_name(), XS("HumanNPC")) ||
				!strcmp(this->class_name(), XS("Scientist")) ||
				!strcmp(this->class_name(), XS("TunnelDweller")) ||
				!strcmp(this->class_name(), XS("HTNPlayer")) ||
				!strcmp(this->class_name(), XS("HumanNPCNew")) ||
				!strcmp(this->class_name(), XS("ScientistNPCNew")) ||
				!strcmp(this->class_name(), XS("BanditGuard")) ||
				!strcmp(this->class_name(), XS("ScientistNPC")) ||
				!strcmp(this->class_name(), XS("NPCMissionProvider")) ||
				!strcmp(this->class_name(), XS("NPCShopkeeper"));
		}

		auto belt_list() -> FPSystem::List<Item*>*
		{
			auto ActiveUid = this->clActiveItem();
			if (!IsAddressValid(ActiveUid.Value))
				return { };

			auto inventory = this->inventory();
			if (!inventory)
				return { };

			auto belt = inventory->containerBelt();
			if (!belt)
				return { };

			auto itemList = belt->itemList();
			if (!itemList)
				return { };

			return itemList;
		}

		auto item() -> Item*
		{
			auto ActiveUid = this->clActiveItem();
			if (!IsAddressValid(ActiveUid.Value))
				return { };

			auto inventory = this->inventory();
			if (!inventory)
				return { };

			auto belt = inventory->containerBelt();
			if (!belt)
				return { };

			auto itemList = belt->itemList();
			if (!itemList)
				return { };

			auto items = *reinterpret_cast<uint64_t*>(itemList + 0x10);
			if (!items)
				return { };

			for (int i = 0; i < 6; i++)
			{
				auto item = *reinterpret_cast<Item**> (items + 0x20 + (i * 0x8));
				if (!item)
					continue;

				if (ActiveUid.Value == item->uid())
					return item;
			}

			return { };
		}



		class Target {
		public:
			Vector3 m_position;
			AssemblyCSharp::BasePlayer* m_player;
			int m_bone = 47;
			float m_distance = 10000;
			float m_fov = m_settings::AimbotFOV;
			Vector3 m_velocity;

			bool m_team = false;
			bool m_npc = false;
			bool m_heli = false;
			bool m_sleeping = false;
			bool m_visible = false;

			void Clear() {
				// Reset member variables to their default values
				m_position = Vector3(); // Assuming Vector3 has a default constructor
				m_player = nullptr;
				m_bone = 47;
				m_distance = 10000;
				m_fov = m_settings::AimbotFOV;
				m_velocity = Vector3();

				m_team = false;
				m_npc = false;
				m_heli = false;
				m_sleeping = false;
				m_visible = false;
			}

			bool operator<(const Target& b) {
				if (m_fov == m_settings::AimbotFOV) {
					return m_distance < b.m_distance;
				}
				else {
					return m_fov < b.m_fov;
				}
			}
		};
		static inline int ClosesestToCrosshair(uintptr_t player) {
			int bestBone = 0;
			float closest = FLT_MAX;

			auto base_p = reinterpret_cast<AssemblyCSharp::BasePlayer*>(player);

			float screen_width = UnityEngine::Screen::get_width();
			float screen_height = UnityEngine::Screen::get_height();

			for (auto bone : { (int)RustStructs::bones::head,(int)RustStructs::bones::neck, (int)RustStructs::bones::spine4, (int)RustStructs::bones::spine3,(int)RustStructs::bones::spine2, (int)RustStructs::bones::spine1_scale, 14, 2, 55, 24, 13, 1, 56, 25, 76, 45, 16, 4, (int)RustStructs::bones::r_ankle_scale, (int)RustStructs::bones::l_ankle_scale,(int)RustStructs::bones::r_hand,(int)RustStructs::bones::l_hand }) {
				Vector3 pos3d = base_p->get_bone_transform(bone)->get_position();
				Vector2 pos;
				if (UnityEngine::WorldToScreen(pos3d, pos) == false) continue;
				float length = Math::sqrtf(Math::pow((screen_width / 2) - pos.x, 2) + Math::pow((screen_height / 2) - pos.y, 2));
				if (length < closest) {
					closest = length;

					bestBone = bone;
				}
			}
			return bestBone;
		}

		static auto GetAimbotTarget(Vector3 Source, float MaxDist = 500) -> Target;

		int NewProjectileID()
		{
			if (!this) return 0;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("NewProjectileID"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<int>(procedure, this);
			}


			return 0;
		}

		Vector3 GetMountVelocity()
		{

			if (!this) return Vector3();
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetMountVelocity"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Vector3>(procedure, this);
			}


			return Vector3();
		}

		Vector3 GetInheritedProjectileVelocity(Vector3 Direction)
		{
			if (!this) return Vector3();
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetInheritedProjectileVelocity"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Vector3>(procedure, this, Direction);
			}


			return Vector3();
		}

		bool OnLadder()
		{
			if (!this) return false;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("OnLadder"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this);
			}


			return false;
		}

		bool InSafeZone()
		{
			if (!this) return false;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("InSafeZone"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this);
			}


			return false;
		}

		void ForcePositionTo(Vector3 Pos)
		{
			if (!this)return;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ForcePositionTo"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, Pos);
			}


			return;
		}


		void ChatMessage(const char* msg)
		{

			if (!this)return;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ChatMessage"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(msg));
			}


			return;
		}

		bool IsServerFalling()
		{

			if (!this)return {};
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsServerFalling"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this);
			}


			return {};
		}

		inline Vector3 get_lookingAtPoint()
		{
			if (!this)
				return Vector3();

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_lookingAtPoint"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Vector3>(procedure, this);
			}
			else
			{

				return Vector3();
			}
		}

		inline Vector3 lookingAtPoint()
		{
			if (!this) return {};

			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<lookingAtPoint>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<Vector3*>(ToAddress(this) + offset);
			//<Resources>k__backingfield
		}
		IL2CPP_FIELD(uint64_t, userID);
		IL2CPP_FIELD(FPSystem::String*, UserIDString);
		IL2CPP_FIELD(uint64_t, currentTeam);
		IL2CPP_FIELD(uintptr_t, clientTeam);

		using List = FPSystem::ListDictionary< uint64_t, BasePlayer* >;
		IL2CPP_STATIC_FIELD(List*, visiblePlayerList);
		IL2CPP_STATIC_PROPERTY(bool, isMounted);

		void SendClientTick();
		auto OnLand(float fVelocity) -> float;

		auto IsWeapon() -> bool;
		auto IsMelee() -> bool;
		auto GetMaxSpeed() -> float;
		auto MaxEyeVelocity() -> float;

		OBB WorldSpaceBounds();

		bool IsSameTeam(BasePlayer* player)
		{
			return currentTeam() == player->currentTeam();
		}

		int FindFromHotbar(BasePlayer* lp, std::wstring shortname)
		{
			FPSystem::List<Item*>* belt = belt_list();
			auto Belt = lp->Belt();
			int id = -1;
			if (Belt)
			{
				auto checkitem = [&](Item* item, int idx) {
					if (!item) return false;
					if (std::wstring(item->GetItemName2()).find(shortname.c_str()) != std::wstring::npos) {
						return true;
					}
					return false;
				};

				for (size_t i = 0; i < 5; i++) {
					if (checkitem(Belt->GetItemInSlot(i), i)) {
						id = i;
					}
				}
			}
			return id;
		}

		UnityEngine::Bounds GetBounds()
		{
			if (!this)return {};
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetBounds"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<UnityEngine::Bounds>(procedure, this);
			}


			return {};
		}

		void SendProjectileUpdate(ProtoBuf::PlayerProjectileUpdate* ricochet);

		BaseMovement* GetBaseMovement();

		bool IsRunning();
		bool IsSwimming();
		float GetRadius();
		float GetHeight(bool ducked);

		void SetVA(const Vector2& VA);
		Vector2 GetVA();
		Vector2 GetRA();


		bool IsLocalPlayer();
		bool HasFlag(uint16_t flag);
		bool IsReceivingSnapshot();
		bool IsConnected();
		bool IsSleeper();
		bool IsAdmin();

		bool IsSleeping();

		auto BoundsPadding() -> float;

		bool is_teammate(BasePlayer* local_player) {
			auto team = local_player->clientTeam();

			auto member = *reinterpret_cast<uintptr_t*>(team + 0x28);

			auto size = *reinterpret_cast<int*>(member + 0x18);

			auto list = *reinterpret_cast<uintptr_t*>(member + 0x10);

			auto steam_id = this->userID();

			for (int i = 0; i < size; i++) {
				auto player = *reinterpret_cast<uintptr_t*>(list + 0x20 + i * 0x8);

				auto id = *reinterpret_cast<unsigned long*>(player + 0x18);

				if (id == steam_id)
					return true;
			}
			return false;
		}
		FPSystem::String* get_displayName();
		std::string* get_displayNameTest();
		auto GetJumpHeight() -> float;

		ItemId2* GetHeldItemID();
		auto ActiveItem() -> Item*;
		Item* GetHeldItemSafe();
		BaseVehicle* GetMountedVehicle();

		template<typename T>
		T* GetHeldEntityCast() {
			if (!IsAddressValid(this)) return {};
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetHeldEntity"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<T*>(procedure, this);
			}


			return {};
		}


		UnityEngine::Transform* get_bone_transform(int bone_id);
	};

	struct ConsoleNetwork : Il2CppObject {
		IL2CPP_CLASS("ConsoleNetwork");

		static bool ClientRunOnServer(Unity_String strCommand);
	};

	struct Graphics : Il2CppObject {
		IL2CPP_CLASS("Graphics");

		static void SetFov(float value);
	};

	struct BaseAnimalNPC : Il2CppObject
	{
		IL2CPP_CLASS("BaseAnimalNPC");
	};

	struct StorageContainer : Il2CppObject
	{
		IL2CPP_CLASS("StorageContainer");
	};

	struct BoxStorage : StorageContainer
	{
		IL2CPP_CLASS("BoxStorage");
	};

	struct Recycler : StorageContainer
	{
		IL2CPP_CLASS("Recycler");
	};

	struct Door : Il2CppObject {
		IL2CPP_CLASS("Door");

		void KnockDoor(AssemblyCSharp::BasePlayer* player);
	};

	struct LootContainer : StorageContainer
	{
		IL2CPP_CLASS("LootContainer");
	};

	struct HackableLockedCrate : LootContainer
	{
		IL2CPP_CLASS("HackableLockedCrate");
		IL2CPP_FIELD(float, hackSeconds);
	};

	struct DroppedItemContainer : BaseCombatEntity
	{
		IL2CPP_CLASS("DroppedItemContainer");

		IL2CPP_FIELD(FPSystem::String*, _playerName);
		IL2CPP_FIELD(FPSystem::String*, lootPanelName);

	};

	struct BaseLadder : BaseCombatEntity
	{
		IL2CPP_CLASS("BaseLadder");

	};

	struct StashContainer : StorageContainer
	{
		IL2CPP_CLASS("StashContainer");
	};

	struct Bear : BaseAnimalNPC
	{
		IL2CPP_CLASS("Bear");
	};
	struct Polarbear : BaseAnimalNPC
	{
		IL2CPP_CLASS("Polarbear");
	};

	struct Stag : BaseAnimalNPC
	{
		IL2CPP_CLASS("Stag");
	};

	struct Boar : BaseAnimalNPC
	{
		IL2CPP_CLASS("Boar");
	};

	struct Wolf : BaseAnimalNPC
	{
		IL2CPP_CLASS("Wolf");
	};

	struct Chicken : BaseAnimalNPC
	{
		IL2CPP_CLASS("Chicken");
	};

	struct PlayerNameID : Il2CppObject
	{
		IL2CPP_CLASS("PlayerNameID");

		IL2CPP_FIELD(FPSystem::String*, username);
		IL2CPP_FIELD(uint64_t, userid);
	};

	struct BuildingPrivlidge : StorageContainer
	{
		IL2CPP_CLASS("BuildingPrivlidge");
		IL2CPP_FIELD(float, cachedProtectedMinutes);
		IL2CPP_FIELD(float, cachedUpkeepPeriodMinutes);
		IL2CPP_FIELD(float, cachedUpkeepCostFraction);
		IL2CPP_FIELD(FPSystem::List<ProtoBuf::PlayerNameID*>*, authorizedPlayers);

		float CalculateUpkeepCostFraction() {
			if (!this) return 0.f;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CalculateUpkeepCostFraction"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<float>(procedure, this);
			}


			return 0.f;
		}

		float UpKeep() {
			if (!this) return 0.f;
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetProtectedMinutes"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<float>(procedure, this, true);
			}


			return 0.f;
		}
	};





	struct Workbench : StorageContainer
	{
		IL2CPP_CLASS("Workbench");
	};

	struct BaseOven : StorageContainer
	{
		IL2CPP_CLASS("BaseOven");
	};

	struct ResearchTable : StorageContainer
	{
		IL2CPP_CLASS("ResearchTable");
	};

	struct ReclaimBackpack : StorageContainer
	{
		IL2CPP_CLASS("ReclaimBackpack");
	};

	struct WorldItem : BaseEntity
	{
		IL2CPP_CLASS("WorldItem");
		IL2CPP_FIELD(Item*, item);
	};

	struct DroppedItem : WorldItem
	{
		IL2CPP_CLASS("DroppedItem");
	};


	struct BradleyAPC : BaseCombatEntity
	{
		IL2CPP_CLASS("BradleyAPC");
	};

	struct BaseCorpse : BaseCombatEntity
	{
		IL2CPP_CLASS("BaseCorpse");
	};

	struct LootableCorpse : BaseCorpse
	{
		IL2CPP_CLASS("LootableCorpse");
	};

	struct PlayerCorpse : LootableCorpse
	{
		IL2CPP_CLASS("PlayerCorpse");
	};

	struct HTNPlayer : BasePlayer
	{
		IL2CPP_CLASS("HTNPlayer");
	};
	struct ScientistNPC : BasePlayer
	{
		IL2CPP_CLASS("ScientistNPC");
	};

	struct GingerbreadNPC : BasePlayer
	{
		IL2CPP_CLASS("GingerbreadNPC");
	};

	struct TunnelDweller : BasePlayer
	{
		IL2CPP_CLASS("TunnelDweller");
	};

	struct UnderwaterDweller : BasePlayer
	{
		IL2CPP_CLASS("UnderwaterDweller");
	};


	struct Hammer : BaseMelee {
		IL2CPP_CLASS("Hammer");

	};

	struct ConstructionTarget
	{
		bool valid; // 0x0
		UnityEngine::Ray ray; // 0x4
		BaseEntity* entity; // 0x20
		uintptr_t socket; // 0x28
		bool onTerrain; // 0x30
		Vector3 position; // 0x34
		Vector3 normal; // 0x40
		Vector3 rotation; // 0x4C
		BasePlayer* player; // 0x58
		bool inBuildingPrivilege; // 0x60
	};

	struct Plannel_Guide : HeldEntity {
		IL2CPP_CLASS("Planner.Guide");

		IL2CPP_FIELD(ConstructionTarget*, lastPlacement);
	};

	struct Planner : HeldEntity {
		IL2CPP_CLASS("Planner");

		IL2CPP_FIELD(Vector3, rotationOffset);
		IL2CPP_FIELD(Plannel_Guide*, guide);
		IL2CPP_FIELD(uintptr_t, currentConstruction);
	};

	

	struct LocalPlayer : Il2CppObject
	{
		IL2CPP_CLASS("LocalPlayer");

		IL2CPP_STATIC_PROPERTY(BasePlayer*, Entity);

		static ItemContainer* GetLootContainer(int index)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetLootContainer"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<ItemContainer*>(procedure, index);
			}


			return {};
		}

		static void MoveItem(uint32_t itemid, uint32_t targetContainer, int targetSlot, int amount, bool altMove)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("MoveItem"), 5);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, itemid, targetContainer, targetSlot, amount, altMove);
			}


			return;
		}
	};


	struct ItemIcon : UnityEngine::MonoBehaviour {
		IL2CPP_CLASS("ItemIcon");

		using List = FPSystem::ListDictionary< int, float >;
		IL2CPP_FIELD(List*, containerLootStartTimes);
		IL2CPP_FIELD(void*, timedAction);
		IL2CPP_FIELD(Vector2, timedActionTime);
		IL2CPP_FIELD(bool, queuedForLooting);
		IL2CPP_FIELD(Item*, item);

		IL2CPP_FIELD(float, queuedLootAtTime);



		auto StartTimedLootAction(float delay) -> void;

		void RunTimedAction();

		auto SetTimedLootAction(int a1, void* a2) -> void;
	};

	struct BaseNpc : BaseCombatEntity
	{
		IL2CPP_CLASS("BaseNpc");

		IL2CPP_FIELD(float, AttackRange);
	};

	struct NPCPlayer : BasePlayer
	{
		IL2CPP_CLASS("NPCPlayer");
	};

	struct GunTrap : StorageContainer
	{
		IL2CPP_CLASS("GunTrap");
	};
	struct SupplyDrop : StorageContainer
	{
		IL2CPP_CLASS("SupplyDrop");
	};
	struct RidableHorse : BaseCombatEntity
	{
		IL2CPP_CLASS("RidableHorse");
	};
	struct OreHotSpot : BaseCombatEntity
	{
		IL2CPP_CLASS("OreHotSpot");
	};

	struct MainMenuSystem : UnityEngine::Component
	{
		IL2CPP_CLASS("MainMenuSystem");
	};

	struct Collider : UnityEngine::Component
	{
		IL2CPP_CLASS("Collider");

		bool set_enabled(bool value);

	};

	struct KeyCodeEx
	{
		IL2CPP_CLASS("KeyCodeEx");

		static FPSystem::String* ToShortname(RustStructs::KeyCode code, bool lowercase)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ToShortname"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, code, lowercase);
			}


			return {};
		}
	};

	struct ExplosionsFPS
	{
		IL2CPP_CLASS("ExplosionsFPS");
	};

	struct AimConeUtil : UnityEngine::MonoBehaviour {
		IL2CPP_CLASS("AimConeUtil");

		static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside);
	};




	struct DecayEntity : BaseCombatEntity
	{
		IL2CPP_CLASS("DecayEntity");
	};

	struct Barricade : BaseEntity
	{
		IL2CPP_CLASS("Barricade");
	};

	struct StabilityEntity : DecayEntity
	{
		IL2CPP_CLASS("StabilityEntity");
	};

	struct BuildingBlock : StabilityEntity
	{
		IL2CPP_CLASS("BuildingBlock");


		void UpgradeToGrade(RustStructs::BuildingGrade grade, int xd, BasePlayer* player);

		bool CanChangeToGrade(RustStructs::BuildingGrade grade, int xd, BasePlayer* player);

		bool CanAffordUpgrade(RustStructs::BuildingGrade grade, int xd, BasePlayer* player);
		bool IsUpgradeBlocked();


	};

	struct StringPool : Il2CppObject {
		IL2CPP_CLASS("StringPool");

		static uint64_t Get(const char* name);

	};

	struct GameTrace : Il2CppObject {
		IL2CPP_CLASS("GameTrace");

		static bool Trace(HitTest* test, int layerMask);

		static void TraceAll(uintptr_t a1, uintptr_t a2, int a3)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("TraceAll"), 3);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, a1, a2, a3);
			}


			return;
		}
	};

	struct TerrainCollision : Il2CppObject {
		IL2CPP_CLASS("TerrainCollision");


		bool GetIgnore(Vector3 pos, float radius)
		{
			if (!this)
				return false;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetIgnore"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this, pos, radius);
			}


			return 0.f;
		}
	};

	struct TerrainSplatMap : Il2CppObject
	{
		IL2CPP_CLASS("TerrainSplatMap");

	};

	struct TerrainHeightMap : Il2CppObject
	{
		IL2CPP_CLASS("TerrainHeightMap");

		float GetHeight(Vector3 pos)
		{
			if (!this)
				return false;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetHeight"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<float>(procedure, this, pos);
			}


			return 0.f;
		}
	};


	struct TerrainColors : Il2CppObject {
		IL2CPP_CLASS("TerrainColors");

		Color GetColor(Vector3 pos, int mask)
		{
			if (!this) return Color();

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetColor"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<Color>(procedure, this, pos, mask);
			}
			else
			{

				return Color();
			}
		}
	};

	struct TerrainMeta : Il2CppObject {
		IL2CPP_CLASS("TerrainMeta");


		IL2CPP_STATIC_PROPERTY(UnityEngine::Terrain_C*, Terrain);
		IL2CPP_STATIC_PROPERTY(TerrainHeightMap*, HeightMap);
		IL2CPP_STATIC_PROPERTY(TerrainCollision*, Collision);
		IL2CPP_STATIC_PROPERTY(TerrainColors*, Colors);

		IL2CPP_STATIC_PROPERTY(Vector3, Position);

	};

	struct EffectLibrary : Il2CppObject {
		IL2CPP_CLASS("EffectLibrary");

	};

	struct Client : Il2CppObject {
		IL2CPP_CLASS("Client");
		IL2CPP_FIELD(uintptr_t*, authTicket);


		void OnRequestUserInformation(uintptr_t packet)
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("OnRequestUserInformation"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, packet);
			}
			else
			{

				return;
			}
		}

		FPSystem::String* GetOSName()
		{
			if (!this) return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetOSName"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, this);
			}
			else
			{

				return {};
			}
		}
	};

	struct SteamClientWrapper : Il2CppObject {
		IL2CPP_CLASS("SteamClientWrapper");

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}

		UnityEngine::Texture2D* GetAvatarTexture(uint64_t steamid)
		{
			if (!this)
				return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetAvatarTexture"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<UnityEngine::Texture2D*>(procedure, this, steamid);
			}


			return {};
		}

		FPSystem::String* GetSteamUserName(uint64_t steamid)
		{
			if (!this)
				return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetUserName"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, this, steamid);
			}


			return {};
		}

	};

	struct CSOption {

		bool IsServer; // 0x0
		bool IsClient;// 0x1
		bool ForwardtoServerOnMissing; // 0x2
		bool PrintOutput; // 0x3
		bool IsUnrestricted; // 0x4
		bool FromRcon; // 0x5
		bool IsFromServer; // 0x6
	};


	struct CSCommand : Il2CppObject
	{
		IL2CPP_CLASS("ConsoleSystem.Command");
		IL2CPP_FIELD(FPSystem::String*, Name);
	};

	struct ConsoleSystemArg : Il2CppObject {
		IL2CPP_CLASS("ConsoleSystem.Arg");
		IL2CPP_FIELD(CSOption*, Option);
		IL2CPP_FIELD(CSCommand*, cmd);
		IL2CPP_FIELD(FPSystem::String*, FullString);
		bool HasPermissionn();
	};

	struct ConsoleSystem : Il2CppObject {
		IL2CPP_CLASS("ConsoleSystem");
		IL2CPP_STATIC_FIELD(ConsoleSystemArg*, CurrentArgs);
		static FPSystem::String* Run(CSOption* option, const char* cmd, uintptr_t* args)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Run"), 3);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, option, CIl2Cpp::il2cpp_string_new(cmd), args);
			}
			else
			{

				return {};
			}
		}

		static CSOption* client()
		{

			auto option = new CSOption();

			return new CSOption
			{
				option->IsClient = true,
				option->ForwardtoServerOnMissing = true,
				option->PrintOutput = true
			};
		}
	};

	struct EffectClient : Il2CppObject {
		IL2CPP_CLASS("Effect.client");


		static void Run(const char* str, UnityEngine::GameObject* gameObject)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Run"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, CIl2Cpp::il2cpp_string_new(str), gameObject);
			}
			else
			{

				return;
			}
		}
	};

	struct EffectData : Il2CppObject
	{
		IL2CPP_CLASS("EffectData");

		IL2CPP_FIELD(int, pooledstringid);
		IL2CPP_FIELD(Vector3, origin);
	};

	struct Effect : EffectData {
		IL2CPP_CLASS("Effect");

		IL2CPP_FIELD(Vector3, worldPos);
		IL2CPP_FIELD(FPSystem::String*, pooledString);
		IL2CPP_STATIC_FIELD(Effect*, reusableInstace);
		IL2CPP_FIELD(UnityEngine::Transform*, transform);

		void Clear()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Clear"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}
		}

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}

		/*
			public Vector3 Up; // 0x58
	public Vector3 worldPos; // 0x64
	public Vector3 worldNrm; // 0x70
	public bool attached; // 0x7C
	public Transform transform; // 0x80
	public GameObject gameObject; // 0x88
	public string pooledString; // 0x90
	public bool broadcast; // 0x98
	private static Effect reusableInstace; // 0x0
		*/
	};

	struct EffectNetwork : Il2CppObject {
		IL2CPP_CLASS("EffectNetwork");

		IL2CPP_STATIC_FIELD(Effect*, effect);

		static void OnReceivedEffect(uintptr_t* message)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("OnReceivedEffect"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, message);
			}
			else
			{

				return;
			}
		}
	};

	struct SoundOcclusion : Il2CppObject {
		IL2CPP_CLASS("SoundOcclusion");

		IL2CPP_FIELD(float, occlusionAmount);
		IL2CPP_FIELD(Vector3, soundOffset);
		IL2CPP_FIELD(float, lastOcclusionCheck);
		IL2CPP_FIELD(float, occlusionCheckInterval);
		IL2CPP_FIELD(FPSystem::List<UnityEngine::RaycastHit*>*, hits);
		IL2CPP_FIELD(UnityEngine::Ray, ray);


		/*
		private bool <isOccluded>k__BackingField; // 0x1C
	private float occlusionAmount; // 0x20
	private Sound sound; // 0x28
	private OnePoleLowpassFilter lowpass; // 0x30
	private SoundModulation.Modulator gainMod; // 0x38
	private Vector3 soundOffset; // 0x40
	private float lastOcclusionCheck; // 0x4C
	private float occlusionCheckInterval; // 0x50
	private Ray ray; // 0x54
	private List<RaycastHit> hits; // 0x70
		*/
	};


	struct AntiHack : Il2CppObject {
		IL2CPP_CLASS("AntiHack");


		static bool TestNoClipping(Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool sphereCast, uintptr_t* collider, bool vehicleLayer, BaseEntity* ignoreEntity)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("TestNoClipping"), 8);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool*>(procedure, oldPos, newPos, radius, backtracking, sphereCast, collider, vehicleLayer, ignoreEntity);
			}
			else
			{

				return false;
			}
		}
	};

	struct UIWounded : Il2CppObject {
		IL2CPP_CLASS("UIWounded");

		IL2CPP_STATIC_FIELD(float , recoveryChance)
	};


	struct UINexusMap : Il2CppObject {
		IL2CPP_CLASS("UINexusMap");

		IL2CPP_FIELD(UnityEngine::Texture2D*, _currentMapTexture);


		void Update()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Update"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}
		}

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}
	};
	struct World : Il2CppObject {
		IL2CPP_CLASS("World");

		static int Size()
		{
			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(StaticClass(), HASH("<Size>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<int*>(ToAddress(StaticClass()->static_fields) + offset);
		}

		static int Seed()
		{
			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(StaticClass(), HASH("<Seed>k__BackingField"));
			if (IsAddressValid(field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}

			return *reinterpret_cast<int*>(ToAddress(StaticClass()->static_fields) + offset);
			//<Seed>k__BackingField
		}
	};

	struct MapView : Il2CppObject {
		IL2CPP_CLASS("MapView");

		IL2CPP_FIELD(UnityEngineUI::Image*, cameraPositon);

		IL2CPP_FIELD(UnityEngineUI::RawImage*, mapImage);

		IL2CPP_STATIC_FIELD(MapView*, ActiveView);

	};

	struct TraceInfo : Il2CppObject // TypeDefIndex: 1153
	{
		IL2CPP_CLASS("TraceInfo");

		bool valid; // 0x0
		float distance; // 0x4
		DWORD64 entity; // 0x8   //BasePlayer
		Vector3 point; // 0x10
		Vector3 normal; // 0x1C
		DWORD64/*Transform*/ bone; // 0x28
		DWORD64 material; // 0x30
		unsigned int partID; // 0x38
		DWORD64 collider; // 0x40

		void UpdateHitTest(HitTest* hittest)
		{
			if (!this)
				return;


			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("UpdateHitTest"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, hittest);
			}
			else
			{
				return;
			}
		}
	};


	struct TerrainTexturing : UnityEngine::Component {
		IL2CPP_CLASS("TerrainTexturing");

		IL2CPP_STATIC_PROPERTY(TerrainTexturing*, Instance);
	};

	struct WaterOverlayEffectParams // TypeDefIndex: 995
	{
		// Fields
		float scatterCoefficient; // 0x0
		bool blur; // 0x4
		float blurDistance; // 0x8
		float blurSize; // 0xC
		int blurIterations; // 0x10
		bool wiggle; // 0x14
		float wiggleSpeed; // 0x18
		bool chromaticAberration; // 0x1C
		bool godRays; // 0x1D
		//static WaterOverlay.EffectParams DefaultAdmin; // 0x0
		//static WaterOverlay.EffectParams DefaultGoggles; // 0x20
		//static WaterOverlay.EffectParams DefaultSubmarine; // 0x40
		//static WaterOverlay.EffectParams DefaultUnderwaterLab; // 0x60
		//static WaterOverlay.EffectParams DefaultCinematic; // 0x80
	};


	struct WaterOverlay : UnityEngine::MonoBehaviour {
		IL2CPP_CLASS("WaterOverlay");

		IL2CPP_FIELD(WaterOverlayEffectParams, adminParams);
	};

}


namespace ConVar {
	IL2CPP_NAME_SPACE("ConVar");

	struct Server : Il2CppObject {
		IL2CPP_CLASS("Server");

		IL2CPP_STATIC_FIELD(FPSystem::String*, ip);
		IL2CPP_STATIC_FIELD(int, seed);
		IL2CPP_STATIC_FIELD(int, max_sleeping_bags);
		IL2CPP_STATIC_FIELD(int, bag_quota_item_amount);

	};

	struct Client : AssemblyCSharp::ConsoleSystem {
		IL2CPP_CLASS("Client");

		IL2CPP_STATIC_FIELD(float, camdist);
	};

	struct Culling : AssemblyCSharp::ConsoleSystem {
		IL2CPP_CLASS("Culling");

		IL2CPP_STATIC_FIELD(float, entityMinCullDist);
	};

	struct Effects : AssemblyCSharp::ConsoleSystem {
		IL2CPP_CLASS("Effects");

		IL2CPP_STATIC_FIELD(int, _antialiasing);
	};

	struct Player : AssemblyCSharp::ConsoleSystem {
		IL2CPP_CLASS("Player");

		IL2CPP_STATIC_FIELD(float, noclipspeed);
		IL2CPP_STATIC_FIELD(float, noclipspeedslow);
		IL2CPP_STATIC_FIELD(float, noclipspeedfast);
	};


	struct Weather : AssemblyCSharp::ConsoleSystem {
		IL2CPP_CLASS("Weather");

		static void set_cloud_opacity(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_cloud_opacity"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_atmosphere_brightness(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_atmosphere_brightness"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_atmosphere_contrast(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_atmosphere_contrast"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_atmosphere_rayleigh(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_atmosphere_rayleigh"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_cloud_brightness(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_cloud_brightness"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_cloud_coverage(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_cloud_coverage"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_fog(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_fog"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_ocean_scale(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_ocean_scale"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_rain(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_rain"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_rainbow(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_rainbow"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_thunder(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_thunder"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}

		static void set_wind(float value)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_wind"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}
	};
}

enum MessageType // TypeDefIndex: 13298
{
	// Fields
	First = 0,
	Welcome = 1,
	Auth = 2,
	Approved = 3,
	Ready = 4,
	Entities = 5,
	EntityDestroy = 6,
	GroupChange = 7,
	GroupDestroy = 8,
	RPCMessage = 9,
	EntityPosition = 10,
	ConsoleMessage = 11,
	ConsoleCommand = 12,
	Effect = 13,
	DisconnectReason = 14,
	Tick = 15,
	Message = 16,
	RequestUserInformation = 17,
	GiveUserInformation = 18,
	GroupEnter = 19,
	GroupLeave = 20,
	VoiceData = 21,
	EAC = 22,
	EntityFlags = 23,
	World = 24,
	ConsoleReplicatedVars = 25,
	Last = 25
};

namespace Network {
	IL2CPP_NAME_SPACE("Network");

	struct NetRead : Il2CppObject {
		IL2CPP_CLASS("NetRead");

	};
	struct BaseNetwork;
	enum SendMethod // TypeDefIndex: 13674
	{

		Reliable = 0,
		ReliableUnordered = 1,
		Unreliable = 2,
	};
	enum Priority // TypeDefIndex: 10367
	{
		Immediate = 0,
		Normal = 1,
	};

	struct SendInfo // TypeDefIndex: 13679
	{
		// Fields
		SendMethod method; // 0x0
		int channel; // 0x4
		Priority priority; // 0x8
		uintptr_t connections; // 0x10
		uintptr_t connection; // 0x18

		static SendInfo* New(uintptr_t connectionz)
		{
			auto option = new SendInfo();



			option->method = SendMethod::Reliable;
			option->channel = 0;
			option->priority = Priority::Normal;
			option->connection = connectionz;

			return option;
		}
	};

	struct NetWrite : Il2CppObject {
		IL2CPP_CLASS("NetWrite");

		void Send(SendInfo* info)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Send"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, info);
			}
			else
			{

				return;
			}
		}
		void BytesWithSize(FPSystem::Array<FPSystem::Byte*>* bytes)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethodFullArgs(HASH("Facepunch.Network::Network::NetWrite::BytesWithSize(Byte[]): Void"));
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, bytes);
			}
			else
			{

				return;
			}
		}

		bool Start(BaseNetwork* net)
		{
			if (!this)
				return false;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Start"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<bool>(procedure, this, net);
			}
			else
			{

				return false;
			}
		}

		void String(const char* val)
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("String"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(val));
			}
			else
			{

				return;
			}
		}

		void UInt32(unsigned int val)
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("UInt32"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, val);
			}
			else
			{

				return;
			}
		}

		void UInt64(unsigned long val)
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("UInt64"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, val);
			}
			else
			{

				return;
			}
		}

		void UInt8(byte val)
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("UInt8"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, val);
			}
			else
			{

				return;
			}
		}

		void PacketID(MessageType type)
		{
			if (!this)
				return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("PacketID"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, type);
			}
			else
			{

				return;
			}
		}
	};

	struct BaseNetwork : Il2CppObject {
		IL2CPP_CLASS("BaseNetwork");


		IL2CPP_FIELD(NetWrite*, writeQueue);
		NetWrite* StartWrite()
		{
			if (!this)
				return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("StartWrite"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<NetWrite*>(procedure, this);
			}
			else
			{

				return {};
			}
		}
	};

	struct Message : Il2CppObject {
		IL2CPP_CLASS("Message");

		IL2CPP_FIELD(BaseNetwork*, peer);
		IL2CPP_FIELD(NetRead*, read);
		IL2CPP_FIELD(MessageType, type);
		IL2CPP_PROPERTY(uintptr_t, connection);
	};

	struct Connection : Il2CppObject
	{
		IL2CPP_CLASS("Connection");

		int GetPacketsPerSecond(int test)
		{
			if (!this) return 0;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethodFullArgs(HASH("Facepunch.Network::Network::Connection::GetPacketsPerSecond(Int32): UInt64"));
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<int>(procedure, this, test);
			}
			else
			{

				return 0;
			}

		}

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}
	};

	namespace Raknet {
		IL2CPP_NAME_SPACE("Facepunch.Network.Raknet");

		class Client
		{
		public:
			IL2CPP_CLASS("Client");


			auto IsConnected() -> bool {
				if (!this)
					return false;

				const auto LOS = reinterpret_cast<bool (*)(Client*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("IsConnected"), 0)));
				return LOS(this);
			}
		};
	}

	class Client
	{
	public:
		IL2CPP_CLASS("Client");


		auto get_ServerName() -> FPSystem::String* {
			const auto LOS = reinterpret_cast<FPSystem::String * (*)(Client*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("get_ServerName"), 0)));
			return LOS(this);
		}
	};
	class Networkable : Il2CppObject
	{
	public:
		IL2CPP_CLASS("Networkable");

		IL2CPP_FIELD(Network::Client*, cl);

	};

	class Net
	{
	public:
		IL2CPP_CLASS("Net");

		IL2CPP_STATIC_PROPERTY(Raknet::Client*, cl);

		//STATIC_FUNCTION("Network::Net::get_cl(): Network.Client", get_cl, Facepunch::Network::Raknet::CClient* ());
	};
}

typedef struct _UncStr {
	char stub[0x10];
	int len;
	wchar_t str[1];
} *pUncStr;

class f_object {
public:
	bool valid;
	DWORD64 entity;
	Vector3 position;
	float dist = 10000.f;
	bool visible = false;

	bool operator<(const f_object& b) { return this->dist < b.dist; }
	bool operator>(const f_object& b) { return this->dist > b.dist; }
	bool operator<=(const f_object& b) { return this->dist <= b.dist; }
	bool operator>=(const f_object& b) { return this->dist >= b.dist; }
	f_object() {
		this->valid = false;
	}
	f_object(Vector3 target) {
		this->valid = false;
		this->position = target;
	}
	static Vector3 GetEntityPosition(std::uint64_t entity) {
		if (!IsAddressValid(entity)) return Vector3();

		uintptr_t plyVis = *reinterpret_cast<uintptr_t*>(entity + 0x8);
		if (!IsAddressValid(plyVis)) return Vector3();

		uintptr_t visualState = *reinterpret_cast<uintptr_t*>(plyVis + 0x38);
		if (!IsAddressValid(visualState)) return Vector3();

		Vector3 ret = *reinterpret_cast<Vector3*>(visualState + 0x90);
		return ret;
	}

	static f_object get_closest_object(Vector3 from, const char* namee, Vector3 ignore = Vector3(), Vector3 ignore2 = Vector3(), Vector3 ignore3 = Vector3(), bool classname = false, const char* classnamee = XS(""), float get_dist = 99999.f, bool vis = false, bool y = false) {
		f_object lowest = f_object();

		auto entityList = AssemblyCSharp::BaseNetworkable::clientEntities()->entityList();
		if (IsAddressValid(entityList)) {
			for (int i = 1; i < entityList->vals->count; i++) {
				uintptr_t Entity = *reinterpret_cast<uintptr_t*>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
				if (!IsAddressValid(Entity)) continue;
				uintptr_t Object = *reinterpret_cast<uint64_t*>(Entity + 0x10);
				if (!IsAddressValid(Object)) continue;
				uintptr_t ObjectClass = *reinterpret_cast<uint64_t*>(Object + 0x30);
				if (!IsAddressValid(ObjectClass)) continue;
				pUncStr name = *reinterpret_cast<pUncStr*>(ObjectClass + 0x60); if (!name) continue;
				char* buff = name->stub;
				f_object res = f_object();
				if (classname) {
					if (String::strstr((char*)*reinterpret_cast<DWORD64*>(*reinterpret_cast<DWORD64*>(*reinterpret_cast<DWORD64*>(Object + 0x28)) + 0x10), classnamee)) {
						uintptr_t a = *reinterpret_cast<UINT64*>(ObjectClass + 0x30);
						float dist = GetEntityPosition(a).get_3d_dist(from);
						if (GetEntityPosition(a) != ignore && GetEntityPosition(a) != ignore2 && GetEntityPosition(a) != ignore3) {
							res.valid = dist <= get_dist;
							res.dist = dist;
							res.entity = Entity;
							res.position = GetEntityPosition(a);
							if (res < lowest) lowest = res;
						}
					}
				}
				else {
					if (String::strstr(buff, namee)) {
						uintptr_t a = *reinterpret_cast<uintptr_t*>(ObjectClass + 0x30);
						float dist = GetEntityPosition(a).get_3d_dist(from);
						if (GetEntityPosition(a) != ignore && GetEntityPosition(a) != ignore2 && GetEntityPosition(a) != ignore3) {
							if (y) {
								if (GetEntityPosition(a).y > 0) {
									res.valid = dist <= get_dist;
									res.dist = dist;
									res.entity = Entity;
									res.position = GetEntityPosition(a);
									if (res < lowest) lowest = res;
								}
							}
							else {
								res.valid = dist <= get_dist;
								res.dist = dist;
								res.entity = Entity;
								res.position = GetEntityPosition(a);
								if (res < lowest) lowest = res;
							}
						}
					}
				}
			}
			return lowest;
		}
	}
};

inline bool ProjectileHitWater = false;
inline AssemblyCSharp::Projectile* ProjectileHitWaterInstance;
inline AssemblyCSharp::Projectile* FatBulletInstance;

struct TimeAverageValueData
{
public:
	int Calculate()
	{
		float realtimeSinceStartup = UnityEngine::Time::get_realtimeSinceStartup();
		float num = realtimeSinceStartup - refreshTime;
		if (num >= 1.0)
		{
			counterPrev = (int)(counterNext / num + 0.5);
			counterNext = 0;
			refreshTime = realtimeSinceStartup;
			num = 0;
		}
		return (int)(counterPrev * (1.0 - num)) + counterNext;
	}

	void Increment()
	{
		this->Calculate();
		counterNext += 1;
	}

	void Reset()
	{
		counterPrev = 0;
		counterNext = 0;
	}

	float refreshTime;

	int counterPrev;

	int counterNext;
};


inline TimeAverageValueData Total_Counter = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter2 = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter3 = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter5 = { 0, 0, 0 };

inline TimeAverageValueData Signal_Counter = { 0, 0, 0 };

namespace Steamworks {
	IL2CPP_NAME_SPACE("Steamworks");



	struct SteamId_c {
		uint64_t Value; // 0x0
	};

	struct SteamClient : Il2CppObject {
		IL2CPP_CLASS("SteamClient");

		IL2CPP_STATIC_PROPERTY(SteamId_c, SteamId);

		IL2CPP_STATIC_PROPERTY(FPSystem::String*, Name);
	};
}

namespace RustPlatformSteam {
	IL2CPP_NAME_SPACE("Rust.Platform.Steam");

	struct AuthTicket : Il2CppObject {
		IL2CPP_CLASS("AuthTicket");

		IL2CPP_PROPERTY(FPSystem::Array<FPSystem::Byte*>*, Data);
	};


	struct SteamPlatform : Il2CppObject {
		IL2CPP_CLASS("SteamPlatform");

		IL2CPP_PROPERTY(bool, IsValid);
		IL2CPP_PROPERTY(FPSystem::String*, UserName);

		void set_UserId(unsigned int userID)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_UserId"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, userID);
			}
			else
			{

				return;
			}
		}

		void set_UserName(FPSystem::String* str)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_UserName"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, (str));
			}
			else
			{

				return;
			}

		}

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}
	};
}
namespace Facepunch
{
	IL2CPP_NAME_SPACE("Facepunch");

	struct CommandLine : Il2CppObject {
		IL2CPP_CLASS("CommandLine");

		IL2CPP_STATIC_PROPERTY(FPSystem::String*, Full);


		static FPSystem::ListDictionary< FPSystem::String*, FPSystem::String* >* GetSwitches()
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetSwitches"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::ListDictionary< FPSystem::String*, FPSystem::String* >*>(procedure);
			}
			else
			{

				return {};
			}
		}
	};

	struct RandomUsernames  : Il2CppObject {
		IL2CPP_CLASS("RandomUsernames");

		static FPSystem::String* Get(int v)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Get"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, v);
			}
			else
			{

				return {};
			}
		}
	};
}
namespace Rust_Workshop
{
	IL2CPP_NAME_SPACE("Rust.Workshop");

	struct WorkshopSkin : Il2CppObject {
		IL2CPP_CLASS("WorkshopSkin");

		static void Apply(UnityEngine::GameObject* obj, uint64_t skinId, uintptr_t* ptr)
		{
			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Apply"), 3);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, obj, skinId, ptr);
			}
			else
			{

				return;
			}
		}
	};
}



namespace NetworkVisibility
{
	IL2CPP_NAME_SPACE("Network.Visibility");


	struct Subscriber : Il2CppObject {
		IL2CPP_CLASS("Subscriber");

	};
}

