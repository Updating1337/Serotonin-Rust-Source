#include "../Hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"

#include "../../Net/net.h"
#include "../../Net/data.h"
#include "../../Net/fnv1a.h"
#include "../../Features/Visuals/Visuals.hpp"
#include "../../MenuFramework/Menu/Menu.hpp"
#include "../../Features/Notifications/Notifications.hpp"
#include "../../MenuFramework/gui/gui.hpp"

#include "../../Includes/colorsettings.hpp"

inline UnityEngine::GUISkin* gui_skin = nullptr;

void SetupStyles()
{
	if (!m_settings::FontChanger) {
		if (UnityEngine::gui_style && gui_skin && UnityEngine::menu_gui_style && UnityEngine::world_gui_style && UnityEngine::screen_gui_style)
			return;
	}

	static bool FontLoaded = false;

	if (gui_skin == nullptr || UnityEngine::gui_style == nullptr || UnityEngine::menu_gui_style == nullptr || UnityEngine::world_gui_style == nullptr || UnityEngine::screen_gui_style == nullptr)
	{

		gui_skin = UnityEngine::GUI::GetSkin();

		UnityEngine::gui_style = gui_skin->m_label();
		UnityEngine::menu_gui_style = gui_skin->m_label();
		UnityEngine::world_gui_style = gui_skin->m_label();
		UnityEngine::screen_gui_style = gui_skin->m_label();

		if (!FontLoaded)
		{
			uintptr_t* g_font;
			if (m_settings::fonttype == 0)
				g_font = font_bundle->LoadAsset<uintptr_t>(XS("ubuntu-medium.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));
			else if (m_settings::fonttype == 1)
				g_font = font_bundle->LoadAsset<uintptr_t>(XS("smallest_pixel-7.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));
			else if (m_settings::fonttype == 2)
				g_font = font_bundle->LoadAsset<uintptr_t>(XS("verdana.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));
			else if (m_settings::fonttype == 3)
				g_font = font_bundle2->LoadAsset<uintptr_t>(XS("division.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));

			gui_skin->m_Font() = ToAddress(g_font);

			FontLoaded = true;
		}

		UnityEngine::GUIStyle::SetAlignment(UnityEngine::gui_style, 0);
		UnityEngine::GUIStyle::SetAlignment(UnityEngine::menu_gui_style, 0);
		UnityEngine::GUIStyle::SetAlignment(UnityEngine::world_gui_style, 0);
		UnityEngine::GUIStyle::SetAlignment(UnityEngine::screen_gui_style, 0);
		UnityEngine::GUI::SetColor(Color::White());
	}

	uintptr_t* g_font;
	static bool SetNewFont = false;
	static int FontTypee = 0;

	if (FontLoaded) {
		if (m_settings::fonttype == 0 && FontTypee != m_settings::fonttype && !SetNewFont)
		{
			FontTypee = m_settings::fonttype;
			SetNewFont = true;
		}
		else if (m_settings::fonttype == 1 && FontTypee != m_settings::fonttype && !SetNewFont)
		{
			FontTypee = m_settings::fonttype;
			SetNewFont = true;
		}
		else if (m_settings::fonttype == 2 && FontTypee != m_settings::fonttype && !SetNewFont)
		{
			FontTypee = m_settings::fonttype;
			SetNewFont = true;
		}
		else if (m_settings::fonttype == 3 && FontTypee != m_settings::fonttype && !SetNewFont)
		{
			FontTypee = m_settings::fonttype;
			SetNewFont = true;
		}

		if (SetNewFont) {
			if (m_settings::fonttype == 0)
				g_font = font_bundle->LoadAsset<uintptr_t>(XS("ubuntu-medium.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));
			else if (m_settings::fonttype == 1)
				g_font = font_bundle->LoadAsset<uintptr_t>(XS("smallest_pixel-7.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));
			else if (m_settings::fonttype == 2)
				g_font = font_bundle->LoadAsset<uintptr_t>(XS("verdana.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));
			else if (m_settings::fonttype == 3)
				g_font = font_bundle2->LoadAsset<uintptr_t>(XS("division.ttf"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Font"))));

			gui_skin->m_Font() = ToAddress(g_font);

			SetNewFont = false;
		}
	}
}


void ConnectorClient()
{
	static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
	float current_time = UnityEngine::Time::get_realtimeSinceStartup();

	static float send_time2 = UnityEngine::Time::get_realtimeSinceStartup();
	float current_time2 = UnityEngine::Time::get_realtimeSinceStartup();

	static bool LoadOnce = false;

	connector::cheat_message msg;
	msg.msg = connector::messages::JOIN_SHARED_ESP;
	msg.value = "TrollServer1"; //Name of channel
	auto data = connector::data(msg);

	if (current_time - send_time > 0.02f)
	{
		net->run();

		if (net->ready_.load())
		{

			if (!LoadOnce)
			{
				net->send_data(data);

				LOG(XS("[DEBUG] Connected to TrollServer1"));
				LoadOnce = true;
			}

			if (LoadOnce)
			{
				static bool ReceivedFile1 = false;
				static bool ReceivedFile2 = false;
				static bool ReceivedFile3 = false;
				static bool ReceivedFile4 = false;
				static bool ReceivedFile5 = false;
				static bool ReceivedFile6 = false;
				static bool ReceivedFile7 = false;
				static bool ReceivedFile8 = false;
				static bool ReceivedFile9 = false;
				static bool ReceivedFile10 = false;
				static bool ReceivedFile11 = false;
				static bool ReceivedFile12 = false;
				static bool ReceivedFile13 = false;
				static bool ReceivedFile14 = false;
				static bool ReceivedFile15 = false;

				//request your uploaded file anytime else
				if (!ReceivedFile1)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FontBundlezNew"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
				}

				static bool DataSent = false;
				if (ReceivedFile2 && !DataSent)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "IconBundlez"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent = true;
				}

				static bool DataSent2 = false;
				if (ReceivedFile3 && !DataSent2)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "IconsBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent2 = true;
				}

				static bool DataSent3 = false;
				if (ReceivedFile4 && !DataSent3)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FireBundleA"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent3 = true;
				}

				static bool DataSent4 = false;
				if (ReceivedFile5 && !DataSent4)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "FireBundleB"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent4 = true;
				}

				static bool DataSent5 = false;
				if (ReceivedFile6 && !DataSent5)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "ColorBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent5 = true;
				}

				static bool DataSent6 = false;
				if (ReceivedFile7 && !DataSent6)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "DivisionFontz"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent6 = true;
				}

				static bool DataSent7 = false;
				if (ReceivedFile8 && !DataSent7)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "LightningBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent7 = true;
				}

				static bool DataSent8 = false;
				if (ReceivedFile9 && !DataSent8)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "GeometricDisolveBundlez"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent8 = true;
				}

				static bool DataSent9 = false;
				if (ReceivedFile10 && !DataSent9)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "GlitterBundlez"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent9 = true;
				}

				static bool DataSent10 = false;
				if (ReceivedFile11 && !DataSent10)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "WireFrameBundlez"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent10 = true;
				}

				static bool DataSent11 = false;
				if (ReceivedFile12 && !DataSent11)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "GhostHitEffectBundlez"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent11 = true;
				}

				static bool DataSent12 = false;
				if (ReceivedFile13 && !DataSent12)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "AmongusBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent12 = true;
				}

				static bool DataSent13 = false;
				if (ReceivedFile14 && !DataSent13)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "HerbertBundle"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent13 = true;
				}

				static bool DataSent14 = false;
				if (ReceivedFile15 && !DataSent14)
				{
					connector::cheat_message msg;
					msg.msg = connector::messages::GET_FILE;
					msg.value = "DamascusBundlez"; //Value has to be identical to the uploaded name
					auto data = connector::data(msg);
					net->send_data(data);
					DataSent14 = true;
				}

				net->shared_files_mutex_.lock();
				if (net->shared_files_.size() > 0)
				{
					for (auto& iter : net->shared_files_) {

						if (!ReceivedFile1) {
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!font_bundle)
								font_bundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile2 = true;
							ReceivedFile1 = true;
						}

						if (ReceivedFile2 && DataSent)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!IconBundle)
								IconBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile3 = true;
							ReceivedFile2 = false;
						}

						if (ReceivedFile3 && DataSent2)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!MenuIconBundles)
								MenuIconBundles = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile4 = true;
							ReceivedFile3 = false;
						}

						if (ReceivedFile4 && DataSent3)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!FireBundleA)
								FireBundleA = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile5 = true;
							ReceivedFile4 = false;
						}

						if (ReceivedFile5 && DataSent4)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!FireBundleB)
								FireBundleB = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile6 = true;
							ReceivedFile5 = false;
						}

						if (ReceivedFile6 && DataSent5)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!ColorBundle)
								ColorBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile7 = true;
							ReceivedFile6 = false;
						}

						if (ReceivedFile7 && DataSent6)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!font_bundle2)
								font_bundle2 = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile8 = true;
							ReceivedFile7 = false;
						}

						if (ReceivedFile8 && DataSent7)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!LightningBundle)
								LightningBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile9 = true;
							ReceivedFile8 = false;
						}

						if (ReceivedFile9 && DataSent8)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!GeometricBundle)
								GeometricBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile10 = true;
							ReceivedFile9 = false;
						}

						if (ReceivedFile10 && DataSent9)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!GlitterBundle)
								GlitterBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile11 = true;
							ReceivedFile10 = false;
						}

						if (ReceivedFile11 && DataSent10)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!WireFrameBundle)
								WireFrameBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
							net->shared_files_.clear();
							ReceivedFile12 = true;
							ReceivedFile11 = false;
						}

						if (ReceivedFile12 && DataSent11)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!GhostAsset) {
								GhostAsset = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);

								if (GhostAsset)
								{
									if (!GhostPrefab)
									{
										GhostPrefab = GhostAsset->LoadAsset<UnityEngine::GameObject>(XS("cfxr2 souls escape.prefab"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
									}
								}
							}

							if (GhostAsset)
							{
								if (!GhostPrefab)
								{
									GhostPrefab = GhostAsset->LoadAsset<UnityEngine::GameObject>(XS("cfxr2 souls escape.prefab"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
								}
							}

							net->shared_files_.clear();
							ReceivedFile13 = true;
							ReceivedFile12 = false;
						}

						if (ReceivedFile13 && DataSent12)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!AmongUsAsset) {
								AmongUsAsset = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);

								if (AmongUsAsset)
								{
									if (!AmongusPrefab)
									{
										AmongusPrefab = AmongUsAsset->LoadAsset<UnityEngine::GameObject>(XS("amongus.fbx"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
									}
								}
							}
							net->shared_files_.clear();
							ReceivedFile14 = true;
							ReceivedFile13 = false;
						}

						if (ReceivedFile14 && DataSent13)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!HerbetAsset) {
								HerbetAsset = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);

								if (HerbetAsset)
								{
									if (!HerbertPrefab)
									{
										HerbertPrefab = HerbetAsset->LoadAsset<UnityEngine::GameObject>(XS("herbert the pervert v2.fbx"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GameObject"))));
									}
								}
							}
							net->shared_files_.clear();
							ReceivedFile15 = true;
							ReceivedFile14 = false;
						}

						if (ReceivedFile15 && DataSent14)
						{
							LOG(XS("[DEBUG] Recieved file %s with size %zu\n"), iter.name.c_str(), iter.data.size());

							// Load bundle from memory
							auto bundleArray = (FPSystem::c_system_array<FPSystem::Byte*>*)FPSystem::il2cpp_array_new(FPSystem::Byte::StaticClass(), iter.data.size());
							std::memcpy(bundleArray->items, iter.data.data(), iter.data.size());
							if (!DamascusBundle) {
								DamascusBundle = UnityEngine::AssetBundle::LoadFromMemory_Internal(bundleArray, 0, 0);
								HasLoadedAllBundles = true;
							}

							net->shared_files_.clear();
							ReceivedFile15 = false;
						}
					}
				}
				net->shared_files_mutex_.unlock();

				//if (current_time2 - send_time2 > 0.8f)
				//{
				//	auto camera = UnityEngine::Camera::get_main();
				//	if (IsAddressValid(camera)) {
				//		auto Target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
				//		Vector3 TargetPos = Target.m_position;
				//		connector::writer write;
				//		write.write(TargetPos.x);
				//		write.write(TargetPos.y);
				//		write.write(TargetPos.z);

				//		//send data to server
				//		connector::shared_esp_data shared_data;
				//		shared_data.channel = HASHH("ServerABCD");//hash of the channel where we want to send data
				//		shared_data.data.resize(write.size() + 1, 0);
				//		memcpy(shared_data.data.data(), write.data(), write.size());

				//		data = connector::data(shared_data);
				//		net->send_data(data);

				//	}
				//	send_time2 = current_time2;
				//}
			}
		}
		else
			SteamConnectorError = true;

		send_time = current_time;
	}
}

void TextDrawBegin()
{
	UnityEngine::GL::PushMatrix();
	UnityEngine::GL::LoadPixelMatrix();
}

void TextDrawEnd()
{
	UnityEngine::GL::PopMatrix();
	UnityEngine::GL::RenderText();
	UnityEngine::GL::RenderScreenText();
	UnityEngine::GL::RenderWorldText();
	UnityEngine::GL::RenderMenuText();
	UnityEngine::GL::RenderIcons();
}

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
bool custom_isalnum(char c) {
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}
bool is_base64(char c) {
	return (custom_isalnum(c) || (c == '+') || (c == '/'));
}


std::string base64_decode(const std::string& encoded_string) {
	int in_len = static_cast<int>(encoded_string.size());
	int i = 0, j = 0, in = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string decoded_string;

	while (in_len-- && (encoded_string[in] != '=') && is_base64(encoded_string[in])) {
		char_array_4[i++] = encoded_string[in];
		in++;
		if (i == 4) {
			for (i = 0; i < 4; i++) {
				char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
			}

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0x0F) << 4) + ((char_array_4[2] & 0x3C) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x03) << 6) + char_array_4[3];

			for (i = 0; i < 3; i++) {
				decoded_string += char_array_3[i];
			}
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++) {
			char_array_4[j] = 0;
		}

		for (j = 0; j < 4; j++) {
			char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
		}

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0x0F) << 4) + ((char_array_4[2] & 0x3C) >> 2);

		for (j = 0; j < i - 1; j++) {
			decoded_string += char_array_3[j];
		}
	}

	return decoded_string;
}
void SetupBundles()
{

}


#include "../../Features/Features/Features.hpp"
#include "../../Configs/Configs.hpp"

float RecordedPointsX[100] = {};
float RecordedPointsY[100] = {};
float RecordedPointsZ[100] = {};

float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}

void drawRaidESP()
{
	LogSystem::RenderExplosions();
}

void drawMisc()
{
	if (!InGame)
		return;
	
	if (!IsAddressValid(Features().LocalPlayer))
		return;

	int yPos = 15;

	int yoffset = 48;

	float center_x = (float)(UnityEngine::screen_size.x) / 2, center_y = (float)(UnityEngine::screen_size.y) / 2;

	if (m_settings::Radar)
	{
		auto sizex = m_settings::RadarSize;
		auto sizey = m_settings::RadarSize;
		auto middle = m_settings::RadarSize / 2;
		auto x = UnityEngine::screen_size.x;
		auto y = UnityEngine::screen_size.y;

		auto xpos = x - 20 - sizex;
		auto ypos = 20;

		m_settings::RadarPosX = xpos; 
		m_settings::RadarPosY = ypos;

		/* MainWindow */
		UnityEngine::GL().RectangleFilled(Vector2(xpos, ypos), Vector2(xpos + sizex, ypos + sizey), Color(34.f, 34.f, 34.f, 120.f).GetUnityColor());

		/* ViewBox */
		UnityEngine::GL().Line(Vector2(xpos + middle, ypos + middle), Vector2(xpos + sizex, ypos), Color::Black());
		UnityEngine::GL().Line(Vector2(xpos + middle, ypos + middle), Vector2(xpos + 1, ypos + 1), Color::Black());
		UnityEngine::GL().Line(Vector2(xpos + middle, ypos + middle), Vector2(xpos + middle, ypos + middle + sizey / 2), Color::Black());

		/* Outline */
		UnityEngine::GL().Rectangle(Vector2(xpos, ypos), Vector2(xpos + sizex, ypos + sizey), Color::Black());

		/* LocalPos */
		UnityEngine::GL().CircleFilled(Vector2(xpos + middle, ypos + middle - 1), 3, Color::White(), 25);
	}

	if (m_settings::Crosshair)
	{
		auto Crosshair_Color = Color(ColorSettings::Crosshair_Color.r, ColorSettings::Crosshair_Color.g, ColorSettings::Crosshair_Color.b, ColorSettings::Crosshair_Color.a);

		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x + 8, screen_center.y), Crosshair_Color);
		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x - 7, screen_center.y), Crosshair_Color);
		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x, screen_center.y + 8), Crosshair_Color);
		UnityEngine::GL::Line(Vector2(screen_center.x, screen_center.y), Vector2(screen_center.x, screen_center.y - 7), Crosshair_Color);
	}

	if (m_settings::Swastika)
	{
		auto sped = m_settings::SwastikaSpeed / 10;
		float speed = sped;
		float razmer = 10;
		bool cadicall = false;

		float xs = screen_center.x, ys = screen_center.y;
		static float rotation_degree = 0.f;
		if (rotation_degree > 89.f)
			rotation_degree = 0.f;
		rotation_degree += speed;
		int length = (int)(screen_center.x / razmer / m_settings::SwastikaSize);
		float gamma = Math::atanf(length / length);
		int i = 0;
		while (i < 4)
		{
			std::vector <int> p
			{
				int(length * Math::sinf(GRD_TO_BOG(rotation_degree + (i * 90)))),
					int(length * Math::cosf(GRD_TO_BOG(rotation_degree + (i * 90)))),
					int((length / Math::cosf(gamma)) * Math::sinf(GRD_TO_BOG(rotation_degree + (i * 90) + RAD2DEG(gamma)))),
					int((length / Math::cosf(gamma)) * Math::cosf(GRD_TO_BOG(rotation_degree + (i * 90) + RAD2DEG(gamma))))
			};

			UnityEngine::GL::Line(Vector2(xs, ys), Vector2(xs + p[0], ys - p[1]), Color::Red());
			UnityEngine::GL::Line(Vector2(xs + p[0], ys - p[1]), Vector2(xs + p[2], ys - p[3]), Color::Red());

			i++;
		}
	}

	if (m_settings::Aimline)
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {
			auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(m_target.m_player))
			{
				auto AimLine_Color = Color(ColorSettings::TargetSnapline_Color.r, ColorSettings::TargetSnapline_Color.g, ColorSettings::TargetSnapline_Color.b, ColorSettings::TargetSnapline_Color.a);

				auto targetPos = m_target.m_position;
				if (!targetPos.IsZero())
				{
					auto bulletTPPos = Features().BulletTPAngle;

					if (bulletTPPos.IsZero())
					{
						bulletTPPos = targetPos;
					}

					Vector2 w2sPos;
					if (UnityEngine::WorldToScreen(bulletTPPos, w2sPos))
					{
						UnityEngine::GL::Line(Vector2(UnityEngine::Screen::get_width() / 2.f, UnityEngine::Screen::get_height() / 2.f), w2sPos, AimLine_Color);
					}
				}
			}
		}
	}

	if (m_settings::ShowCachedLOS) {
		if (Features().ConstantLOSCheck == true)
			UnityEngine::GL().ScreenTextCenter(Vector2(center_x, center_y - 400), XS("Cached Visible"), Color::Red(), Color::Black(), m_settings::fontsize);

	}

	if (m_settings::AimMarker)
	{
		auto camera = UnityEngine::Camera::get_main();
		if (IsAddressValid(camera)) {
			auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(m_target.m_player))
			{
				auto AimMarker_Color = Color(ColorSettings::TargetMarker_Color.r, ColorSettings::TargetMarker_Color.g, ColorSettings::TargetMarker_Color.b, ColorSettings::TargetMarker_Color.a);

				auto targetPos = m_target.m_position;

				if (!targetPos.IsZero())
				{
					Vector2 w2sPos;

					if (UnityEngine::WorldToScreen(targetPos, w2sPos))
					{
						UnityEngine::GL().ScreenTextCenter(w2sPos, XS("X"), AimMarker_Color, Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
					}
				}
			}
		}
	}

	if (m_settings::SavePos)
	{
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		if (IsAddressValid(LocalPlayer)) {
			auto CurrentPos = LocalPlayer->get_bone_transform(47)->get_position();
			static Vector2 SavedPos;

			if (UnityEngine::Input::GetKey(m_settings::SavePosKey))
			{
				SavedWorldPos = CurrentPos;
			}

			if (UnityEngine::WorldToScreen(SavedWorldPos, SavedPos))
			{
				auto distance = CurrentPos.Distance(SavedWorldPos);

				std::string player_name = "SavedPos";
				char str[256];
				sprintf(str, XS("[%dm]"), (int)distance);
				player_name = player_name + " " + str;

				UnityEngine::GL().WorldTextCenter(SavedPos, player_name.c_str(), Color::Cyan(), Color::Black(), m_settings::fontsize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
			}
		}
	}

	if (m_settings::SaveHouse)
	{
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		if (IsAddressValid(LocalPlayer)) {
			auto CurrentPos = LocalPlayer->get_bone_transform(47)->get_position();
			static Vector2 SavedPos;

			if (UnityEngine::Input::GetKey(m_settings::SaveHouseKey))
			{
				SavedHousePos = CurrentPos;
			}

			if (UnityEngine::WorldToScreen(SavedHousePos, SavedPos))
			{
				auto distance = CurrentPos.Distance(SavedHousePos);

				std::string player_name = "Home";
				char str[256];
				sprintf(str, XS("[%dm]"), (int)distance);
				player_name = player_name + " " + str;

				UnityEngine::GL().WorldTextCenter(SavedPos, player_name.c_str(), Color::Cyan(), Color::Black(), m_settings::fontsize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
			}
		}
	}

	if (m_settings::DrawFov)
	{
		auto Fov_Color = Color(ColorSettings::FOV_Color.r, ColorSettings::FOV_Color.g, ColorSettings::FOV_Color.b, ColorSettings::FOV_Color.a);
		UnityEngine::GL::Circle(screen_center, m_settings::AimbotFOV, Fov_Color, 100);
	}

	if (m_settings::BulletTPFlags && m_settings::Thickbullet_Indicator && m_settings::BulletTP)
	{
		UnityEngine::GL().ScreenTextCenter(Vector2(center_x, center_y - yPos), XS("Bullet TP"), Color::Red(), Color::Black(), m_settings::fontsize);
		yPos += 10;
	}

	if (m_settings::InstantBullet)
	{
		auto desynctime = UnityEngine::Time::get_realtimeSinceStartup() - AssemblyCSharp::LocalPlayer::get_Entity()->lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;


		if (desyncpercentage >= 0.85f)
		{
			UnityEngine::GL().ScreenTextCenter(Vector2(center_x, center_y - yPos), XS("Instant Hit"), Color::Red(), Color::Black(), m_settings::fontsize);
			yPos += 10;
		}
	}

	if (m_settings::AutoReload)
	{

		if (auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity())
		{
			if (LocalPlayer->lifestate() != RustStructs::Dead)
			{
				if (auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>())
				{
					if (BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::Planner::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()))
					{
						if (auto HeldItem = Features().LocalPlayer->ActiveItem())
						{
							if (!BaseProjectile->HasReloadCooldown())
							{
								if (m_settings::did_reload == false && m_settings::time_since_last_shot <= (m_settings::reload_time - (m_settings::reload_time / 10)) && m_settings::time_since_last_shot > 0)
								{
									float time_full = (m_settings::reload_time - (m_settings::reload_time / 10));
									float time_left = m_settings::time_since_last_shot;
									auto percentage = (((time_left / time_full) * 100.0f) + 1.f) / 100;
									float bars = 0;
									float red, green, blue;
									float Num = percentage;

									if (Num < 0.5) {
										red = Num * 2.f * 255.f;
										green = 255.f;
										blue = 0.f;
									}
									else {
										red = 255.f;
										green = (2.f - 2.f * Num) * 255.f;
										blue = 0.f;
									}


									if (Num > 0.01) {
										float xzzzz = bars++;

										if (auto mag = BaseProjectile->primaryMagazine())
										{
											if (auto def = mag->ammoType())
											{
												if (auto test = def->FindIconSprite(HeldItem->info()->itemid()))
												{
													if (auto texture = test->get_texture())
													{
														auto rect = test->get_rect();

														if (m_settings::AutoReloadIcon)
															UnityEngine::GL().DrawIcon(Vector2(screen_center.x - 25, screen_center.y + 68), Vector2(rect.wid / 4.5f, rect.hei / 4.5f), texture, Color::White());
													}
												}
											}
										}
										auto xpostop = screen_center.x - 50;
										auto xpostop2 = screen_center.x - 49;
										auto ypostop = screen_center.y + yoffset;
										UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 1 }, { xpostop + 100, ypostop + 2 }, Color(0, 0, 0, 255.f).GetUnityColor());
										UnityEngine::GL::RectangleFilled({ xpostop, ypostop + 1 }, { xpostop + 100, ypostop + 4 }, Color(0, 0, 0, 255.f).GetUnityColor());
										UnityEngine::GL::RectangleFilled({ xpostop2, ypostop }, { xpostop2 + (100 * (time_left / time_full)), ypostop + 3 }, Color((int)(red), (int)(green), (int)(blue), 255.f).GetUnityColor());
										yoffset += 10;
									}
								}
							}
							else
							{
								m_settings::time_since_last_shot = 0.f;
								m_settings::just_shot = false;
								m_settings::did_reload = true;
							}

						}
					}
					else
					{
						m_settings::time_since_last_shot = 0.f;
						m_settings::just_shot = false;
						m_settings::did_reload = true;
					}
				}
			}
		}
	}

	if (m_settings::Manipulation && m_settings::BulletTP && m_settings::BulletTPFlags && m_settings::ManipFlags && m_settings::Manipulation_Indicator)
	{
		UnityEngine::GL().ScreenTextCenter(Vector2(center_x, center_y - yPos), XS("Manipulated"), Color::Red(), Color::Black(), m_settings::fontsize);
		yPos += 10;
	}
	else if (m_settings::ManipFlags && m_settings::Manipulation_Indicator && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		UnityEngine::GL().ScreenTextCenter(Vector2(center_x, center_y - yPos), XS("Manipulated"), Color::Red(), Color::Black(), m_settings::fontsize);
		yPos += 10;
	}

	if (m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
	{
		auto desynctime = UnityEngine::Time::get_realtimeSinceStartup() - AssemblyCSharp::LocalPlayer::get_Entity()->lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;

		float red, green, blue;
		float Num = desyncpercentage;
		float bars = 0;

		if (desyncpercentage < 0.1)
			Num = 0;

		if (Num != 0) {
			if (Num < 0.5) {
				red = Num * 2.f * 255.f;
				green = 255.f;
				blue = 0.f;
			}
			else {
				red = 255.f;
				green = (2.f - 2.f * Num) * 255.f;
				blue = 0.f;
			}

			if (Num > 1.f)
				Num = 1.f;


			float xzzzz = bars++;


			auto xpostop = screen_center.x - 50;
			auto xpostop2 = screen_center.x - 49;
			auto ypostop = screen_center.y + yoffset;
			UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 1 }, { xpostop + 100, ypostop + 2 }, Color(0, 0, 0, 255.f).GetUnityColor());
			UnityEngine::GL::RectangleFilled({ xpostop, ypostop + 1 }, { xpostop + 100, ypostop + 4 }, Color(0, 0, 0, 255.f).GetUnityColor());
			UnityEngine::GL::RectangleFilled({ xpostop2, ypostop }, { xpostop2 + (100 * desynctime), ypostop + 3 }, Color((int)(red), (int)(green), (int)(blue), 255.f).GetUnityColor());
			yoffset += 10;
		}
	}

	if (m_settings::Flyhack_Indicator)
	{
		float YPos = (UnityEngine::screen_size.y / 8);
		int YOffset = 40;

		float bar_width = 200.f;
		float x = screen_center.x;
		float y = screen_center.y;
		float w = 300.f;
		float h = 10.f;

		auto FlyhackColorY = Color(0.f, 255.f, 0.f, 255.f);
		auto FlyhackColorX = Color(0.f, 255.f, 0.f, 255.f);

		const auto horizontal_percentage = minm(m_settings::HorisontalFlyhack / m_settings::MaxHorisontalFlyhack, 1.f);
		const auto vertical_percentage = minm(m_settings::VerticalFlyhack / m_settings::MaxVerticalFlyhack, 1.f);

		if (vertical_percentage > 0.5 && vertical_percentage < 0.8)
			FlyhackColorY = Color(255.f, 137.f, 0.f, 255.f);
		else if (vertical_percentage > 0.8)
			FlyhackColorY = Color(255.f, 0.f, 0.f, 255.f);
		else
			FlyhackColorY = Color(0.f, 255.f, 0.f, 255.f);

		if (horizontal_percentage > 0.5 && horizontal_percentage < 0.8)
			FlyhackColorX = Color(255.f, 137.f, 0.f, 255.f);
		else if (horizontal_percentage > 0.8)
			FlyhackColorX = Color(255.f, 0.f, 0.f, 255.f);
		else
			FlyhackColorX = Color(0.f, 255.f, 0.f, 255.f);

		auto xpostop = x - w / 2;
		auto ypostop = YPos - YOffset;
		UnityEngine::GL::RectangleFilled({ xpostop, ypostop }, { xpostop + w, ypostop + h }, Color(34.f, 34.f, 34.f, 255.f).GetUnityColor());
		UnityEngine::GL::RectangleFilled({ xpostop, ypostop }, { xpostop + w * horizontal_percentage, ypostop + h }, FlyhackColorX.GetUnityColor());

		UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 10 }, { xpostop + w, ypostop + h - 10 }, Color(34.f, 34.f, 34.f, 255.f).GetUnityColor());
		UnityEngine::GL::RectangleFilled({ xpostop, ypostop - 10 }, { xpostop + w * vertical_percentage, ypostop + h - 10 }, FlyhackColorY.GetUnityColor());

		UnityEngine::GL::Rectangle({ xpostop, ypostop }, { xpostop + w, ypostop + h }, Color(0.f, 0.f, 0.f, 120.f).GetUnityColor());
		UnityEngine::GL::Rectangle({ xpostop, ypostop - 10 }, { xpostop + w, ypostop + h - 10 }, Color(0.f, 0.f, 0.f, 120.f).GetUnityColor());
	}
}

const wchar_t* ConvertToWideString(const char* str) //imports
{
	// Get the length of the wide string
	size_t length = LI_FN(mbstowcs)(nullptr, str, 0);

	// Allocate memory for the wide string
	wchar_t* wideStr = new wchar_t[length + 1];

	// Convert the string to wide string
	LI_FN(mbstowcs)(wideStr, str, length + 1);

	return wideStr;
}

auto prefab_spawner() -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	if (!IsAddressValid(Features().LocalPlayer->eyes()))
		return;

	if (m_settings::HerbertPrefabSpawn && UnityEngine::Input::GetKeyDown(m_settings::HerbertKey))
	{
		if (IsAddressValid(HerbertPrefab))
		{
			auto lookingatPoint = Features().LocalPlayer->lookingAtPoint();
			UnityEngine::Object().Instantiate(HerbertPrefab, lookingatPoint, Features().LocalPlayer->eyes()->get_rotation());
		}
	}

	if (m_settings::AmongusPrefabSpawn && UnityEngine::Input::GetKeyDown(m_settings::AmongusKey))
	{
		if (IsAddressValid(AmongusPrefab))
		{
			auto lookingatPoint = Features().LocalPlayer->lookingAtPoint();
			UnityEngine::Object().Instantiate(AmongusPrefab, lookingatPoint, Features().LocalPlayer->eyes()->get_rotation());

		}
	}
}

inline Vector2 hotbar_pos;
inline Vector2 window_size2;
inline bool sex2 = false;
inline void DrawPlayerHotbar(UnityEngine::Event* event, const Vector2& pos, const Vector2& window_size) {
	if (m_settings::SelectedHotbar == 1 || m_settings::SelectedHotbar == 2)
	{
		if (!sex2) {
			hotbar_pos = pos;
			sex2 = true;
		}

		window_size2 = window_size;

		auto mouse = UnityEngine::Input::GetMousePosition();
		auto width = UnityEngine::Screen::get_width();
		auto height = UnityEngine::Screen::get_height();
		auto menu_event = event->Type();
		auto key_code = UnityEngine::Event::get_keyCode(event);

		//mouse_pos.x = UnityEngine::Input::GetMousePosition().x;
		//mouse_pos.y = UnityEngine::Screen::get_height() - UnityEngine::Input::GetMousePosition().y;
		auto mouse_state = UnityEngine::Input::GetMouseButton(0);

		//if (main_menu_open)
		//{
		//	if (Menu().is_mouse_in_box({ hotbar_pos.x, hotbar_pos.y }, { hotbar_pos.x + window_size2.x, hotbar_pos.y + window_size2.y }) && mouse_state && !hover_element) {
		//		hotbar_pos.x += mouse_pos.x - old_mouse_pos.x;
		//		hotbar_pos.y += mouse_pos.y - old_mouse_pos.y;
		//	}
		//	else {
		//		hover_element = false;
		//	}

		//}

		auto camera = UnityEngine::Camera::get_main();
		float info_y = 0;
		float info_y_icons = 0;

		float TestPos = 0;

		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(AimbotTarget.m_player))
			{
				auto inventory = AimbotTarget.m_player->inventory();
				if (IsAddressValid(inventory))
				{
					if (m_settings::SelectedHotbar == 1) {
						auto containerBelt = inventory->containerBelt();
						if (IsAddressValid(containerBelt))
						{
							auto ItemList = containerBelt->itemList();
							if (IsAddressValid(ItemList))
							{
								if (menu_event == RustStructs::EventType::Repaint)
								{
									for (int i = 0; i < ItemList->_size; i++) {
										auto item = ItemList->_items->m_Items[i];
										if (!IsAddressValid(item))
											continue;

										if (i > ItemList->_size - 1)
										{
											info_y += 13;
											continue;
										}

										if (IsAddressValid(item)) {

											auto amount = item->amount();
											auto name = item->GetItemName();

											auto camera = UnityEngine::Camera::get_main();
											if (IsAddressValid(camera)) {
												auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
												if (IsAddressValid(m_target.m_player))
												{
													if (IsAddressValid(name))
													{
														std::string ItemName = "";
														char str[256];
														sprintf(str, XS("[%d] %s"), (int)amount, name->string_safe().c_str());
														ItemName = str;

														if (IsAddressValid(item->heldEntity()) && IsAddressValid(item->heldEntity()->prefabID())) {
															if (item->heldEntity() && m_target.m_player && m_target.m_player->ActiveItem()) {
																if (item->heldEntity()->prefabID() == m_target.m_player->ActiveItem()->heldEntity()->prefabID())
																	UnityEngine::GL().ScreenTextCenter(Vector2(hotbar_pos.x, hotbar_pos.y + info_y), ItemName.c_str(), Color::Turquoise(), Color::Black(), m_settings::fontsize);
															}
															else
																UnityEngine::GL().ScreenTextCenter(Vector2(hotbar_pos.x, hotbar_pos.y + info_y), ItemName.c_str(), Color::White(), Color::Black(), m_settings::fontsize);
														}
													}
												}
											}
										}

										info_y += 13;
									}
									info_y += 10;
									//info_y = 0;
								}
							}
						}
					}
					if (m_settings::SelectedHotbar == 2) {
						auto containerBelt = inventory->containerBelt();
						if (IsAddressValid(containerBelt))
						{
							auto ItemList = containerBelt->itemList();
							if (IsAddressValid(ItemList))
							{
								if (menu_event == RustStructs::EventType::Repaint)
								{
									if (IsAddressValid(AimbotTarget.m_player->get_displayName())) {
										std::string player_name = utf16_to_utf8(AimbotTarget.m_player->get_displayName()->c_str());

										//BackGround
										{
											UnityEngine::GL::ScreenTextCenter(Vector2(hotbar_pos.x, hotbar_pos.y + 12.5), player_name.c_str(), Color::White(), Color::Black(), 10);
										}
									}

									Vector2 Size = Vector2(60, 60);

									for (int i = 0; i < 6; i++) {
										UnityEngine::GL::RectangleFilled(Vector2(hotbar_pos.x - (((Size.x + 5) * 6) / 2) + TestPos, hotbar_pos.y + 20.f), Vector2(hotbar_pos.x - (((Size.x + 5) * 6) / 2) + TestPos + Size.x, hotbar_pos.y + 20.f + Size.y), Color(34.f, 34.f, 34.f, 120.f).GetUnityColor());
										TestPos += 65;
									}

									for (int i = 0; i < 6; i++) {
										auto item = ItemList->_items->m_Items[i];
										if (!IsAddressValid(item))
											continue;

										if (i > ItemList->_size - 1)
										{
											info_y_icons += 65;
											continue;
										}

										if (IsAddressValid(item)) {

											auto name = item->GetItemName();

											auto sprite_the_drink = item->get_iconSprite();
											if (!IsAddressValid(sprite_the_drink))
												continue;

											auto texture = sprite_the_drink->get_texture();
											if (!IsAddressValid(texture))
												continue;

											auto camera = UnityEngine::Camera::get_main();
											if (IsAddressValid(camera)) {
												auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
												if (IsAddressValid(m_target.m_player))
												{
													if (IsAddressValid(name))
													{
														if (IsAddressValid(item->heldEntity()) && IsAddressValid(item->heldEntity()->prefabID())) {
															if (item->heldEntity() && m_target.m_player && m_target.m_player->ActiveItem()) {
																if (item->heldEntity()->prefabID() == m_target.m_player->ActiveItem()->heldEntity()->prefabID())
																	UnityEngine::GL::RectangleFilled(Vector2(hotbar_pos.x - (((Size.x + 5) * 6) / 2) + info_y_icons, hotbar_pos.y + 20.f), Vector2(hotbar_pos.x - (((Size.x + 5) * 6) / 2) + info_y_icons + Size.x, hotbar_pos.y + 20.f + Size.y), Color(0.f, 24.f, 143.f, 120.f).GetUnityColor());
															}

															UnityEngine::GL().DrawIcon(Vector2(hotbar_pos.x - (((Size.x + 5) * 6) / 2) + info_y_icons, hotbar_pos.y + 20.f), Size, texture, Color::White());
														}
													}
												}
											}
										}

										info_y_icons += 65;
									}

									TestPos = 0;
									info_y_icons = 0;
								}
							}
						}
					}
				}
			}
		}
		//Menu().end_window();
	}
}

inline Vector2 hotbar_pos_c;
inline Vector2 window_size2_c;
inline bool sex2_c = false;

inline void DrawPlayerClothing(UnityEngine::Event* event, const Vector2& pos, const Vector2& window_size) {
	if (m_settings::SelectedClothing == 1 || m_settings::SelectedClothing == 2)
	{
		if (!sex2_c) {
			hotbar_pos_c = pos;
			sex2_c = true;
		}

		window_size2_c = window_size;

		auto mouse = UnityEngine::Input::GetMousePosition();
		auto width = UnityEngine::Screen::get_width();
		auto height = UnityEngine::Screen::get_height();
		auto menu_event = event->Type();
		auto key_code = UnityEngine::Event::get_keyCode(event);

		//mouse_pos.x = UnityEngine::Input::GetMousePosition().x;
		//mouse_pos.y = UnityEngine::Screen::get_height() - UnityEngine::Input::GetMousePosition().y;
		//auto mouse_state = UnityEngine::Input::GetMouseButton(0);

		//if (main_menu_open)
		//{
		//	if (Menu().is_mouse_in_box({ hotbar_pos_c.x, hotbar_pos_c.y }, { hotbar_pos_c.x + window_size2_c.x, hotbar_pos_c.y + window_size2_c.y }) && mouse_state && !hover_element) {
		//		hotbar_pos_c.x += mouse_pos.x - old_mouse_pos.x;
		//		hotbar_pos_c.y += mouse_pos.y - old_mouse_pos.y;
		//	}
		//	else {
		//		hover_element = false;
		//	}

		//}

		auto camera = UnityEngine::Camera::get_main();
		float info_y = 0;
		float info_y_icons = 0;
		float TestPos = 0;
		if (IsAddressValid(camera)) {
			auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
			if (IsAddressValid(AimbotTarget.m_player))
			{
				auto inventory = AimbotTarget.m_player->inventory();
				if (IsAddressValid(inventory))
				{
					if (m_settings::SelectedClothing == 1) {
						auto containerWear = inventory->containerWear();
						if (IsAddressValid(containerWear))
						{
							auto ItemList = containerWear->itemList();
							if (IsAddressValid(ItemList))
							{
								for (int i = 0; i < ItemList->_size; i++) {
									auto item = ItemList->_items->m_Items[i];
									if (!IsAddressValid(item))
										continue;

									if (i > ItemList->_size - 1)
									{
										info_y += 13;
										continue;
									}

									if (IsAddressValid(item)) {

										auto name = item->GetItemName();

										auto camera = UnityEngine::Camera::get_main();
										if (IsAddressValid(camera)) {
											auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);

											if (IsAddressValid(m_target.m_player))
											{
												if (IsAddressValid(name)) {
													std::string ItemName = "";
													char str[256];
													sprintf(str, XS("%s"), name->string_safe().c_str());
													ItemName = str;

													UnityEngine::GL().ScreenTextCenter(Vector2(hotbar_pos_c.x, hotbar_pos_c.y + info_y), ItemName.c_str(), Color::White(), Color::Black(), m_settings::fontsize);
												}
											}
										}
									}

									info_y += 13;
								}
								info_y = 0;
							}
						}
					}
					if (m_settings::SelectedClothing == 2) {
						auto containerBelt = inventory->containerWear();
						if (IsAddressValid(containerBelt))
						{
							auto ItemList = containerBelt->itemList();
							if (IsAddressValid(ItemList))
							{
								if (menu_event == RustStructs::EventType::Repaint)
								{
									Vector2 Size = Vector2(60, 60);

									for (int i = 0; i < 7; i++) {
										UnityEngine::GL::RectangleFilled(Vector2(hotbar_pos_c.x - (((Size.x + 5) * 7) / 2) + TestPos, hotbar_pos_c.y + 20.f), Vector2(hotbar_pos_c.x - (((Size.x + 5) * 7) / 2) + TestPos + Size.x, hotbar_pos_c.y + 20.f + Size.y), Color(34.f, 34.f, 34.f, 120.f).GetUnityColor());
										TestPos += 65;
									}

									for (int i = 0; i < ItemList->_size; i++) {
										auto item = ItemList->_items->m_Items[i];
										if (!IsAddressValid(item))
											continue;

										if (i > ItemList->_size - 1)
										{
											info_y_icons += 65;
											continue;
										}

										if (IsAddressValid(item)) {

											auto sprite_the_drink = item->get_iconSprite();
											if (!IsAddressValid(sprite_the_drink))
												continue;

											auto texture = sprite_the_drink->get_texture();
											if (!IsAddressValid(texture))
												continue;

											auto camera = UnityEngine::Camera::get_main();
											if (IsAddressValid(camera)) {
												auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
												if (IsAddressValid(m_target.m_player))
												{
													if (IsAddressValid(texture)) {
														UnityEngine::GL().DrawIcon(Vector2(hotbar_pos_c.x - (((Size.x + 5) * 7) / 2) + info_y_icons, hotbar_pos_c.y + 20.f), Size, texture, Color::White());
													}
												}
											}
										}

										info_y_icons += 65;
									}
									TestPos = 0;
									info_y_icons = 0;
								}
							}
						}
					}
				}
			}
		}

		//Menu().end_window();
	}
}

void SetupTextures()
{
	if (!AK47Icon)
	{
		AK47Icon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("ak47.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!BoltyIcon)
	{
		BoltyIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("bolt-action-rifle.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!CompoundBowIcon)
	{
		CompoundBowIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("compound-bow.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!CrossbowIcon)
	{
		CrossbowIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("crossbow.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!CustomSMGIcon)
	{
		CustomSMGIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("custom-smg.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!DoubleBarrelIcon)
	{
		DoubleBarrelIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("double-barrel.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!EokaIcon)
	{
		EokaIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("eoka.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!HMLmgIcon)
	{
		HMLmgIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("hmlmg.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!HuntingBowIcon)
	{
		HuntingBowIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("hunting-bow.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!LR300Icon)
	{
		LR300Icon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("lr300.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!M39Icon)
	{
		M39Icon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("m39.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!M92Icon)
	{
		M92Icon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("m92.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!M249Icon)
	{
		M249Icon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("m249.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!Mp4a4Icon)
	{
		Mp4a4Icon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("mp5.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!PistolIcon)
	{
		PistolIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("p250.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!PumpShotgunIcon)
	{
		PumpShotgunIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("pump-shotgun.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!PythonIcon)
	{
		PythonIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("python.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!RevolverIcon)
	{
		RevolverIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("revolver.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!SarIcon)
	{
		SarIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("sar.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}

	if (!Spas12Icon)
	{
		Spas12Icon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("spas-12.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}	

	if (!ThompsonIcon)
	{
		ThompsonIcon = IconBundle->LoadAsset<UnityEngine::Texture2D>(XS("thompson.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
	}
}

static inline bool HasTriggered = false;
void Hooks::OnGUI(AssemblyCSharp::ExplosionsFPS* _This)
{
	screen_center = { UnityEngine::Screen::get_width() / 2.f, UnityEngine::Screen::get_height() / 2.f };
	UnityEngine::screen_size = { (float)UnityEngine::Screen::get_width(), (float)UnityEngine::Screen::get_height() };

	//ConnectorClient();

	if (!Hooks::ProjectileUpdatehk.IsHooked())
	{
		Hooks::ProjectileUpdatehk.PointerSwapHook(XS("Projectile"), HASH("Update"), &Hooks::ProjectileUpdate, XS(""), 0);
	}

	if (!Hooks::ClientInputhk.IsHooked())
	{
		Hooks::ClientInputhk.VirtualFunctionHook(XS("BasePlayer"), HASH("ClientInput"), &Hooks::ClientInput, XS(""), 1);
	}

	if (!Hooks::SteamPlatformUpdatehk.IsHooked())
	{
		Hooks::SteamPlatformUpdatehk.VirtualFunctionHook(XS("SteamPlatform"), HASH("Update"), &Hooks::SteamPlatformUpdate, XS("Rust.Platform.Steam"), 0);
	}

	if (!Hooks::OnAttackedhk.IsHooked())
	{
		Hooks::OnAttackedhk.VirtualFunctionHook(XS("BasePlayer"), HASH("OnAttacked"), &Hooks::OnAttacked, XS(""), 1);
	}

	/*if (!Hooks::SkyUpdatehk.IsHooked())
	{
		Hooks::SkyUpdatehk.PointerSwapHook(XS("TOD_Camera"), HASH("Update"), &Hooks::SkyUpdate, XS(""), 0);
	}*/

	SetupBundles();

	//if (!font_bundle)
	//	LoadFontBundle();

	//if (font_bundle)
	{//
		SetupStyles();

		GUI().SetupGUI();

		//if (!TestBundle) {
		//	TestBundle = UnityEngine::AssetBundle::LoadFromFile_Internal("C:/Damascus.unity3d", 0, 0);
		//	LOG(XS("[DEBUG] Loaded TestBundle"));
		//}

		//if (IconBundle)
		//	SetupTextures();

		GUI().DrawMenu();

		auto m_Event = UnityEngine::Event::Current();
		if (IsAddressValid(m_Event))
		{
			TextDrawBegin();

			if (m_Event->Type() == RustStructs::EventType::Repaint)
			{
				if (ConnectionManager().IsConnected())
					InGame = true;
				else
					InGame = false;

				notifcations::object.run();

				static bool has_init = false;
				if (!has_init)
				{
					const auto string = std::wstring(XS(L"[Serotonin] Successfully Loaded!"));
					notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

					has_init = true;
				}

				if (!HasLoadedAllBundles) {
					float center_x = (float)(UnityEngine::screen_size.x) / 2, center_y = (float)(UnityEngine::screen_size.y) / 16;

					UnityEngine::GL().MenuText(Vector2(center_x, 10), XS("Initializing Cheat, Please wait..."), Color::White(), Color::Black(), true);
				}
				else {
					static bool has_init = false;
					if (!has_init)
					{
						const auto string = std::wstring(XS(L"[Serotonin] Successfully Loaded All Bundles!"));
						notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
						has_init = true;
					}
				}


				static std::string Message;
				static bool DisplayMessage = false;
				if (Message != GlobalMessage)
				{
					if (DisplayMessage)
						DisplayMessage = false;
					Message = GlobalMessage;
				}
				if (Message == GlobalMessage) {
				
					if (!DisplayMessage) {						
				
						auto Text = ConvertToWideString(GlobalMessage.c_str());
						notifcations::object.push(Text, UnityEngine::Time::get_time());
						DisplayMessage = true;
					}
				}

				if (InGame)
				{
					drawMisc();

					//if (m_settings::RaidESP)
					//{
					//	drawRaidESP();
					//}

					float x = screen_center.x;
					float YPos = (UnityEngine::screen_size.y / 8);
					int YOffset = 40;

					if (m_settings::SelectedHotbar == 1 && m_settings::SelectedClothing == 1)
					{
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerHotbar(m_Event, { x,  YPos - YOffset + 20 }, WindowSize);
						YOffset += 20.f;
					}
					else if (m_settings::SelectedHotbar == 2 && m_settings::SelectedClothing == 1)
					{
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerHotbar(m_Event, { x,  YPos - YOffset + 20 }, WindowSize);
						YOffset += 20.f;
					}
					else if (m_settings::SelectedHotbar == 1) {
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerHotbar(m_Event, { x,  YPos - YOffset + 20 }, WindowSize);
						YOffset += 10.f;
					}
					else if (m_settings::SelectedHotbar == 2)
					{
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerHotbar(m_Event, { x,  YPos - YOffset + 20 }, WindowSize);
						YOffset += 5.f;
					}

					if (m_settings::SelectedClothing == 1) {
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerClothing(m_Event, { x,  YPos + YOffset + 10 }, WindowSize);
						YOffset += 25.f;
					}
					else if (m_settings::SelectedClothing == 2) {
						Vector2 WindowSize = Vector2(200, 50);

						DrawPlayerClothing(m_Event, { x,  YPos + YOffset }, WindowSize);
						YOffset += 25.f;
					}
					YOffset = 40;

					if (m_settings::HerbertPrefabSpawn || m_settings::AmongusPrefabSpawn)
						prefab_spawner();

					Visuals().CachePlayers();
					Visuals().DrawPlayers();

					//static float send_time = UnityEngine::Time::get_realtimeSinceStartup();
					//float current_time = UnityEngine::Time::get_realtimeSinceStartup();
					//if (current_time - send_time > 5.f)
					//{
						//LOG(XS("[DEBUG] Speed"));

						Visuals().CacheEntities();

					//	send_time = current_time;
					//}
		
					//if (!PrefabVectorList.empty())
						Visuals().RenderEntities();
				}	
			}

			TextDrawEnd();
		}
	}

#ifdef DEBUG_MODE
	if (UnityEngine::Input::GetKey(RustStructs::End))
	{
		connector::cheat_message msg;
		msg.msg = connector::messages::LEAVE_SHARED_ESP;
		msg.value = XS("TrollServer1"); //Name of channel
		auto data = connector::data(msg);
		net->send_data(data);
		delete net;

		MenuIconBundles->Unload(true);
		MenuIconBundles = nullptr;

		SerotoninIconBundle->Unload(true);
		SerotoninIconBundle = nullptr;

		/* Chams */
		{

			if (HerbetAsset)
			{
				HerbetAsset->Unload(true);
				HerbetAsset = nullptr;

				if (HerbertPrefab)
				{
					HerbertPrefab = nullptr;
				}
			}

			if (AmongUsAsset)
			{
				AmongUsAsset->Unload(true);
				AmongUsAsset = nullptr;

				if (AmongusPrefab)
				{
					AmongusPrefab = nullptr;
				}
			}

			if (ExplosionAsset)
			{
				ExplosionAsset->Unload(true);
				ExplosionAsset = nullptr;

				if (ExplosionPrefab)
				{
					ExplosionPrefab = nullptr;
				}
			}

			if (GhostAsset)
			{
				GhostAsset->Unload(true);
				GhostAsset = nullptr;

				if (GhostPrefab)
				{
					GhostPrefab = nullptr;
				}
			}

			if (TestAsset)
			{
				TestAsset->Unload(true);
				TestAsset = nullptr;

				if (TestPrefab)
				{
					TestPrefab = nullptr;
				}
			}



			if (GalaxyBundle)
			{
				GalaxyBundle->Unload(true);
				GalaxyBundle = nullptr;
				GalaxyShader = nullptr;
				GalaxyMaterial = nullptr;
			}

			if (WireFrameBundle)
			{
				WireFrameBundle->Unload(true);
				WireFrameBundle = nullptr;
				WireFrameShader = nullptr;
				WireFrameMaterial = nullptr;
			}

			if (FireBundleA)
			{
				FireBundleA->Unload(true);
				FireBundleA = nullptr;
				FireShaderA = nullptr;
				FireMaterialA = nullptr;
			}

			if (RPBGalaxyBundle)
			{
				RPBGalaxyBundle->Unload(true);
				RPBGalaxyBundle = nullptr;
				RPBGalaxyShader = nullptr;
				RPBGalaxyMaterial = nullptr;
			}

			if (FireBundleB)
			{
				FireBundleB->Unload(true);
				FireBundleB = nullptr;
				FireShaderB = nullptr;
				FireMaterialB = nullptr;
			}

			if (GeometricBundle)
			{
				GeometricBundle->Unload(true);
				GeometricBundle = nullptr;
				GeometricShader = nullptr;
				GeometricMaterial = nullptr;
			}

			if (ColorBundle)
			{
				ColorBundle->Unload(true);
				ColorBundle = nullptr;
				ColorShader = nullptr;
				ColorMaterial = nullptr;
			}

			if (LightningBundle)
			{
				LightningBundle->Unload(true);
				LightningBundle = nullptr;
				LightningShader = nullptr;
				LightningMaterial = nullptr;
			}

			if (DamascusBundle)
			{
				DamascusBundle->Unload(true);
				DamascusBundle = nullptr;
				DamascusShader = nullptr;
				DamascusMaterial = nullptr;
			}

			if (font_bundle)
			{
				font_bundle->Unload(true);
				font_bundle = nullptr;
			}

			if (font_bundle2)
			{
				font_bundle2->Unload(true);
				font_bundle2 = nullptr;
			}

			if (IconBundle)
			{
				IconBundle->Unload(true);
				IconBundle = nullptr;
			}

			if (TestBundle)
			{
				TestBundle->Unload(true);
				TestBundle = nullptr;
				TestShader = nullptr;
				TestMaterial = nullptr;
			}

			if (GlitterBundle)
			{
				GlitterBundle->Unload(true);
				GlitterBundle = nullptr;
				GlitterShader = nullptr;
				GlitterMaterial = nullptr;
			}
		}

		white_texture = 0;
		skin = 0;
		label_style = 0;

	/*	auto base = m_game_assembly;
		{
			memory::address_t klass = ScanImage(base, XS("4C 8B 0D ? ? ? ? 4D 8B C7 48 8B 15 ? ? ? ? 48 8B CF"));
			klass.self_jmp(0x3);
			memory::address_t function = init_type_info(klass);
			auto address = function.offset(0x38).get(2);
			*(uint64_t*)(address.cast<uint64_t>() + 0x8) = o_projectile_shoot;
		}

		projectile_shoot_class = nullptr;
		o_projectile_shoot.clear();*/

		Hooks::ClientInputhk.Unhook();
		ConnectionManager().Instance()->ResetPlayerCache();
		Hooks::ProjectileShootHookhk.Unhook();
		Hooks::DoAttackhk.Unhook();
		Hooks::ProjectileUpdatehk.Unhook();
		Hooks::PPA_WriteToStreamhk.Unhook();
		Hooks::PlayerWalkMovementhk.Unhook();
		Hooks::TryToMovehk.Unhook();
		Hooks::SkyUpdatehk.Unhook();
		Hooks::SteamPlatformUpdatehk.Unhook();
		Hooks::OnAttackedhk.Unhook();
		Hooks::BlockSprinthk.Unhook();
		Hooks::LateUpdatehk.Unhook();
		Hooks::OnNetworkMessagehk.Unhook();
		Hooks::OnInputhk.Unhook();
		//Hooks::DoAttackBowhk.Unhook();
		Hooks::DoAttackMeleehk.Unhook();
		//Hooks::IsAiminghk.Unhook();
		Hooks::ProcessAttackhk.Unhook();
		Hooks::GetRandomVelocityhk.Unhook();

		Hooks::FlintStrikeWeaponDoAttackhk.Unhook();
		Hooks::OnGUIhk.Unhook();
		Hooks::Update_hk.Unhook();
	}
#endif

	return;
}