#pragma once
#include "AssemblyCSharp.hpp"
#include "../../Features/Features/Features.hpp"
#include "../../Features/Notifications/Notifications.hpp"


namespace O::Projectile {
	constexpr auto initialVelocity = 0x18;
	constexpr auto drag = 0x24;
	constexpr auto gravityModifier = 0x28;
	constexpr auto thickness = 0x2C;
	constexpr auto initialDistance = 0x30;
	constexpr auto remainInWorld = 0x34;
	constexpr auto stickProbability = 0x38;
	constexpr auto breakProbability = 0x3C;
	constexpr auto conditionLoss = 0x40;
	constexpr auto ricochetChance = 0x44;
	constexpr auto penetrationPower = 0x48;
	constexpr auto waterIntegrityLoss = 0x4C;
	constexpr auto damageProperties = 0x50;
	constexpr auto damageDistances = 0x58;
	constexpr auto createDecals = 0x80;
	constexpr auto doDefaultHitEffects = 0x81;
	constexpr auto flybySound = 0x88;
	constexpr auto flybySoundDistance = 0x90;
	constexpr auto closeFlybySound = 0x98;
	constexpr auto closeFlybyDistance = 0xA0;
	constexpr auto tumbleSpeed = 0xA4;
	constexpr auto tumbleAxis = 0xA8;
	constexpr auto swimScale = 0xB4;
	constexpr auto swimSpeed = 0xC0;
	constexpr auto owner = 0xD0;
	constexpr auto sourceWeaponPrefab = 0xD8;
	constexpr auto sourceProjectilePrefab = 0xE0;
	constexpr auto mod = 0xE8;
	constexpr auto projectileID = 0xF0;
	constexpr auto seed = 0xF4;
	constexpr auto clientsideEffect = 0xF8;
	constexpr auto clientsideAttack = 0xF9;
	constexpr auto integrity = 0xFC;
	constexpr auto maxDistance = 0x100;
	constexpr auto modifier = 0x104;
	constexpr auto invisible = 0x114;
	constexpr auto currentVelocity = 0x118;
	constexpr auto currentPosition = 0x124;
	constexpr auto traveledDistance = 0x130;
	constexpr auto traveledTime = 0x134;
	constexpr auto launchTime = 0x138;
	constexpr auto sentPosition = 0x13C;
	constexpr auto previousPosition = 0x148;
	constexpr auto previousVelocity = 0x154;
	constexpr auto previousTraveledTime = 0x160;
	constexpr auto isUnderwater = 0x164;
	constexpr auto isRicochet = 0x165;
	constexpr auto isRetiring = 0x166;
	constexpr auto flybyPlayed = 0x167;
	constexpr auto wasFacingPlayer = 0x168;
	constexpr auto flybyPlane = 0x16C;
	constexpr auto flybyRay = 0x17C;
	constexpr auto cleanupAction = 0x198;
	constexpr auto hitTest = 0x1A0;
	constexpr auto swimRandom = 0x1A8;
	constexpr auto _waterMaterialID = 0x4;
	constexpr auto cachedWaterString = 0x8;
};

template<typename t>
t read(uintptr_t addr) {
	if (addr < 0xffffff)
		return t();
	if (addr > 0x7fffffff0000)
		return t();

	return *reinterpret_cast<t*>(addr);
}

template<typename t>
bool write(uintptr_t addr, t buffer) {
	*reinterpret_cast<t*>(addr) = buffer;
	return true;
}


#define safe_read(Addr, Type) read<Type>((DWORD64)Addr)
#define safe_write(Addr, Data, Type) write<Type>((DWORD64)Addr, Data);

class Projectile_c : AssemblyCSharp::Projectile {
public:
	IL2CPP_CLASS("Projectile");
	IL2CPP_FIELD(float, thickness);
	IL2CPP_FIELD(Vector3, currentPosition);
	IL2CPP_FIELD(Vector3, sentPosition);

	IL2CPP_FIELD(Vector3, currentVelocity);
	IL2CPP_FIELD(Vector3, initialVelocity);
	IL2CPP_FIELD(Vector3, previousPosition);
	IL2CPP_FIELD(Vector3, previousVelocity);
	IL2CPP_FIELD(AssemblyCSharp::HitTest*, hitTest);
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
	IL2CPP_FIELD(float, swimRandom);
	IL2CPP_FIELD(Vector3, swimSpeed);

	IL2CPP_FIELD(int, projectileID);
	IL2CPP_FIELD(float, initialDistance);
	IL2CPP_FIELD(float, integrity);
	IL2CPP_FIELD(AssemblyCSharp::BasePlayer*, owner);
	IL2CPP_FIELD(bool, isRicochet);
	IL2CPP_FIELD(AssemblyCSharp::AttackEntity*, sourceWeaponPrefab);
	IL2CPP_FIELD(AssemblyCSharp::DamageProperties*, damageProperties);
	IL2CPP_FIELD(float, ricochetChance);

	bool IsAlive() {
		return (this->integrity() > 0.001f && this->traveledDistance() < this->maxDistance());
	}

	struct TraceInfo {

		bool valid; // 0x0
		float distance; // 0x4
		DWORD64 entity; // 0x8   //BasePlayer
		Vector3 point; // 0x10
		Vector3 normal; // 0x1C
		DWORD64/*Transform*/ bone; // 0x28
		DWORD64 material; // 0x30
		unsigned int partID; // 0x38
		DWORD64 collider; // 0x40
	};

	void SimulateProjectile(Vector3 position, Vector3 velocity, float partialTime, float travelTime, Vector3 gravity, float drag,  Vector3 prevPosition,  Vector3 prevVelocity)
	{
		float num = 0.03125f;
		prevPosition = position;
		prevVelocity = velocity;
		if (partialTime > 0)
		{
			float num2 = num - partialTime;
			if (travelTime < num2)
			{
				prevPosition = position;
				prevVelocity = velocity;
				position += velocity * travelTime;
				partialTime += travelTime;
				return;
			}
			prevPosition = position;
			prevVelocity = velocity;
			position += velocity * num2;
			velocity += gravity * num;
			velocity -= velocity * (drag * num);
			travelTime -= num2;
		}
		int num3 = int(travelTime / num);
		for (int i = 0; i < num3; i++)
		{
			prevPosition = position;
			prevVelocity = velocity;
			position += velocity * num;
			velocity += gravity * num;
			velocity -= velocity * (drag * num);
		}
		partialTime = travelTime - num * (float)num3;
		if (partialTime > 0)
		{
			prevPosition = position;
			prevVelocity = velocity;
			position += velocity * partialTime;
		}
	}

	inline Vector3 SimulateProjectilezzzzz(Vector3& position, Vector3& velocity, float& partialTime, float travelTime, Vector3 gravity, float drag)
	{
		float num = 0.03125f;
		Vector3 origin = position;
		if (partialTime > 0)
		{
			float num2 = num - partialTime;
			if (travelTime < num2)
			{
				origin = position;
				position += velocity * travelTime;
				partialTime += travelTime;
				return origin;
			}
			origin = position;
			position += velocity * num2;
			velocity += gravity * num;
			velocity -= velocity * drag * num;
			travelTime -= num2;
		}

		int num3 = int(travelTime / num);

		for (int i = 0; i < num3; i++)
		{
			origin = position;
			position += velocity * num;
			velocity += gravity * num;
			velocity -= velocity * drag * num;
		}
		partialTime = travelTime - num * (float)num3;
		if (partialTime > 0)
		{
			origin = position;
			position += velocity * partialTime;
		}
		return origin;
	}

	inline Vector3 Simulatezzzzz(bool returnvelocity, bool sendtoserver) {
		Vector3 pos = sentPosition(); Vector3 prev = tumbleAxis(); float part = tumbleSpeed(); float travel = maxx(traveledTime() - closeFlybyDistance(), 0);

		Vector3 gr = UnityEngine::Physics::get_gravity(); //static Vector3 get_gravity();


		Vector3 origin = SimulateProjectilezzzzz(pos, prev, part, travel, gr * gravityModifier(), drag());

		if (sendtoserver) {
			sentPosition() = (pos);
			tumbleAxis() = (prev);
			tumbleSpeed() = (part);
			closeFlybyDistance() = (traveledTime());
		}

		if (returnvelocity) return prev;

		return origin;
	}

	AssemblyCSharp::HitInfo* CreateHitInfo(AssemblyCSharp::Projectile* projectile, ProtoBuf::PlayerProjectileAttack* playerProjectileAttack, AssemblyCSharp::HitTest* hTest, Vector3 HitPointWorld)
	{
		if (!InGame)
			return {};

		if (!IsAddressValid(playerProjectileAttack))
			return {};

		if (!IsAddressValid(projectile))
			return {};

		if (!IsAddressValid(hTest))
			return {};

		if (!IsAddressValid(Features().LocalPlayer))
			return {};

		auto camera = UnityEngine::Camera::get_main();
		if (!IsAddressValid(camera))
			return {};


		auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (!IsAddressValid(m_target.m_player))
			return {};

		
		static uintptr_t PlayerAttackClass = 0; if (!PlayerAttackClass) PlayerAttackClass = (uintptr_t)CIl2Cpp::FindClass(XS("ProtoBuf"), XS("PlayerAttack"));
		if (ProtoBuf::PlayerAttack* playerAttack = reinterpret_cast<ProtoBuf::PlayerAttack*>(CIl2Cpp::il2cpp_object_new((void*)PlayerAttackClass)))
		{
			playerProjectileAttack->playerAttack() = playerAttack;
			playerProjectileAttack->hitVelocity() = projectile->currentVelocity();
			playerProjectileAttack->hitDistance() = projectile->traveledDistance();
		}
		
		UnityEngine::Ray ray = UnityEngine::Ray(projectile->currentPosition(), (HitPointWorld - projectile->currentPosition()).UnityNormalize());

		playerProjectileAttack->playerAttack()->attack() = hTest->BuildAttackMessage(Features().LocalPlayer);
		playerProjectileAttack->playerAttack()->projectileID() = projectile->projectileID();

		static uintptr_t HitInfoClass = 0; if (!HitInfoClass) HitInfoClass = (uintptr_t)CIl2Cpp::FindClass(XS(""), XS("HitInfo"));
		if (AssemblyCSharp::HitInfo* hitInfo = reinterpret_cast<AssemblyCSharp::HitInfo*>(CIl2Cpp::il2cpp_object_new((void*)HitInfoClass)))
		{
			hitInfo->LoadFromAttack(playerProjectileAttack->playerAttack()->attack(), false);
			hitInfo->Initiator() = projectile->owner();
			hitInfo->ProjectileID() = projectile->projectileID();
			hitInfo->ProjectileDistance() = projectile->traveledDistance();
			hitInfo->ProjectileVelocity() = projectile->currentVelocity();
			hitInfo->ProjectilePrefab() = projectile->sourceProjectilePrefab();
			hitInfo->IsPredicting() = true;
			hitInfo->WeaponPrefab() = projectile->sourceWeaponPrefab();
			hitInfo->DoDecals() = projectile->createDecals();

			return hitInfo;
		}
		
	}

	class Line1 {
	public:

		float Clamp22(float value, float min, float max)
		{
			if (value < min)
			{
				value = min;
			}
			else if (value > max)
			{
				value = max;
			}
			return value;
		}

		float Dot(const Vector3& Vec1, const Vector3& Vec2)
		{
			return Vec1.x * Vec2.x + Vec1.y * Vec2.y + Vec1.z * Vec2.z;
		}


		Vector3 start;
		Vector3 end;
		Line1(Vector3 s, Vector3 e) {
			start = s; end = e;
		}
		Line1() { }
		Vector3 ClosestPoint(Vector3 pos)
		{
			Vector3 a = end - start;
			float magnitude = a.Length();
			if (magnitude == 0.f) return start;
			Vector3 vector = a / magnitude;
			return start + vector * Clamp22(Dot(pos - start, vector), 0.f, magnitude);
		}

		float Distance(Vector3 pos)
		{
			return (pos - ClosestPoint(pos)).UnityMagnitude();
		}
	};

	
	bool BulletTP(AssemblyCSharp::Projectile* instance, Vector3 NextCurrentPosition, Vector3 CurrentPosition, Vector3 CurrentVelocity, float deltaTime)
	{
		if (!InGame)
			return false;

		if (!IsAddressValid(instance))
			return false;

		if (!IsAddressValid(Features().LocalPlayer))
			return false;

		if (instance->projectileID() == 0)
			return false;

		if (instance->integrity() <= 0.f)
			return false;

	/*	auto projectile_fired_time = UnityEngine::Time::get_realtimeSinceStartup();

		if (projectile_fired_time < UnityEngine::Time::get_realtimeSinceStartup() - 8.f)
		{
			return false;
		}*/

		if (RPC_Counter.Calculate() > 100)
		{
			return false;
		}

		auto camera = UnityEngine::Camera::get_main();
		if (!IsAddressValid(camera))
			return false;


		auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (!IsAddressValid(m_target.m_player))
			return false;

		if (m_target.m_heli)
			return false;

		auto Line = NextCurrentPosition - CurrentPosition;
		auto LineLength = Line.UnityMagnitude();
		Line.UnityNormalize();

		auto CenterPosition = m_target.m_player->PivotPoint() + Vector3(0.f, 0.9f, 0.f);
		auto v = CenterPosition - CurrentPosition;
		auto d = v.Dot(Line);

		if (d < 0.0f)
		{
			d = 0.0f;
		}
		else if (d > LineLength)
		{
			d = LineLength;
		}

		auto OriginalClosestPointOnLine = CurrentPosition + Line * d;
		auto ClosestPointOnLine = OriginalClosestPointOnLine;

		auto ClosestPoint = m_target.m_player->ClosestPoint(ClosestPointOnLine);
		auto OriginalDistance = m_target.m_player->Distance(ClosestPointOnLine);
		auto Distance = OriginalDistance;

		Vector3 HitPointWorld = ClosestPoint;

		if (m_target.m_player->mounted())
		{
			if (Distance > 7.5f)
			{
				return false;
			}
		}
		else
		{
			if (Distance > 3.f)
			{
				return false;
			}
		}

		if (Distance > 1.2f)
		{
			auto endPositionTrajectoryUsage = Distance - 1.2f + 0.01f;
			auto amountNeeded = endPositionTrajectoryUsage / Distance;
			auto direction = HitPointWorld - ClosestPointOnLine;
			auto newPosition = ClosestPointOnLine + (direction * amountNeeded);

			if (ClosestPointOnLine.Distance(newPosition) > 1.f || !AssemblyCSharp::IsVisible_2(ClosestPointOnLine, newPosition, 10551296, 0.f))
				return false;

			ClosestPointOnLine = newPosition;
			Distance = m_target.m_player->Distance(ClosestPointOnLine);
		}

		if (Distance > 1.f)
		{
			auto playerDistanceUsage = minm(0.19f, Distance - 1.f);
			auto amountNeeded = 1.f - playerDistanceUsage / Distance;
			auto direction = HitPointWorld - ClosestPointOnLine;
			auto newPosition = ClosestPointOnLine + (direction * amountNeeded);

			HitPointWorld = newPosition;
		}

		int num15 = 2162688;
		num15 |= 8388608;
		num15 |= 134217728;

		if (!AssemblyCSharp::IsVisible_2(ClosestPointOnLine, HitPointWorld, 10551296, 0.f) || !AssemblyCSharp::IsVisible_2(CurrentPosition, OriginalClosestPointOnLine, 10551296, 0.f) ||
			!AssemblyCSharp::IsVisible_2(OriginalClosestPointOnLine, ClosestPointOnLine, 10551296, 0.f) || !AssemblyCSharp::IsVisible_2(CenterPosition, HitPointWorld, 10551296, 0.f))
		{
			return false;
		}

		static uintptr_t PlayerProjectileUpdateClass = 0; if (!IsAddressValid(PlayerProjectileUpdateClass)) PlayerProjectileUpdateClass = (uintptr_t)CIl2Cpp::FindClass(XS("ProtoBuf"), XS("PlayerProjectileUpdate"));

		instance->previousPosition() = instance->currentPosition();
		instance->currentPosition() = OriginalClosestPointOnLine;
		instance->traveledDistance() += instance->previousPosition().Distance(instance->currentPosition());
		instance->traveledTime() += instance->previousPosition().Distance(instance->currentPosition()) / CurrentVelocity.Length();

		if (ProtoBuf::PlayerProjectileUpdate* playerProjectileUpdate = reinterpret_cast<ProtoBuf::PlayerProjectileUpdate*>(CIl2Cpp::il2cpp_object_new((void*)PlayerProjectileUpdateClass)))
		{
			playerProjectileUpdate->projectileID() = instance->projectileID();
			playerProjectileUpdate->travelTime() = instance->traveledTime();
			playerProjectileUpdate->curVelocity() = instance->currentVelocity();
			playerProjectileUpdate->curPosition() = instance->currentPosition();

			Vector3 position2 = instance->currentPosition();
			Vector3 curPosition = playerProjectileUpdate->curPosition();
			Vector3 b2 = (curPosition - position2).UnityNormalize() * 0.01f;

			int num14 = 2162688;
			num14 |= 8388608;
			num14 |= 134217728;

			if (!AssemblyCSharp::GamePhysics::LineOfSight(position2 - b2, curPosition + b2, num14, nullptr))
			{
				return false;
			}

			instance->owner()->SendProjectileUpdate(playerProjectileUpdate);
			RPC_Counter.Increment();

			if (m_settings::Thickbullet_Arrows)
			{
				UnityEngine::DDraw().Arrow(instance->previousPosition(), instance->currentPosition(), 0.1f, Color(0.f, 1.f, 0.f, 1.f), 30.f);
			}
		}

		instance->previousPosition() = instance->currentPosition();
		instance->currentPosition() = ClosestPointOnLine;
		instance->traveledDistance() += instance->previousPosition().Distance(instance->currentPosition());
		instance->traveledTime() += instance->previousPosition().Distance(instance->currentPosition()) / CurrentVelocity.Length();

		if (ProtoBuf::PlayerProjectileUpdate* playerProjectileUpdate = reinterpret_cast<ProtoBuf::PlayerProjectileUpdate*>(CIl2Cpp::il2cpp_object_new((void*)PlayerProjectileUpdateClass)))
		{
			playerProjectileUpdate->projectileID() = instance->projectileID();
			playerProjectileUpdate->travelTime() = instance->traveledTime();
			playerProjectileUpdate->curVelocity() = instance->currentVelocity();
			playerProjectileUpdate->curPosition() = instance->currentPosition();

			Vector3 position2 = instance->currentPosition();
			Vector3 curPosition = playerProjectileUpdate->curPosition();
			Vector3 b2 = (curPosition - position2).UnityNormalize() * 0.01f;

			int num14 = 2162688;
			num14 |= 8388608;
			num14 |= 134217728;

			if (!AssemblyCSharp::GamePhysics::LineOfSight(position2 - b2, curPosition + b2, num14, nullptr))
			{
				return false;
			}

			instance->owner()->SendProjectileUpdate(playerProjectileUpdate);
			RPC_Counter.Increment();

			if (m_settings::Thickbullet_Arrows)
			{
				UnityEngine::DDraw().Arrow(instance->previousPosition(), instance->currentPosition(), 0.1f, Color(1.f, 0.f, 0.f, 1.f), 30.f);
			}
		}
		AssemblyCSharp::HitTest* hTest = instance->hitTest();
		if (!IsAddressValid(hTest))
		{
			auto g_hit_test_class = AssemblyCSharp::HitTest::StaticClass();
			hTest = (AssemblyCSharp::HitTest*)CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);
		}

		if (HitPointWorld == instance->currentPosition())
		{
			HitPointWorld.y += 0.01f;
		}

		UnityEngine::Ray ray = UnityEngine::Ray(instance->currentPosition(), (HitPointWorld - instance->currentPosition()).UnityNormalize());

		hTest->MaxDistance() = 1000.0f;
		hTest->AttackRay() = ray;
		hTest->DidHit() = true;
		hTest->HitTransform() = m_target.m_player->get_bone_transform(m_target.m_bone);
		hTest->HitEntity() = m_target.m_player;
		hTest->HitPoint() = hTest->HitTransform()->InverseTransformPoint(HitPointWorld);
		hTest->HitNormal() = hTest->HitTransform()->InverseTransformDirection(HitPointWorld);
		hTest->damageProperties() = instance->damageProperties();
		hTest->HitMaterial() = CIl2Cpp::il2cpp_string_new(XS("Flesh"));

		static uintptr_t PlayerProjectileAttack = 0; if (!IsAddressValid(PlayerProjectileAttack)) PlayerProjectileAttack = (uintptr_t)CIl2Cpp::FindClass(XS("ProtoBuf"), XS("PlayerProjectileAttack"));
		if (ProtoBuf::PlayerProjectileAttack* playerProjectileAttack = reinterpret_cast<ProtoBuf::PlayerProjectileAttack*>(CIl2Cpp::il2cpp_object_new((void*)PlayerProjectileAttack)))
		{
			const auto HitInfo = CreateHitInfo(instance, playerProjectileAttack, hTest, HitPointWorld);
			if (IsAddressValid(HitInfo))
			{
				Vector3 vector2 = HitInfo->PositionOnRay(HitPointWorld);

				Vector3 position2 = instance->currentPosition();
				const auto pointStart = HitInfo->PointStart();
				Vector3 b2 = (pointStart - position2).UnityNormalize() * 0.01f;
				Vector3 b3 = (vector2 - pointStart).UnityNormalize() * 0.01f;
				Vector3 vector = HitInfo->HitPositionWorld();

				bool flag10 = AssemblyCSharp::GamePhysics::LineOfSight(position2 - b2, pointStart + b2, num15, nullptr) &&
					AssemblyCSharp::GamePhysics::LineOfSight(pointStart - b3, vector2, num15, nullptr) && AssemblyCSharp::GamePhysics::LineOfSight(vector2, vector, num15, nullptr);;
				if (!flag10)
					return false;

				Vector3 hitPositionWorld = HitInfo->HitPositionWorld();


				//LOS invalids fix?
				// Features().LocalPlayer->eyes()->get_position() + Features().CachedManipPoint;

				Vector3 position3 = HitPointWorld;
				Vector3 vector4 = instance->owner()->WorldSpaceBounds().position;
				float projectile_losforgiveness = 0.2f;
				bool flag11 = AssemblyCSharp::IsVisible_2(hitPositionWorld, position3, num15, projectile_losforgiveness) && AssemblyCSharp::IsVisible_2(position3, hitPositionWorld, num15, projectile_losforgiveness);
				if (!flag11)
				{
					flag11 = (AssemblyCSharp::IsVisible_2(hitPositionWorld, vector4, num15, projectile_losforgiveness) && AssemblyCSharp::IsVisible_2(vector4, hitPositionWorld, num15, projectile_losforgiveness));
				}

				if (!flag11)
					return false;

				/////////////////////////////////////

				/*bool isUsingManip = m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey);
				Vector3 position3 = HitPointWorld;
				Vector3 vector4 = Features().LocalPlayer->WorldSpaceBounds().position;
				float projectile_losforgiveness = 0.2f;
				bool flag11 = AssemblyCSharp::IsVisible_2(hitPositionWorld, position3, num15, projectile_losforgiveness) && AssemblyCSharp::IsVisible_2(position3, hitPositionWorld, num15, projectile_losforgiveness);
				if (!flag11)
				{
					flag11 = (AssemblyCSharp::IsVisible_2(hitPositionWorld, vector4, num15, projectile_losforgiveness) && AssemblyCSharp::IsVisible_2(vector4, hitPositionWorld, num15, projectile_losforgiveness));
				}

				if (!flag11)
					return false;*/

				//other invalid checks
				//player_distance
				
				float timeSinceLastTick = (UnityEngine::Time::get_realtimeSinceStartup() - Features().LocalPlayer->lastSentTickTime());
				float last_tick_time = maxx(0.f, minm(timeSinceLastTick, 1.f));

				float num = 1.5f;
				float eye_clientframes = 2.0f;
				float eye_serverframes = 2.0f;
				float num2 = eye_clientframes / 60.f;
				float num3 = eye_serverframes * Max3(UnityEngine::Time::get_deltaTime(), UnityEngine::Time::get_smoothDeltaTime(), UnityEngine::Time::get_fixedDeltaTime());
				float num4 = (last_tick_time + num2 + num3) * num;

				float num5 = Features().LocalPlayer->MaxEyeVelocity() + Features().LocalPlayer->GetParentVelocity().Magnitude();
				float num6 = Features().LocalPlayer->BoundsPadding() + num4 * num5;

				if (instance->sourceWeaponPrefab()->IsA(AssemblyCSharp::BowWeapon::StaticClass()))
				{
					if (IsAddressValid(hTest->HitEntity()))
					{
						AssemblyCSharp::BaseEntity* basePlayer = hTest->HitEntity();

						float magnitude = basePlayer->GetParentVelocity().UnityMagnitude();
						float num19 = basePlayer->BoundsPadding() + num4 * magnitude + 0.1f;
						float num20 = basePlayer->Distance(HitInfo->HitPositionWorld());
						if (num20 > num19)
						{
							if (m_settings::ShotIndicators) {
								const auto string = std::wstring(XS(L"[Serotonin] Missed shot due to player_distance!"));
								notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
							}
							return false;
						}

					}
					
					float num16 = hTest->HitEntity()->MaxVelocity() + hTest->HitEntity()->GetParentVelocity().UnityMagnitude();
					float num17 = hTest->HitEntity()->BoundsPadding() + num4 * num16;
					float num18 = hTest->HitEntity()->Distance(HitInfo->HitPositionWorld());
					if (num18 > num17)
					{
						if (m_settings::ShotIndicators) {
							const auto string = std::wstring(XS(L"[Serotonin] Missed shot due to entity_distance!"));
							notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
						}
						return false;
					}
				}


				float travel = maxx(traveledTime() - closeFlybyDistance(), 0);
				Vector3 gr = UnityEngine::Physics::get_gravity(); //static Vector3 get_gravity();


				////trajectory_invalids
				Vector3 a;
				Vector3 b;
				SimulateProjectile(instance->currentPosition(), instance->currentVelocity(), tumbleSpeed(), travel, gr * gravityModifier(), drag(), a, b);

				Vector3 positionOffset = Vector3();
				float num25 = 0.f;
				if (hTest->HitEntity() != nullptr)
				{
					float num26 = hTest->HitEntity()->GetParentVelocity().UnityMagnitude();
					if (hTest->HitEntity()->class_name() == XS("TugBoat"))
					{
						num26 += hTest->HitEntity()->MaxVelocity();
					}
					num25 = num6 * num26;
				}

				Line1 line_1 = Line1(a - b, currentPosition() + b);
				float num27 = max(line_1.Distance(HitInfo->PointStart()) - positionOffset.UnityMagnitude() - num25, 0.f);
				float num28 = max(line_1.Distance(HitInfo->HitPositionWorld()) - positionOffset.UnityMagnitude() - num25, 0.f);

				if (num27 > 1.f)
				{
					if (m_settings::ShotIndicators) {
						const auto string = std::wstring(XS(L"[Serotonin] Missed shot due to trajectory_start!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
					}
					return false;
				}

				if (num28 > 1.f)
				{
					if (m_settings::ShotIndicators) {
						const auto string = std::wstring(XS(L"[Serotonin] Missed shot due to trajectory_end!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
					}
					return false;
				}

				bool flag6 = hTest->HitEntity() != nullptr;
				float num14 = Vector3().Distance(instance->currentPosition(), HitInfo->HitPositionWorld());
				float num21 = flag6 ? (hTest->HitEntity()->MaxVelocity() + hTest->HitEntity()->GetParentVelocity().UnityMagnitude()) : 0.f;
				float num22 = flag6 ? (num6 * num21) : 0.f;
				float num24 = HitInfo->ProjectileDistance() + 1.f + positionOffset.UnityMagnitude() + num22;

				if (num14 > num24)
				{
					if (m_settings::ShotIndicators) {
						const auto string = std::wstring(XS(L"[Serotonin] Missed shot due to projectile_distance!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
					}
					return false;
				}
			}

		}
		
		if (m_settings::Thickbullet_Arrows)
		{
			UnityEngine::DDraw().Arrow(instance->currentPosition(), HitPointWorld, 0.1f, Color(0.f, 0.f, 1.f, 1.f), 30.f);
			UnityEngine::DDraw().Arrow(HitPointWorld, m_target.m_player->ClosestPoint(HitPointWorld), 0.1f, Color(1.f, 1.f, 0.f, 1.f), 30.f);
		}

		instance->DoHit(hTest, hTest->HitPoint(), hTest->HitNormal()); //hTest->HitNormal()
		return true;
	}

	inline float GetHitDist() {
		float travel = traveledTime();

		float num6 = (travel + 2 / 60 + 0.03125f) * 1.5f;
		float maxdist = 0.1f + num6 * 5.5f;
		return maxdist;
	}


	inline bool DoFatBulletHit(Projectile_c* pr, Vector3 point) {
		float maxDist = GetHitDist();
		auto target = AssemblyCSharp::BasePlayer::GetAimbotTarget(point, maxDist);

		if (pr->IsAlive() && target.m_player && !target.m_team || target.m_heli) {
			if (!AssemblyCSharp::IsVisible(target.m_position, point)) {
				return false;
			}

			auto ht = hitTest();

			safe_write(ht + 0x66, true, bool); //DidHit
			safe_write(ht + 0x88, (DWORD64)target.m_player, DWORD64); //HitEntity
			UnityEngine::Transform* Transform;

			if (!target.m_heli) {
				Transform = target.m_player->get_bone_transform(target.m_bone);
			}
			else
			{
				Transform = target.m_player->get_bone_transform(19);
			}

			if (!IsAddressValid(Transform))
				return false;

			safe_write(ht + 0xB0, (uintptr_t)Transform, DWORD64);

			Vector3 hitpoint = Transform->InverseTransformPoint(point);
			safe_write(ht + 0x90, hitpoint, Vector3); //hitPoint
			safe_write(ht + 0x14, point, Vector3);


			AssemblyCSharp::HitTest* test = (AssemblyCSharp::HitTest*)ht;
			bool result = pr->DoHit(test, point, Vector3());
			//Sphere(point, 0.015f, col(1, 0, 0, 1), 20, true);
			return true;
		}
		return false;
	}

	inline void UpdateHitTest(TraceInfo info) {
		auto ht = hitTest();

		safe_write(ht + 0x66, true, bool); //DidHit
		safe_write(ht + 0x88, info.entity, DWORD64); //HitEntity
		safe_write(ht + 0xA8, info.distance, float); //HitDistance

		if (info.material != 0) {
			FPSystem::String* material = (AssemblyCSharp::AssetNameCache::GetName(info.material));
			safe_write(ht + 0xC0, material, FPSystem::String*); //HitMaterial  
		}

		safe_write(ht + 0xB8, info.partID, unsigned int); //HitPart
		safe_write(ht + 0xB0, info.bone, DWORD64); //HitTransform
		safe_write(ht + 0x90, info.point, Vector3); //HitPoint
		safe_write(ht + 0x9C, info.normal, Vector3); //HitNormal
		safe_write(ht + 0x78, info.collider, DWORD64); //collider


		auto go = (info.collider) ? reinterpret_cast<UnityEngine::Component*>(info.collider)->get_gameObject() : reinterpret_cast<UnityEngine::Component*>(info.bone)->get_gameObject();

		safe_write(ht + 0x70, go, UnityEngine::GameObject*); //gameObject
		if (info.bone != 0) {

			auto htt = safe_read(ht + 0xB0, UnityEngine::Transform*);
			Vector3 hitpoint = htt->InverseTransformPoint(info.point);
			safe_write(ht + 0x90, hitpoint, Vector3); //hitPoint

			Vector3 normalpoint = htt->InverseTransformDirection(info.normal);
			safe_write(ht + 0x9C, normalpoint, Vector3); //HitNormal
		}

	}
	inline bool DoHit2(Projectile_c* pr, DWORD64 ht, Vector3 point, Vector3 normal, TraceInfo info, bool& exit) {
		bool result = false;
		if (!IsAlive())
			return result;

		auto material = info.material != 0 ? AssemblyCSharp::AssetNameCache::GetName(info.material)->c_str() : (XS(L"generic"));

		bool canIgnore = AssemblyCSharp::IsVisible(sentPosition(), currentPosition() + currentVelocity().Normalized() * 0.01f);
		if (!canIgnore) {
			integrity() = (0);
			return true;
		}

		float org;
		if (canIgnore) {
			Vector3 attackStart = Simulatezzzzz(false, true);

			safe_write(ht + 0x14, UnityEngine::Ray(attackStart, Vector3()), UnityEngine::Ray);
		}

		if (canIgnore && String::wcscmp(material, XS(L"Flesh"))) {
			DWORD64 Tra = safe_read(ht + 0xB0, DWORD64);
			if (IsAddressValid(Tra)) {
				auto st = XS("head");
				reinterpret_cast<UnityEngine::Transform*>(Tra)->set_name(st);
			}

			result = pr->DoHit((AssemblyCSharp::HitTest*)ht, point, normal);
			sentPosition() = (currentPosition());

		}
		return result;
	}

	inline bool DoMovement(float deltaTime, Projectile_c* pr) {
		if (!IsAddressValid(this))
			return false;

		if (!IsAddressValid(pr))
			return false;

		if (!IsAddressValid(Features().LocalPlayer))
			return false;

		AssemblyCSharp::BasePlayer* m_Owner = pr->owner();
		if (!IsAddressValid(m_Owner))
			return false;

		if (m_Owner->userID() != Features().LocalPlayer->userID())
			return false;


		Vector3 a = currentVelocity() * deltaTime;
		float magnitude = a.Length();
		float num2 = 1 / magnitude;
		Vector3 vec2 = a * num2;
		bool flag = false;

		Vector3 vec3 = currentPosition() + vec2 * magnitude;
		float num3 = traveledTime() + deltaTime;

		float v38 = deltaTime + this->traveledTime();

		auto ht = hitTest();
		if (!ht) {
			/*HitTest_TypeInfo*/

			auto g_hit_test_class = AssemblyCSharp::HitTest::StaticClass();
			auto g_hit_test = CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);
			ht = (AssemblyCSharp::HitTest*)g_hit_test;
			hitTest() = (AssemblyCSharp::HitTest*)g_hit_test;
		}
		UnityEngine::Ray ray = UnityEngine::Ray(currentPosition(), vec2);
		ht->AttackRay() = ray;
		ht->MaxDistance() = magnitude;
	
		AssemblyCSharp::BasePlayer* ow = this->owner();
		ht->ignoreEntity() = ow;
		ht->Radius() = 0.f;
		ht->Forgiveness() = 0.5f;


		if (!pr->owner() || ow->userID() == pr->owner()->userID()) {
			ht->type() = 0x2;
		}
		else ht->type() = 0x1; //Type	`

		if (sourceWeaponPrefab()) {
			ht->BestHit() = true;
			ht->damageProperties() = damageProperties();
		}
	OFFSET:
		typedef DWORD64(__stdcall* Unknown)(DWORD64);
		DWORD64 st = safe_read(m_game_assembly + 54962184, DWORD64); //Method$Facepunch.Pool.GetList\u003CTraceInfo\u003E() address
		if (!IsAddressValid(st)) 
		{
			goto OFFSET;
		}

		Unknown get_list = (Unknown)(m_game_assembly + 19250656);//Method$Facepunch.Pool.GetList\u003CTraceInfo\u003E() MethodAddress
		if (!IsAddressValid(get_list))
		{
			goto OFFSET;
		}

		DWORD64 rs = get_list(st);
		if (!IsAddressValid(rs))
		{
			goto OFFSET;
		}


		int layerMask = 1270440721;

		if (m_settings::PierceMaterials)
		{
			layerMask &= ~256; //Deployed
			layerMask &= ~1; //Default
			layerMask &= ~1073741824; //tree
			layerMask &= ~16; //Water
			layerMask &= ~134217728; //Vehicle_Large
			layerMask &= ~32768; //Vehicle_World
			layerMask &= ~8192; //Vehicle_Detailed
			layerMask &= ~1073741824; //tree
		}

		AssemblyCSharp::GameTrace::TraceAll(ToAddress(ht), rs, layerMask /*mask*/);

		static bool traceall = false;


		ht = hitTest();
		ht->MaxDistance() = 0.f;


		int size = safe_read(rs + 0x18, int);

		DWORD64 lst = safe_read(rs + 0x10, DWORD64);

		auto camera = UnityEngine::Camera::get_main();
		if (!IsAddressValid(camera))
			return false;

		auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
		if (!IsAddressValid(m_target.m_player))
			return false;

		float real_travel_time = this->traveledTime();
		Vector3 vel = this->currentVelocity();

		if (m_target.m_player->mounted() || m_target.m_heli)
		{
			if (DoFatBulletHit(pr, currentPosition()))
			{
				RPC_Counter.Reset();

				this->currentVelocity() = (vel);
				this->traveledTime() = (real_travel_time);
				integrity() = (0);
				flag = true;
				return false;
			}
		}
		else
		{
			if (BulletTP(this, vec3, currentPosition(), currentVelocity(), deltaTime))
			{
				RPC_Counter.Reset();
				integrity() = (0);
				flag = true;
				////this->Retire();
				return false;
			}
		}

		for (int i = 0; i < size && this->IsAlive() && !flag; i++) {
			TraceInfo Trace = safe_read(lst + 0x20 + (i * sizeof(TraceInfo)), TraceInfo);
			if (Trace.valid) {
				this->UpdateHitTest(Trace);

				Vector3 vec4 = reinterpret_cast<AssemblyCSharp::HitTest*>(ht)->HitPointWorld(); //Vector3 HitPointWorld();
				Vector3 normal = reinterpret_cast<AssemblyCSharp::HitTest*>(ht)->HitNormalWorld(); //Vector3 HitNormalWorld();

				float magnitude2 = (vec4 - currentPosition()).Length();
				float num5 = magnitude2 * num2 * deltaTime;

				traveledDistance() = (traveledDistance() + magnitude2);
				traveledTime() = (traveledTime() + num5);
				currentPosition() = (vec4);

				bool exit = false;
				if (this->DoHit(ht, vec4, normal))
					flag = true;

				if (exit) {
					return true;
				}
			}
		}

		if (this->integrity() > 0.001 && this->maxDistance() > this->traveledDistance())
		{
			if (flag && traveledTime() < num3)
			{
				DoMovement(num3 - traveledTime(), this);
				return false;
			}


			if (!flag && this->IsAlive()) {
				float magnitude3 = (vec3 - currentPosition()).Length();
				float num6 = magnitude3 * num2 * deltaTime;
				traveledDistance() = (traveledDistance() + magnitude3);
				traveledTime() = (traveledTime() + num6);
				currentPosition() = (vec3);
			}
		}

		

		return false;
	}
	inline void DoVelocityUpdate(float deltaTime) {
		if (!this)
			return;

		Vector3 gr = UnityEngine::Physics::get_gravity(); //static Vector3 get_gravity();

		Vector3 tr = (gr * gravityModifier() * deltaTime);
		currentVelocity() = (currentVelocity() + tr);

		Vector3 dr = (currentVelocity() * drag() * deltaTime);
		currentVelocity() = (currentVelocity() - dr);
	}
};
