#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"
#include "../WriteToStream/Prediction.hpp"

double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity, float drag) {
	//	velocity *= 1 - 0.015625f * drag;

	double pitch = (Math::atan2f(height, DepthPlayerTarget));
	double BulletVelocityXY = velocity * Math::cosf(pitch);

	double Time = DepthPlayerTarget / BulletVelocityXY;
	double TotalVerticalDrop = (0.5f * gravity * Time * Time) * (1 - 0.015625f * drag);
	return TotalVerticalDrop * 10;
}

void Prediction(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity, float drag) {

	float Dist = local.get_3d_dist(target);
	float BulletTime = Dist / bulletspeed;

	Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;

	Vector3 PredictVel = vel * BulletTime;

	target += PredictVel;

	double height = target.y - local.y;
	Vector3 dir = target - local;
	float DepthPlayerTarget = Math::sqrtf(powFFFFFFFFFFFFFFFFFFFFFF(dir.x) + powFFFFFFFFFFFFFFFFFFFFFF(dir.z));

	float drop = CalcBulletDrop(height, DepthPlayerTarget, bulletspeed, gravity, drag);

	target.y += drop;
}

void Prediction2(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity, float drag) {
	float Dist = local.get_3d_dist(target);
	float BulletTime = Dist / bulletspeed;

	Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;
	Vector3 PredictVel = vel * BulletTime;
	target += PredictVel;

	double height = target.y - local.y;
	Vector3 dir = target - local;
	float DepthPlayerTarget = Math::sqrtf(Math::powf(dir.x, 2) + Math::powf(dir.z, 2));

	float drop = CalcBulletDrop(height, DepthPlayerTarget, bulletspeed, gravity, drag);
	target.y += drop;
}

void Hooks::OnInput(AssemblyCSharp::BaseMelee* _This)
{
	if (!InGame)
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	if (!m_settings::MeleeAimbot)
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	if (!_This)
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);
	}

	if (_This->HasAttackCooldown())
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	if (!_This->IsFullyDeployed())
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	auto camera = AssemblyCSharp::LocalPlayer::get_Entity()->eyes();
	if (!IsAddressValid(camera))
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_position(), 500.f);
	if (!IsAddressValid(m_target.m_player))
		return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);

	if (Features().BulletTPAngle.IsZero())
	{
		Features().BulletTPAngle = m_target.m_position;
	}

	auto info = _This->GetOwnerItemDefinition();

	auto component = reinterpret_cast<AssemblyCSharp::ItemModProjectile*>(info->GetComponent(FPSystem::Type::ItemModProjectile()));

	auto currentProjectileSpread = component->projectileSpread();
	auto currentBodyRotation = AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->bodyRotation();
	auto currentTransformPosition = AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position();
	auto projectileComponent = component->projectileObject()->Get()->GetComponent<AssemblyCSharp::Projectile>(FPSystem::Type::Projectile());

	auto localPlayer = Features().LocalPlayer;
//	Vector3 OriginalPos = Features().LocalPlayer->eyes()->viewOffset();

	if (IsAddressValid(localPlayer)) {
		auto playerInput = localPlayer->input();
		auto inputState = playerInput->state();

		if (IsAddressValid(component)) {
			if (component->projectileSpread() != 0.f)
				component->projectileSpread() = 0.f;

			if (component->projectileVelocitySpread() != 0.f)
				component->projectileVelocitySpread() = 0.f;
		}

		
		if (IsAddressValid(inputState)) {

			auto fGraviModifier = projectileComponent->gravityModifier();
			auto vGravity = Vector3(0.f, -9.81f, 0.f);
			auto vTrueGravity = vGravity * fGraviModifier;

			Vector3 Local = AssemblyCSharp::LocalPlayer::get_Entity()->get_bone_transform(RustStructs::bones::head)->get_position();

			Prediction(Local, Features().BulletTPAngle, m_target.m_velocity, component->projectileVelocity() , projectileComponent->gravityModifier(), projectileComponent->drag());
			auto posnormal = (Features().BulletTPAngle - Local).Normalized();
			Vector4 toQuat = Vector4::QuaternionLookRotation(posnormal, Vector3(0, 1, 0));

			

			if (inputState->IsDown(RustStructs::FIRE_SECONDARY) && inputState->WasJustPressed(RustStructs::FIRE_PRIMARY))
			{
				if (!_This->HasAttackCooldown())
				{
		
					AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->SetBodyRotation(toQuat);

					//Vector3 re_p = Features().LocalPlayer->eyes()->get_position();
					//if (Features().ManipulationAngle != Vector3(0, 0, 0))
					//{
					//	UnityEngine::DDraw().Sphere(Features().CachedManipPoint, 0.5f, Color::Cyan(), 3.f, false);
					//	//				UnityEngine::DDraw().Sphere(OriginalPos, 0.5f, Color::Cyan(), 3.f, false);

					//	//StartPosition += (Features().CachedManipPoint - re_p);

					//	Vector3 ManipPosition = (Features().CachedManipPoint - re_p);
					//	ManipPosition.Normalized();

					//	//base.transform.position + base.transform.up * (PlayerEyes.EyeOffset.y + this.viewOffset.y);
					//	Features().LocalPlayer->eyes()->viewOffset() = ManipPosition;

					//}
					_This->DoThrow();
					_This->StartAttackCooldown(_This->repeatDelay());

				
				}
			}
		}
	}

	//Features().LocalPlayer->eyes()->viewOffset() = OriginalPos;

	return Hooks::OnInputhk.get_original< decltype(&OnInput)>()(_This);
}