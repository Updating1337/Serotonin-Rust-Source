#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"
#include "../WriteToStream/Prediction.hpp"
#include "../../SDK/AssemblyCSharp/ProjectileCode.hpp"
#include "../../Includes/colorsettings.hpp"

void ProjectileLaunch(AssemblyCSharp::Projectile* _This)
{
	if (!InGame)
		return;

	if (!IsAddressValid(_This))
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	BasePlayer* m_Owner = _This->owner();
	if (!IsAddressValid(m_Owner))
		return;

	if (m_Owner->userID() != Features().LocalPlayer->userID())
		return;

	static float OriginalThickness = _This->thickness();


	float Thickness = m_settings::NormalThickBulletThickness;
	if (m_settings::NormalThickBullet) {
		_This->thickness() = Thickness;
	}
	else
		_This->thickness() = 0.1f;

	float delta_time = 0.03125f;

	_This->integrity() = 1.f;

	auto OriginalDistance = _This->initialDistance();
	if (m_settings::InstantBullet)
	{
		_This->initialDistance() = InitialDistanceDebug;
	}

	UnityEngine::Transform* transform = _This->get_transform();

	while (_This->IsAlive() && (_This->traveledDistance() < _This->initialDistance() || _This->traveledTime() < 0.1f))
	{
		Vector3 previous_position = _This->previousPosition();
		if (_This->traveledTime() != 0.f)
			_This->previousPosition() = _This->currentPosition();

		_This->currentPosition() = transform->get_position();
		if (_This->traveledTime() == 0.f)
			_This->sentPosition() = _This->previousPosition() = _This->currentPosition();


		delta_time *= UnityEngine::Time::get_timeScale();

		if (m_settings::BulletTracers)
		{
			auto Tracers_Color = Color(ColorSettings::BulletTracers_Color.r, ColorSettings::BulletTracers_Color.g, ColorSettings::BulletTracers_Color.b, ColorSettings::BulletTracers_Color.a);

			Vector3 a = _This->currentVelocity() * delta_time;
			float magnitude = a.Length();
			float num2 = 1 / magnitude;
			Vector3 vec2 = a * num2;
			bool flag = false;

			Vector3 vec3 = _This->currentPosition() + vec2 * magnitude;

			UnityEngine::DDraw().Line(_This->currentPosition(), vec3, Tracers_Color, 5.f, false, false);
		}

		auto project_ = (Projectile_c*)_This;
		bool res = project_->DoMovement(delta_time, project_);
		if (!res)
		{
			project_->DoVelocityUpdate(delta_time);
		}
		
		transform->set_position(_This->currentPosition());
		transform->set_rotation(Vector4::QuaternionLookRotation(_This->currentVelocity(), { 0.f, 1.f, 0.f }));
	}

	if (_This->integrity() < 0.01f || _This->maxDistance() <= _This->traveledDistance() || _This->traveledTime() > 8.f)
		_This->Retire();


	_This->initialDistance() = OriginalDistance;
}

void LaunchRecreation()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;


	for (size_t i = 0; i < LaunchedProjectileSize; i++)
	{
		if (auto projectile = LaunchedProjectilesArray[i])
		{
			ProjectileLaunch(projectile);
		}
	}
}


void Hooks::DoAttack(AssemblyCSharp::BaseProjectile* _This)
{
	if (!InGame)
		return Hooks::DoAttackhk.get_original< decltype(&DoAttack)>()(_This);

	if(!IsAddressValid(Features().LocalPlayer))
		return Hooks::DoAttackhk.get_original< decltype(&DoAttack)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::DoAttackhk.get_original< decltype(&DoAttack)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::DoAttackhk.get_original< decltype(&DoAttack)>()(_This);
	}

	if (!m_settings::BulletTP)
		return Hooks::DoAttackhk.get_original< decltype(&DoAttack)>()(_This);

	CalledLaunchFromHook = true;

	Hooks::DoAttackhk.get_original< decltype(&DoAttack)>()(_This);

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return Hooks::DoAttackhk.get_original< decltype(&DoAttack)>()(_This);

	auto m_target = AssemblyCSharp::BasePlayer().GetAimbotTarget(camera->get_positionz());
	if (m_settings::BulletTP && IsAddressValid(m_target.m_player))
	{
		LaunchRecreation();
	}
	CalledLaunchFromHook = false;
}