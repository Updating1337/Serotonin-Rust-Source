#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::FlintStrikeWeaponDoAttack(AssemblyCSharp::FlintStrikeWeapon* _This)
{
	if (!InGame)
		return Hooks::FlintStrikeWeaponDoAttackhk.get_original< decltype(&FlintStrikeWeaponDoAttack)>()(_This);

	if (!_This)
		return Hooks::FlintStrikeWeaponDoAttackhk.get_original< decltype(&FlintStrikeWeaponDoAttack)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::FlintStrikeWeaponDoAttackhk.get_original< decltype(&FlintStrikeWeaponDoAttack)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::FlintStrikeWeaponDoAttackhk.get_original< decltype(&FlintStrikeWeaponDoAttack)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::FlintStrikeWeaponDoAttackhk.get_original< decltype(&FlintStrikeWeaponDoAttack)>()(_This);
	}

	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();

	if (m_settings::InstantEoka)
	{
		if (IsAddressValid(LocalPlayer)) {
			if (_This->_didSparkThisFrame() != true)
				_This->_didSparkThisFrame() = true;	
		}
	}

	static bool StartEokaShot = false;
	if (m_settings::Autoshoot && UnityEngine::Input::GetKey(m_settings::AutoshootKey)) {
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500.f);
			if (IsAddressValid(AimbotTarget.m_player)) {
				if (AssemblyCSharp::IsVisible(LocalPlayer->get_bone_transform(47)->get_position(), AimbotTarget.m_player->get_bone_transform(AimbotTarget.m_bone)->get_position())) {
					Features().PointVisible = true;
					StartEokaShot = true;
				}
				else if (m_settings::BehindWall) {
					if (m_settings::Manipulation && m_settings::BulletTP) {
						if (m_settings::Thickbullet_AutoShoot && m_settings::StartShooting && m_settings::Manipulation_Indicator)
							StartEokaShot = true;
						else
							StartEokaShot = false;
					}
				}
				else if (m_settings::Thickbullet_AutoShoot) {
					if (m_settings::BulletTP)
						StartEokaShot = true;
					else
						StartEokaShot = false;
				}
				else if (m_settings::StartShooting) {
					if (m_settings::Manipulation)
						StartEokaShot = true;
					else
						StartEokaShot = false;
				}
				else
					StartEokaShot = false;
			}

		}

	}
	else
		StartEokaShot = false;

	if (m_settings::Autoshoot && UnityEngine::Input::GetKey(m_settings::AutoshootKey))
	{
		if (IsAddressValid(LocalPlayer)) {
			auto eyes = LocalPlayer->eyes();
			if (IsAddressValid(eyes)) {

				if (StartEokaShot && Features().PointVisible)
				{
					if (_This->_isStriking() != false)
						_This->_isStriking() = false;

					if (_This->primaryMagazine()->contents() <= 0)
					{
					//	_This->TryReload();
						return;
					}

					AssemblyCSharp::ItemDefinition* ammoType = _This->primaryMagazine()->ammoType();
					_This->primaryMagazine()->contents()--;
					_This->StartAttackCooldown(_This->repeatDelay());

					_This->GetOwnerPlayer()->SendSignalBroadcast(RustStructs::Signal::Attack, XS(""));
					if (_This->viewModel())
					{
						_This->viewModel()->Play(XS("attack"), 0);
					}

					AssemblyCSharp::ItemModProjectile* component = ammoType->GetComponent<AssemblyCSharp::ItemModProjectile>(FPSystem::Type::ItemModProjectile());

					_This->LaunchProjectileClientside(ammoType, component->numProjectiles(), 0.f);

					_This->UpdateAmmoDisplay();
					_This->DidAttackClientside();
				}
			}
		}
	}
	else
	{
		return Hooks::FlintStrikeWeaponDoAttackhk.get_original< decltype(&FlintStrikeWeaponDoAttack)>()(_This);
	}
}