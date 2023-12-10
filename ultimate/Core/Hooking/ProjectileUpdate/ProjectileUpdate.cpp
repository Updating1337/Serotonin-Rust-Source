#include "../Hooks.hpp"
#include "../../SDK/AssemblyCSharp/ProjectileCode.hpp"
#include "../WriteToStream/Prediction.hpp"
#include "../../Features/Features/Features.hpp"


float GetEffectScale(AssemblyCSharp::Projectile* _This)
{
	if (!IsAddressValid(_This))
		return 0.f;

	if (_This->invisible())
	{
		return 0.f;
	}
	if (_This->traveledDistance() < 8.f)
	{
		return 0.f;
	}

	return Vector3().InverseLerp(12.f, 20.f, _This->currentVelocity().UnityMagnitude());
}

void Hooks::ProjectileUpdate(AssemblyCSharp::Projectile* _This)
{
	if (!InGame)
		return Hooks::ProjectileUpdatehk.get_original< decltype(&ProjectileUpdate)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::ProjectileUpdatehk.get_original< decltype(&ProjectileUpdate)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::ProjectileUpdatehk.get_original< decltype(&ProjectileUpdate)>()(_This);

	static float OriginalThickness = _This->thickness();


	float Thickness = m_settings::NormalThickBulletThickness;
	if (m_settings::NormalThickBullet) {
		_This->thickness() = Thickness;
	}
	else
		_This->thickness() = 0.1f;

	if (!m_settings::BulletTP)
		return Hooks::ProjectileUpdatehk.get_original< decltype(&ProjectileUpdate)>()(_This);

	float delta_time = 0.03125f;
	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return Hooks::ProjectileUpdatehk.get_original< decltype(&ProjectileUpdate)>()(_This);

	auto m_target = AssemblyCSharp::BasePlayer().GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(m_target.m_player))
		return Hooks::ProjectileUpdatehk.get_original< decltype(&ProjectileUpdate)>()(_This);

	BasePlayer* m_Owner = _This->owner();
	if (!IsAddressValid(m_Owner))
		return;

	if (m_Owner->userID() != Features().LocalPlayer->userID())
		return;

	if (_This->projectileID() == 0 || !m_Owner)
		return Hooks::ProjectileUpdatehk.get_original< decltype(&ProjectileUpdate)>()(_This);

	auto OriginalOriginalDistance = _This->initialDistance();

	if (m_settings::InstantBullet)
	{
		_This->initialDistance() = InitialDistanceDebug;
	}

	UnityEngine::Transform* transform = _This->get_transform();

	while (
		_This->integrity() > 0.001f &&
		_This->maxDistance() > _This->traveledDistance() &&
		_This->traveledTime() < 8.f &&
		_This->launchTime() > 0.f &&
		(UnityEngine::Time::get_time() - _This->launchTime()) >= (_This->traveledTime() + delta_time))
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
			Vector3 a = _This->currentVelocity() * delta_time;
			float magnitude = a.Length();
			float num2 = 1 / magnitude;
			Vector3 vec2 = a * num2;
			bool flag = false;

			Vector3 vec3 = _This->currentPosition() + vec2 * magnitude;

			UnityEngine::DDraw().Line(_This->currentPosition(), vec3, Color::Red(), 5.f, false, false);
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

	if (_This->integrity() <= 0.01f || _This->maxDistance() <= _This->traveledDistance() || _This->traveledTime() > 8.f)
		_This->Retire();
	else
	{
		_This->SetEffectScale(GetEffectScale(_This));
		_This->DoFlybySound();
	}

	_This->initialDistance() = OriginalOriginalDistance;

}