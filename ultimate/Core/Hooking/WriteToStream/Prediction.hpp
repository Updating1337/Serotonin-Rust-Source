#pragma once

#include "../Hooks.hpp"


using AssemblyCSharp::BasePlayer;
using AssemblyCSharp::ItemModProjectile;
using AssemblyCSharp::BaseProjectile;
using AssemblyCSharp::Projectile;
inline float InitialDistanceDebug = 0.f;
inline bool CalledLaunchFromHook = false;
inline AssemblyCSharp::Projectile* LaunchedProjectilesArray[256];
inline size_t LaunchedProjectileSize;
inline bool InstantHitReady = false;

inline void SimulateProjectile(BasePlayer* target,
	Vector3 rpc_position,
	Vector3 target_pos,
	Vector3& aimbot_velocity,
	Vector3& _aimdir,
	float& travel_t,
	Projectile* p,
	BaseProjectile* heldEntity,
	ItemModProjectile* mod,
	Vector3 average_velo) {

	Vector3 gravity = UnityEngine::Physics::get_gravity();
	float deltatime = UnityEngine::Time::get_deltaTime();
	float timescale = UnityEngine::Time::get_timeScale();
	float drag = p->drag();
	float grav = p->gravityModifier();
	float stepSize = 0.98f;

	Vector3 targetPosition = target_pos;
	Vector3 offset = Vector3(0, 0, 0);

	Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector3 player_velocity = Vector3(0, 0, 0);
	std::vector<Vector3> path;
	int simulations = 0;

	while (simulations < 50) {
		travel_t = 0.f;
		Vector3 pos = rpc_position;
		Vector3 origin = pos;
		float num = deltatime * timescale;
		float num3 = 8.f / num;

		_aimdir = (targetPosition - rpc_position).Normalized() * stepSize;
		Vector3 velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale(false);

		for (size_t i = 0; i < num3; i++) {
			origin = pos;
			pos += velocity * num;
			velocity += gravity * grav * num;
			velocity -= velocity * drag * num;
			travel_t += num;

			Vector3 line = (origin - pos);
			float len = line.UnityMagnitude();
			line.UnityNormalize();
			Vector3 v = target_pos - pos;
			float d = line.Dot(v);

			d = CLAMP(d, 0.f, len);
			Vector3 nearestPoint = pos + line * d;

			if (nearestPoint.Distance(target_pos) < 0.01f) {
				aimbot_velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale(false);
				aimbot_velocity += gravity * grav * num;
				aimbot_velocity -= velocity * drag * num;
				break;
			}
			else if (nearestPoint.Distance(target_pos) < closestPoint.Distance(target_pos)) {
				closestPoint = nearestPoint;
				offset = target_pos - nearestPoint;
			}
		}
		targetPosition += offset;
		simulations++;
		if (!aimbot_velocity.IsZero())
			break;
	}

	if (!average_velo.IsZero() && travel_t > 0.f && target) {
		float num = deltatime * timescale;
		int num3 = static_cast<int>(8.f / num);

		std::vector<Vector3> velocity_list = {};
		float last_frame = 0.f;
		float next_frame = last_frame + UnityEngine::Time::get_deltaTime();
		if (UnityEngine::Time::get_fixedTime() > next_frame)
		{
			//new frame, record velocity, record frame
			last_frame = UnityEngine::Time::get_fixedTime();
			if (velocity_list.size() < 30) //0.03125 * 30 = 0.9 seconds
				velocity_list.push_back(average_velo);
			else
			{
				velocity_list.pop_back();
				velocity_list.insert(velocity_list.begin(), 1, average_velo);
			}
			float avgx = 0.f;
			float avgy = 0.f;
			float avgz = 0.f;
			int count = 0;
			for (auto v : velocity_list)
			{
				if (v.IsZero()) break;
				avgx += v.x;
				avgy += v.y;
				avgz += v.z;
				count += 1;
			}
			avgx /= count; avgy /= count; avgz /= count;

			average_velo = Vector3().Lerp(average_velo, Vector3(avgx, avgy, avgz), 0.1f);
		}

		Vector3 final_vel = average_velo * travel_t;
		Vector3 actual = target_pos + final_vel;

		Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);

		while (simulations < 50) {
			travel_t = 0.f;
			Vector3 pos = rpc_position;
			Vector3 origin = pos;

			_aimdir = (targetPosition - rpc_position).Normalized() * stepSize;
			Vector3 velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale(false);

			for (size_t i = 0; i < num3; i++) {
				origin = pos;
				pos += velocity * num;
				velocity += gravity * grav * num;
				velocity -= velocity * drag * num;
				travel_t += num;

				Vector3 line = (origin - pos);
				float len = line.UnityMagnitude();
				line.UnityNormalize();
				Vector3 v = actual - pos;
				float d = line.Dot(v);

				d = CLAMP(d, 0.f, len);
				Vector3 nearestPoint = pos + line * d;

				if (nearestPoint.Distance(actual) < 0.01f) {
					aimbot_velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale(false);
					aimbot_velocity += gravity * grav * num;
					aimbot_velocity -= velocity * drag * num;
					break;
				}
				else if (nearestPoint.Distance(actual) < closestPoint.Distance(actual)) {
					closestPoint = nearestPoint;
					offset = actual - nearestPoint;
				}
			}
			targetPosition += offset;
			simulations++;
			if (!aimbot_velocity.IsZero())
				break;
		}
	}
}


inline Vector3 GetAimDirectionToTarget(BasePlayer* Local, BaseProjectile* Projectile, Vector3 TargetPosition, Vector3 TargetVelocity, ItemModProjectile* mod, Vector3 EyesPosition)
{
	if (!InGame)
		return Vector3();

	if (!IsAddressValid(Local))
		return Vector3();

	if (!IsAddressValid(Projectile))
		return Vector3();

	if (!IsAddressValid(mod))
		return Vector3();

	if (Projectile->IsA(AssemblyCSharp::Planner::StaticClass()))
		return Vector3();

	if (Projectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()))
		return Vector3();




	auto fVelocity = mod->projectileVelocity();
	auto fVelocityScale = Projectile->GetProjectileVelocityScale(false) * (1.f);
	auto fProjectilePrefab = mod->projectileObject()->Get()->GetComponent<AssemblyCSharp::Projectile>(FPSystem::Type::Projectile());
	auto fDrag = fProjectilePrefab->drag();
	auto fGraviModifier = fProjectilePrefab->gravityModifier();
	auto vGravity = Vector3(0.f, -9.81f, 0.f);

	auto fFinalVelocity = fVelocity * fVelocityScale;
	auto vTrueGravity = vGravity * fGraviModifier;

	Vector3 TemporaryTargetPosition = TargetPosition;

	// 30 Sims
	for (size_t j = 0; j < 50; j++)
	{
		Vector3 Direction = (TemporaryTargetPosition - EyesPosition).Normalized();

		Vector3 Velocity = Direction * fFinalVelocity;

		Vector3 CurrentPosition = EyesPosition;
		Vector3 PreviousPosition = CurrentPosition;

		Vector3 MissedOffset = { 0, 0, 0 };
		Vector3 ClosestPoint(FLT_MAX, FLT_MAX, FLT_MAX);

		Vector3 SimulatedTargetPosition = TargetPosition;
		float SimulatedTargetTime = 0.f;

		Vector3 initialPosition = CurrentPosition;
		float initalDistance = fProjectilePrefab->initialDistance();


		if (m_settings::InstantBullet)
		{
			auto desyncTimeClamped = minm(UnityEngine::Time::get_realtimeSinceStartup() - Local->lastSentTickTime(), 1.f);
			auto desyncTimeClampedServer = maxx(desyncTimeClamped - 0.03125f * 5.f, 0.2f);
			float num11 = desyncTimeClampedServer;
			float distanceToTarget = CurrentPosition.Distance(TemporaryTargetPosition);// this should be changed to total project air distance due to arc
			float magnitude2 = Velocity.Magnitude();
			initalDistance = fProjectilePrefab->initialDistance() + num11 * magnitude2;
			InitialDistanceDebug = initalDistance;
		}

		size_t TotalSteps = static_cast<size_t>(8.0f / 0.03125f);

		for (size_t Step = 0; Step < TotalSteps; Step++)
		{
			PreviousPosition = CurrentPosition;

			// move our current position by the velocity
			//
			CurrentPosition += (Velocity * 0.03125f);

			// Modify our velocity by gravity, since gravity is generally a vector of 0, -9.81, 0 per second,
			// and deltaTime is probably .03125 seconds, we are basically reducing Velocity y axis by adding a negative number
			//
			Velocity += (vTrueGravity * 0.03125f);

			// We are now reducing all 3 axis of velocity by itself multiply by drag value
			// fDrag is just a multiplier of velocity per second and since it is the opposite of the current
			// velocity, we are subtracting
			//
			Velocity -= (Velocity * fDrag * 0.03125f);

			// Line here is the direction that points the previous position
			// toward the current position, so it is this calculation frame frame's segment's vector


			auto Line = CurrentPosition - PreviousPosition;

			if (initialPosition.Distance(CurrentPosition) > initalDistance || InitialDistanceDebug == 0.f)
			{
				// Simulating future player position based off current travelTime
				//
				SimulatedTargetTime += 0.03125f;
				SimulatedTargetPosition = (TargetPosition + (TargetVelocity * (SimulatedTargetTime)));
			}
			else
			{
				SimulatedTargetPosition = TargetPosition;
			}

			// Magnitude here is basically the change of the current line across all 3 axis
			//
			auto LineLength = Line.Magnitude();
			Line.UnityNormalize();
			auto v = SimulatedTargetPosition - PreviousPosition;
			auto d = v.Dot(Line);

			if (d < 0.0f)
			{
				d = 0.0f;
			}
			else if (d > LineLength)
			{
				d = LineLength;
			}

			Vector3 CurrentPoint = PreviousPosition + Line * d;

			float DistanceMissed = CurrentPoint.Distance(SimulatedTargetPosition);

			// If our Nearest point is practically ON the target, then that mean we can hit the entity with this aimAngle
			//
			if (DistanceMissed < 0.1f)
			{
				// Total amount of time the bullet traveled for to arrive at this point
				//
				ClosestPoint = CurrentPoint;

				return TemporaryTargetPosition;
			}

			// If this misses our target but it is a closer point in the path, save it
			//
			else if (DistanceMissed < ClosestPoint.Distance(SimulatedTargetPosition))
			{
				// How far is this point from the target (as the sim go on, it will get closer and closer)
				//
				MissedOffset = SimulatedTargetPosition - CurrentPoint;
				ClosestPoint = CurrentPoint;
			}
		}

		TemporaryTargetPosition += MissedOffset;
	}

	return Vector3();
}
