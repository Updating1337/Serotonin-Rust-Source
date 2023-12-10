#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

#include "../../Includes/colorsettings.hpp"

void Hooks::LateUpdate(AssemblyCSharp::TOD_Sky* _This)
{
	if (!InGame)
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (!IsAddressValid(_This))
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);
	}

	if (IsAddressValid(_This)) {
		if (IsAddressValid(_This->Sun()))
		{
			auto Sun = _This->Sun();
			static bool ResetSunBrightness = false;
			static float Orig_SunBrightness;
			static float Orig_SunContast;
			static float Orig_SunSize;
			if (m_settings::NoSun)
			{
				if (Sun->MeshBrightness() != 0.f) {
					Orig_SunBrightness = Sun->MeshBrightness();
					Sun->MeshBrightness() = 0.f;
				}

				if (Sun->MeshBrightness() != 0.f) {
					Orig_SunContast = Sun->MeshContrast();
					Sun->MeshContrast() = 0.f;
				}

				if (Sun->MeshSize() != 0.f) {
					Orig_SunSize = Sun->MeshSize();
					Sun->MeshSize() = 0.f;
				}
			}
			else {
				if (!m_settings::NoSun && ResetSunBrightness)
				{
					if (Sun->MeshBrightness() != Orig_SunBrightness) {
						Sun->MeshBrightness() = Orig_SunBrightness;
					}

					if (Sun->MeshContrast() != Orig_SunContast) {
						Sun->MeshContrast() = Orig_SunContast;
					}

					if (Sun->MeshSize() != Orig_SunSize) {
						Sun->MeshSize() = Orig_SunSize;
					}
				}
			}
		}

		if (IsAddressValid(_This->Night()))
		{
			auto Night = _This->Night();

			if (IsAddressValid(Night)) {
				{
					static float Orig_LightIntensity;
					static float Orig_AmbientMultiplier;
					static float Orig_ReflectionMultiplier;
					static bool ResetBrightnightToDefault = false;
					if (m_settings::Brightnight) {

						if (Night->LightIntensity() != 20.f) {
							Orig_LightIntensity = Night->LightIntensity();
							Night->LightIntensity() = 20.f;
						}

						if (Night->AmbientMultiplier() != 4.f) {
							Orig_AmbientMultiplier = Night->AmbientMultiplier();
							Night->AmbientMultiplier() = 4.f;
						}

						if (!Night->ReflectionMultiplier() != 1.f) {
							Orig_ReflectionMultiplier = Night->ReflectionMultiplier();
							Night->ReflectionMultiplier() = 1.f;
						}
						ResetBrightnightToDefault = true;
					}
					else {
						if (!m_settings::Brightnight && ResetBrightnightToDefault)
						{
							if (Night->LightIntensity() != Orig_LightIntensity) {
								Night->LightIntensity() = Orig_LightIntensity;
							}

							if (Night->AmbientMultiplier() != Orig_AmbientMultiplier) {
								Night->AmbientMultiplier() = Orig_AmbientMultiplier;
							}

							if (!Night->ReflectionMultiplier() != Orig_ReflectionMultiplier) {
								Night->ReflectionMultiplier() = Orig_ReflectionMultiplier;
							}
							ResetBrightnightToDefault = false;
						}
					}
				}

				{
					static Vector4 Orig_AmbientColor;
					static bool ResetBrightAmbientToDefault;

					if (m_settings::BrightAmbient) {
						auto Ambient = Night->AmbientColor();
						if (IsAddressValid(Ambient))
						{
							if (!HasSetAmbient) {
								auto Ambient_Color = Color{ ColorSettings::Ambient_Color.r, ColorSettings::Ambient_Color.g, ColorSettings::Ambient_Color.b, ColorSettings::Ambient_Color.a };

								uintptr_t AmbientColor = *reinterpret_cast<uintptr_t*>(Ambient + 0x10);
								Orig_AmbientColor = *reinterpret_cast<Vector4*>(AmbientColor);
								*reinterpret_cast<Color*>(AmbientColor) = { Ambient_Color };
								HasSetAmbient = true;
								ResetBrightAmbientToDefault = true;
							}
						}

						//*(Vector4*)(AmbientColor) = { 0.8f, 0.8f, 0.8f, 0.8f };
					}
					else if (!m_settings::BrightAmbient && ResetBrightAmbientToDefault)
					{
						auto Ambient = Night->AmbientColor();
						if (IsAddressValid(Ambient))
						{
							uintptr_t AmbientColor = *reinterpret_cast<uintptr_t*>(Ambient + 0x10);
							*reinterpret_cast<Vector4*>(AmbientColor) = Orig_AmbientColor;
							ResetBrightAmbientToDefault = false;
						}
					}
					else
						HasSetAmbient = false;
				}

				{
					static Color Orig_SkyColorNight;
					static bool ResetSkyColorNightToDefault;
					if (m_settings::SkyColorNight) {
						auto Sky = Night->SkyColor();
						if (IsAddressValid(Sky))
						{
							if (!HasSetNightColor) {
								auto Skybox_Color = Color{ ColorSettings::SkyBox_Color.r, ColorSettings::SkyBox_Color.g, ColorSettings::SkyBox_Color.b, ColorSettings::SkyBox_Color.a };

								uintptr_t SkyColor = *reinterpret_cast<uintptr_t*>(Sky + 0x10);
								Orig_SkyColorNight = *reinterpret_cast<Color*>(SkyColor);
								*reinterpret_cast<Color*>(SkyColor) = Color(Skybox_Color);
								HasSetNightColor = true;
								ResetSkyColorNightToDefault = true;
							}
						}
						//*(Color*)(SkyColor) = Color(66.f, 245.f, 206.f, 255.f).GetUnityColor();
					}
					else if (!m_settings::SkyColorNight && ResetSkyColorNightToDefault)
					{
						auto Sky = Night->SkyColor();
						if (IsAddressValid(Sky))
						{
							uintptr_t SkyColor = *reinterpret_cast<uintptr_t*>(Sky + 0x10);
							*reinterpret_cast<Color*>(SkyColor) = Orig_SkyColorNight;
							ResetSkyColorNightToDefault = false;
						}
					}
					else
						HasSetNightColor = false;
				}

				{
					static Vector4 Orig_SharpClouds;
					static bool ResetSharpCloudsToDefault = false;
					if (m_settings::SharpClouds) {
						auto Clouds = Night->CloudColor();
						if (IsAddressValid(Clouds))
						{
							if (!HasSetSharpCloud) {
								uintptr_t CloudColor = *reinterpret_cast<uintptr_t*>(Clouds + 0x10);
								Orig_SharpClouds = *reinterpret_cast<Vector4*>(CloudColor);
								*reinterpret_cast<Color*>(CloudColor) = Color(255.f, 255.f, 255.f, 255.f).GetUnityColor();
								HasSetSharpCloud = true;
								ResetSharpCloudsToDefault = true;
							}
						}
						//*(Color*)(CloudColor) = Color(255.f, 255.f, 255.f, 255.f).GetUnityColor();
					}
					else if (!m_settings::SharpClouds && ResetSharpCloudsToDefault)
					{
						auto Clouds = Night->CloudColor();
						if (IsAddressValid(Clouds))
						{
							uintptr_t CloudColor = *reinterpret_cast<uintptr_t*>(Clouds + 0x10);
							*reinterpret_cast<Vector4*>(CloudColor) = Orig_SharpClouds;
							ResetSharpCloudsToDefault = false;
						}
					}
					else
						HasSetSharpCloud = false;
				}
			}
		}

		if (IsAddressValid(_This->Day()))
		{
			auto Day = _This->Day();

			if (IsAddressValid(Day))
			{
				{
					static Vector4 Orig_SkyColorDay;
					static bool ResetSkyColorDayToDefault;
					if (m_settings::SkyColorDay) {
						auto Sky = Day->SkyColor();
						if (IsAddressValid(Sky))
						{
							if (!HasSetDayColor) {

								auto Skybox_Color = Color{ ColorSettings::SkyBox_Color.r, ColorSettings::SkyBox_Color.g, ColorSettings::SkyBox_Color.b, ColorSettings::SkyBox_Color.a };
								uintptr_t SkyColor = *reinterpret_cast<uintptr_t*>(Sky + 0x10);
								Orig_SkyColorDay = *reinterpret_cast<Vector4*>(SkyColor);
								*reinterpret_cast<Color*>(SkyColor) = Color(Skybox_Color);
								HasSetDayColor = true;
								ResetSkyColorDayToDefault = true;
							}
						}
						//*(Color*)(SkyColor) = Color(66.f, 245.f, 206.f, 255.f).GetUnityColor();
					}
					else if (!m_settings::SkyColorDay && ResetSkyColorDayToDefault)
					{
						auto Sky = Day->SkyColor();
						if (IsAddressValid(Sky))
						{
							uintptr_t SkyColor = *reinterpret_cast<uintptr_t*>(Sky + 0x10);
							*reinterpret_cast<Vector4*>(SkyColor) = Orig_SkyColorDay;
							ResetSkyColorDayToDefault = false;
						}
					}
					else
						HasSetDayColor = false;
				}

				{
					static float Orig_AmbientMultiplierDay;
					static float Orig_ReflectionMultiplierDay;
					static bool ResetBrightCaveToDefault;
					if (m_settings::BrightCave) {
						if (Day->AmbientMultiplier() != 1.f) {
							Orig_AmbientMultiplierDay = Day->AmbientMultiplier();
							Day->AmbientMultiplier() = 1.f;
						}

						if (Day->ReflectionMultiplier() != 1.f) {
							Orig_ReflectionMultiplierDay = Day->ReflectionMultiplier();
							Day->ReflectionMultiplier() = 1.f;
						}

						ResetBrightCaveToDefault = true;
					}
					else if (!m_settings::BrightCave && ResetBrightCaveToDefault)
					{
						if (Day->AmbientMultiplier() != Orig_AmbientMultiplierDay) {
							Day->AmbientMultiplier() = Orig_AmbientMultiplierDay;
						}

						if (Day->ReflectionMultiplier() != Orig_ReflectionMultiplierDay) {
							Day->ReflectionMultiplier() = Orig_ReflectionMultiplierDay;
						}

						ResetBrightCaveToDefault = false;
					}
				}
			}
		
		}

		if (IsAddressValid(_This->Stars()))
		{
			auto Stars = _This->Stars();
			if (IsAddressValid(Stars))
			{
				static float Orig_StarsAmount;
				static bool ResetStarsToDefault;
				if (m_settings::Stars) {
					if (Stars->Brightness() != 150.f) {
						Orig_StarsAmount = Stars->Brightness();
						Stars->Brightness() = 150.f;
					}
					ResetStarsToDefault = true;
				}
				else if (!m_settings::Stars && ResetStarsToDefault)
				{
					if (Stars->Brightness() != Orig_StarsAmount) {
						Stars->Brightness() = Orig_StarsAmount;
					}
					ResetStarsToDefault = false;
				}
			}
		}
	}

	return Hooks::LateUpdatehk.get_original< decltype(&LateUpdate)>()(_This);
}