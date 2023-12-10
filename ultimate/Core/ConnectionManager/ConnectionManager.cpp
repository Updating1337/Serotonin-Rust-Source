#include "ConnectionManager.hpp"
#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

#include "../Features/Visuals/Visuals.hpp"
#include "../Features/Features/Features.hpp"

void ConnectionManager::ResetPlayerCache()
{
	Features().GeneratedPoints = false;
	Features().cachedPoints.clear();
	HasSetNightColor = false;
	HasSetAmbient = false;
	HasSetSharpCloud = false;
	HasSetDayColor = false;
	DoNoclip = false;
	DebugCamera = false;
	Visuals().Instance()->VisiblePlayerList = nullptr;

	Features().LocalPlayer = nullptr;
	Features().BaseProjectile = nullptr;

	auto camera = UnityEngine::Camera::get_main();
	if (IsAddressValid(camera))
	{
		auto target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
		//// Clear the target instance
		target.Clear();
	}

	translated_map.clear();
	translated_map2.clear();

	VisualsArray.clear();
	VisualsArrayTemp.clear();

	PrefabVectorList.clear();

	LogSystem::loggedExplosions.clear();

	PrefabListTemp.clear();

	Features().BulletTPAngle = Vector3();
	Features().ManipulationAngle = Vector3();
	Features().CachedManipPoint = Vector3();
	Features().CachedBulletTPPosition = Vector3();
	Features().BulletTPPointVisible = false;
	Features().PointVisible = false;
	Features().PositionVisible = false;

	m_settings::MaxVerticalFlyhack = 0;
	m_settings::VerticalFlyhack = 0;
	m_settings::MaxHorisontalFlyhack = 0;
	m_settings::HorisontalFlyhack = 0;

	//m_settings::DrawPlayerChams = false;
	m_settings::did_reload = false;
	m_settings::just_shot = false;
	m_settings::time_since_last_shot = 0.0f;
	m_settings::fixed_time_last_shot = 0.0f;

	m_settings::can_manipulate = false;
	m_settings::StartShooting = false;
	m_settings::Manipulation_Indicator = false;
	m_settings::Thickbullet_Indicator = false;
	m_settings::last_tick_time = 0.f;
	m_settings::max_spoofed_eye_distance = 0.f;

	/* Chams */
	{

		if (HerbertPrefab)
		{
			HerbertPrefab = nullptr;
		}

		if (AmongusPrefab)
		{
			AmongusPrefab = nullptr;
		}

		if (ExplosionPrefab)
		{
			ExplosionPrefab = nullptr;
		}

		if (GhostPrefab)
		{
			GhostPrefab = nullptr;
		}

		if (TestPrefab)
		{
			TestPrefab = nullptr;
		}
	
		if (GalaxyBundle)
		{
			GalaxyShader = nullptr;
			GalaxyMaterial = nullptr;
		}

		if (FireBundleA)
		{
			FireShaderA = nullptr;
			FireMaterialA = nullptr;
		}

		if (RPBGalaxyBundle)
		{
			RPBGalaxyShader = nullptr;
			RPBGalaxyMaterial = nullptr;
		}

		if (FireBundleB)
		{
			FireShaderB = nullptr;
			FireMaterialB = nullptr;
		}

		if (GeometricBundle)
		{
			GeometricShader = nullptr;
			GeometricMaterial = nullptr;
		}

		if (LightningBundle)
		{
			LightningShader = nullptr;
			LightningMaterial = nullptr;
		}

		if (WireFrameBundle)
		{
			WireFrameShader = nullptr;
			WireFrameMaterial = nullptr;
		}

		if (ColorBundle)
		{
			ColorShader = nullptr;
			ColorMaterial = nullptr;
		}

		if (TestBundle)
		{
			TestShader = nullptr;
			TestMaterial = nullptr;
		}

		if (GlitterBundle)
		{
			GlitterShader = nullptr;
			GlitterMaterial = nullptr;
		}

		if (DamascusBundle)
		{
			DamascusShader = nullptr;
			DamascusMaterial = nullptr;
		}
	}
}

bool ConnectionManager::IsConnected()
{
	const auto Network = Network::Net::get_cl();

	if (!IsAddressValid(Network))
		return false;

	if (!Network->IsConnected())
	{
		auto LocalPlayer = AssemblyCSharp::LocalPlayer().get_Entity();
		if (!IsAddressValid(LocalPlayer))
			return false;

		if (LocalPlayer)
			LocalPlayer->net() = nullptr;

		this->ResetPlayerCache();

		return false;
	}

	const auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();

	if (!IsAddressValid(LocalPlayer) || !IsAddressValid(LocalPlayer->net()))
	{
		this->ResetPlayerCache();

		return false;
	}


	/*if (!LocalPlayer->IsAlive())
	{
		if (IsAddressValid(Features().Instance()->LocalPlayer))
		{
			if (IsAddressValid(Features().Instance()->LocalPlayer->GetBaseMovement()))
			{
				Features().Instance()->LocalPlayer->GetBaseMovement()->adminCheat() = false;
			}
		}
	}*/

	return LocalPlayer->IsAlive() && !LocalPlayer->IsSleeping();
}