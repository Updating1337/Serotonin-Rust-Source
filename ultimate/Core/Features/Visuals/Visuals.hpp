#pragma once

#include "../../CRT/memory.hpp"
#include <vector>
#include "../../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../Features/Features.hpp"
inline static bool CachedPointss = false;

inline UnityEngine::AssetBundle* RPBGalaxyBundle;
inline UnityEngine::Shader* RPBGalaxyShader;
inline UnityEngine::Material* RPBGalaxyMaterial;

inline UnityEngine::AssetBundle* font_bundle;
inline UnityEngine::AssetBundle* font_bundle2;

inline UnityEngine::AssetBundle* FireBundleA;
inline UnityEngine::Shader* FireShaderA;
inline UnityEngine::Material* FireMaterialA;

inline UnityEngine::AssetBundle* FireBundleB;
inline UnityEngine::Shader* FireShaderB;
inline UnityEngine::Material* FireMaterialB;

inline UnityEngine::AssetBundle* ColorBundle;
inline UnityEngine::Shader* ColorShader;
inline UnityEngine::Material* ColorMaterial;

inline UnityEngine::AssetBundle* IconBundle;
inline UnityEngine::AssetBundle* TestBundle;
inline UnityEngine::Shader* TestShader;
inline UnityEngine::Material* TestMaterial;

inline UnityEngine::AssetBundle* GalaxyBundle;
inline UnityEngine::Shader* GalaxyShader;
inline UnityEngine::Material* GalaxyMaterial;

inline UnityEngine::AssetBundle* GeometricBundle;
inline UnityEngine::Shader* GeometricShader;
inline UnityEngine::Material* GeometricMaterial;

inline UnityEngine::AssetBundle* LightningBundle;
inline UnityEngine::Shader* LightningShader;
inline UnityEngine::Material* LightningMaterial;

inline UnityEngine::AssetBundle* WireFrameBundle;
inline UnityEngine::Shader* WireFrameShader;
inline UnityEngine::Material* WireFrameMaterial;

inline UnityEngine::AssetBundle* GlitterBundle;
inline UnityEngine::Shader* GlitterShader;
inline UnityEngine::Material* GlitterMaterial;

inline UnityEngine::AssetBundle* DamascusBundle;
inline UnityEngine::Shader* DamascusShader;
inline UnityEngine::Material* DamascusMaterial;

static UnityEngine::AssetBundle* AmongUsAsset = nullptr;
static UnityEngine::AssetBundle* HerbetAsset = nullptr;
inline UnityEngine::AssetBundle* ExplosionAsset = nullptr;
inline UnityEngine::AssetBundle* GhostAsset = nullptr;
inline UnityEngine::AssetBundle* TestAsset = nullptr;

inline static bool HasLoadedAllBundles = false;

class VisualsVector {
public:
	VisualsVector(AssemblyCSharp::BasePlayer* player)
	{
		this->BasePlayer = player;
	}
public:
	AssemblyCSharp::BasePlayer* BasePlayer;
};
static inline bool DoNoclip = false;
static inline bool DebugCamera = false;

inline std::vector< VisualsVector> VisualsArray;
inline std::vector< VisualsVector> VisualsArrayTemp;


inline UnityEngine::GameObject* ExplosionPrefab = nullptr;
inline UnityEngine::GameObject* GhostPrefab = nullptr;
inline UnityEngine::GameObject* AmongusPrefab = nullptr;
inline UnityEngine::GameObject* HerbertPrefab = nullptr;
inline UnityEngine::GameObject* TestPrefab = nullptr;

/* Icons */
inline UnityEngine::Texture2D* AK47Icon = nullptr;
inline UnityEngine::Texture2D* BoltyIcon = nullptr;
inline UnityEngine::Texture2D* CompoundBowIcon = nullptr;
inline UnityEngine::Texture2D* CrossbowIcon = nullptr;
inline UnityEngine::Texture2D* CustomSMGIcon = nullptr;
inline UnityEngine::Texture2D* DoubleBarrelIcon = nullptr;
inline UnityEngine::Texture2D* EokaIcon = nullptr;
inline UnityEngine::Texture2D* HMLmgIcon = nullptr;
inline UnityEngine::Texture2D* HuntingBowIcon = nullptr;
inline UnityEngine::Texture2D* LR300Icon = nullptr;
inline UnityEngine::Texture2D* M39Icon = nullptr;
inline UnityEngine::Texture2D* M92Icon = nullptr;
inline UnityEngine::Texture2D* M249Icon = nullptr;
inline UnityEngine::Texture2D* Mp4a4Icon = nullptr;
inline UnityEngine::Texture2D* PistolIcon = nullptr;
inline UnityEngine::Texture2D* PumpShotgunIcon = nullptr;
inline UnityEngine::Texture2D* PythonIcon = nullptr;
inline UnityEngine::Texture2D* RevolverIcon = nullptr;
inline UnityEngine::Texture2D* SarIcon = nullptr;
inline UnityEngine::Texture2D* Spas12Icon = nullptr;
inline UnityEngine::Texture2D* ThompsonIcon = nullptr;


inline Vector3 HeadBone;
inline Vector3 NeckBone;
inline Vector3 Spine;

inline AssemblyCSharp::BasePlayer* EspBasePlayer;

class PrefabList {
public:
	PrefabList(AssemblyCSharp::BaseNetworkable* _This)
	{
		if (IsAddressValid(_This))
		{
			this->CachedEntity = _This;
		}
	}

	AssemblyCSharp::BaseNetworkable* CachedEntity;

	// Equality comparison operator
	bool operator==(const PrefabList& other) const {
		// Define your comparison logic here
		return (CachedEntity == other.CachedEntity);
	}
};

inline std::vector< PrefabList> PrefabVectorList;
inline std::vector< PrefabList> PrefabListTemp;


inline float timee = 120.f;

struct Explosion {
public:
	std::string name;
	float timeSince;
	Vector3 position;
	int amount = 1;
};

class LogSystem {
public:
	static inline int max_entries = 10;

	static inline std::vector<Explosion> loggedExplosions = std::vector<Explosion>();

	static inline void LogExplosion(std::string type, Vector3 pos) {
		if (!InGame)
			return;

		bool explosionCollision = false;
		std::vector<Explosion>::iterator it;
		for (it = loggedExplosions.begin(); it != loggedExplosions.end(); it++) {
			Vector2 explPos;
			
			if (it->position.Distance(pos) <= 25.0f) {

				explosionCollision = true;
				break;
			}			
		}
		if (!explosionCollision) {
			Explosion explosion = Explosion();
			char str[256];
			sprintf(str, XS("%s"), type.c_str());
			explosion.name = str;
			explosion.position = pos;
			explosion.timeSince = UnityEngine::Time::get_realtimeSinceStartup();
			loggedExplosions.push_back(explosion);
		}
	}

	static inline void RenderExplosions() {
		if (!InGame)
			return;

		if (!IsAddressValid(Features().LocalPlayer))
			return;

		for (int i = 0; i < LogSystem::loggedExplosions.size(); i++) {
			if ((UnityEngine::Time::get_realtimeSinceStartup() - LogSystem::loggedExplosions[i].timeSince) >= m_settings::MaxRaidTimer) {
				LogSystem::loggedExplosions.erase(LogSystem::loggedExplosions.begin() + i);
				continue;
			}

			Explosion explosion = LogSystem::loggedExplosions.at(i);

			Vector2 explPos;

			if (explosion.position.Distance(Features().LocalPlayer->get_transform()->get_position()) <= m_settings::MaxExplosionDistance)
			{
				if (UnityEngine::WorldToScreen(explosion.position, explPos))
				{
					auto yoffset = 0.f;

					std::string raiddistance;
					char str[256];
					sprintf(str, XS("Raid [%1.0fm]"), explosion.position.get_3d_dist(Features().LocalPlayer->get_transform()->get_position()));
					raiddistance += str;

					std::string explosionType;
					char str1[256];
					sprintf(str1, XS("%s [%d]"), explosion.name.c_str(), (int)LogSystem::loggedExplosions[i].amount);
					explosionType += str1;

					std::string TimeSinceLastShot;
					char str2[256];
					sprintf(str2, XS("LastShot: [%d]"), (int)((UnityEngine::Time::get_realtimeSinceStartup() - LogSystem::loggedExplosions[i].timeSince)));
					TimeSinceLastShot += str2;


					UnityEngine::GL().TextCenter(Vector2(explPos.x, explPos.y + yoffset), raiddistance.c_str(), Color::Red(), Color::Black(), m_settings::fontsize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
					yoffset += 13.f;

					UnityEngine::GL().TextCenter(Vector2(explPos.x, explPos.y + yoffset), TimeSinceLastShot.c_str(), Color::Turquoise(), Color::Black(), m_settings::fontsize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
					yoffset += 13.f;

					UnityEngine::GL().TextCenter(Vector2(explPos.x, explPos.y + yoffset), explosionType.c_str(), Color::White(), Color::Black(), m_settings::fontsize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
					yoffset += 13.f;
				}
			}
		
		}
	}
};
class Visuals {
public:
	static auto Instance() -> Visuals*
	{
		Visuals obj;
		return &obj;
	}
	box_bounds get_bounds(AssemblyCSharp::BasePlayer* player, float expand = 0);
public:
	void CachePlayers();
	void DrawPlayers();
	using List = FPSystem::ListDictionary< uint64_t, AssemblyCSharp::BasePlayer* >;
	List* VisiblePlayerList ;

	void CacheEntities();
	void RenderEntities();

public:
	AssemblyCSharp::BasePlayer::Target GetAimbotTargetSafe(Vector3 Source, float MaxDist = 500);
};