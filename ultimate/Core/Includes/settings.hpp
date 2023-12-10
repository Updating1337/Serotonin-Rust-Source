#pragma once

#include "../SDK/RustStructs.h"

namespace m_settings {
	inline bool LoadRage = false;
	inline bool LoadLegit = false;
	inline bool SelectedOption = false;
	inline bool FontChanger = false;
	inline int BuildingGrade = 0;
	inline bool SilentAim = false;
	inline bool PlayerChams = false;
	inline bool NoMovementRestrictions = false;
	inline bool AlwaysHotspot = false;
	inline bool Weather = false;
	inline bool NoClouds = false;
	inline bool NoAtmosphere = false;
	inline bool AtmosphereContrast = false;
	inline bool RainbowSky = false;
	inline float RainbowAmount = 40.f;
	inline bool TargetAttackHeli = false;
	inline bool Waves = false;
	inline bool Rainbows = false;
	inline bool report_player = false;
	inline RustStructs::KeyCode report_key = RustStructs::F;
	inline bool NoFog = false;
	inline bool NoRain = false;
	inline bool ViewDirection = false;
	inline bool NoThunder = false;
	inline bool TeamCheck = false;
	inline bool NoWind = false;
	inline float AimbotSmoothness = 5.f;
	inline bool ShowPrediction = false;
	inline float AimbotFOV = 200.f;
	inline float TestSlider = 24.f;
	inline bool NormalThickBullet = false;
	inline float BradleyColor[4] = { 255.f, 0.f, 0.f, 255.f };
	inline bool AutoUpgrade = false;
	inline bool DrawInventory = false;
	inline bool DrawInventoryIcons = false;
	inline bool DoorSpammer = false;
	inline float MaxTurretDistance = 50.f;
	inline bool ShowAlerts = false;
	inline bool DrawClothing = false;
	inline bool Radar = false;
	inline float RadarSize = 200;
	inline int RadarPosX;
	inline int RadarPosY;
	inline bool AutoReloadIcon = false;
	inline bool TC_Health = false;
	inline bool TC_Upkeep = false;
	inline bool LongMelee = false;
	inline bool AuthorizedPlayers = false;
	inline bool DrawClothingIcons = false;
	inline float AuthorizedPlayersDistance = 100.f;
	inline float SilentSpread = 100.f;
	inline bool DrawManipPoints = false;
	inline float NormalThickBulletThickness = 4.4f;
	inline bool AimbotNPC = false;
	inline bool RaidESP = false;
	inline bool ShowRocket = false;
	inline bool BehindWall = false;
	inline bool ShowC4 = false;
	inline bool ShowSatchel = false;
	inline bool ShowExplosiveAmmo = false;
	inline bool DisableHitSounds = false;
	inline bool CustomHitSounds = false;
	inline float LOSCheckAmount = 1000;
	inline bool CacheBulletTP = false;
	inline bool AdvancedChecks = false;
	inline bool ShowCachedLOS = false;
	inline bool ShowCachedPoint = false;

	inline bool HammerSpam = false;
	inline RustStructs::KeyCode HammerSpamKey = RustStructs::KeyCode::Z;

	inline int HitMaterial = 0;
	inline bool SilentWalk = false;
	inline RustStructs::KeyCode SilentWalkKey = RustStructs::KeyCode::H;

	inline RustStructs::KeyCode AimbotKey = RustStructs::KeyCode::Mouse0;

	inline bool TeleportMax = false;
	inline RustStructs::KeyCode TeleportMaxKey = RustStructs::KeyCode::H;
	inline bool WeaponChams = false;
	inline bool HeliAimbot = false;
	inline int HammerMaterialType = 0;
	inline bool RemoveAttackAnimations = false;
	inline bool TurretOnFlags = false;
	inline bool AmongusPrefabSpawn = false;
	inline bool HerbertPrefabSpawn = false;
	inline RustStructs::KeyCode AmongusKey = RustStructs::KeyCode::F;
	inline RustStructs::KeyCode HerbertKey = RustStructs::KeyCode::C;
	inline bool HeldItemIcon = false;

	inline float SpeedhackSpeed = 0.f;
	inline bool Speedhack = false;
	inline RustStructs::KeyCode SpeedhackKey = RustStructs::KeyCode::F;

	inline float ManipPoints = 5;
	inline bool ReportAllAuthedTurret = false;
	inline bool InstantEoka = false;
	inline bool TargetWounded = false;
	inline bool ShowUsers = false;
	inline bool NameSpoofer = false;
	inline bool RandomName = false;
	inline bool CustomName = false;
	inline std::string custom_name = "";
	inline int SelectedBoxESP = 0;
	inline int HeldItemType = 0;
	inline int SelectedHealthBar = 0;
	inline int SelectedHotbar = 0;
	inline int SelectedClothing = 0;
	inline int SelectedOutsideType = 0;
	inline int HealthBar = 0;
	inline int VisCheckType = 0;

	inline int SelectedAimbone = 0;
	inline bool MeleeAimbot = false;
	inline bool FloorHugger = false;
	inline bool HackableCrateTimer = false;
	inline bool AlwaysManipulate = false;
	inline bool PatrolHelicopter = false;
	inline bool DrawDistance = false;
	inline bool InteractiveDebug = false;
	inline bool HackableCrateFlags = false;
	inline bool InstantBullet = false;
	inline bool FixDebugCamera = false;
	inline bool DebugCamera = false;
	inline bool AdjustNoClipSpeed = false;
	inline int SelectedChams = 0;
	inline int WeaponSelectedChams = 0;
	inline int SelectedConfig = 0;
	inline bool InstantKill = false;
	inline bool WaitForBulletTP = false;
	inline bool Target_Indicator = false;
	inline bool NormalFastBullet = false;
	inline bool NoWeaponBob = false;
	inline bool VelocityAimbot = false;
	inline bool RotationAimbot = false;
	inline RustStructs::KeyCode RotationKey = RustStructs::KeyCode::Mouse1;
	inline RustStructs::KeyCode DebugCameraKey = RustStructs::KeyCode::X;

	inline bool ValidVelocity = true;
	inline float VelocityScale = 70.f;
	inline bool WeaponSpammer;
	inline float WeaponSpamDelay = 10.f;
	inline RustStructs::KeyCode InteractiveKey = RustStructs::KeyCode::F;

	inline RustStructs::KeyCode WeaponSpamKey = RustStructs::KeyCode::F;
	inline bool PierceMaterials = false;
	inline bool Crosshair = true;
	inline bool BaseCheck = false;
	inline bool BulletTracers = false;
	inline int SelectedHitbox = 0;
	inline int BulletTPIntensity = 0;
	inline int ManipMode = 0;
	inline bool AutoReload = false;
	inline bool HeliHitboxOverride = false;
	inline bool Aimline = false;
	inline bool HitboxOverride = false;
	inline float reload_time = 0.f;
	inline float BulletTPRadius = 2.4f;
	inline bool OOFIndicators = false;
	inline bool AimMarker = false;
	inline bool DrawFov = false;
	inline bool TargetFriendList = false;
	inline bool InstantLoot = false;
	inline float Fov_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float Crosshair_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float AimbotAccuracy = 100.f;
	inline bool ChangeRecoil = false;
	inline bool Thickbullet_Arrows = false;
	inline bool BulletTP = false;
	inline bool Manipulation = false;
	inline bool StopPlayer = false;
	inline bool ManipFlags = false;
	inline bool SnickerBullet = false;
	inline bool BulletTPFlags = false;
	inline bool BlockServerCommands = false;
	inline bool Autoshoot = false;
	inline bool AlwaysAutoshoot = false;
	inline bool NoSpread = false;
	inline bool ChangeSpread = false;
	inline bool NoSway = false;
	inline bool OnHalfDesync = false;
	inline bool FastBullets = false;
	inline bool LoadGlitterChams = false;
	inline bool LoadDamascusChams = false;
	inline float BulletsSpeeds = 100;
	inline bool SilentMelee = false;
	inline RustStructs::KeyCode ManipKey = RustStructs::KeyCode::F;
	inline RustStructs::KeyCode AddFriend = RustStructs::KeyCode::Keypad0;
	inline RustStructs::KeyCode RemoveFriend = RustStructs::KeyCode::Keypad1;
	inline RustStructs::KeyCode RemoveAllFriends = RustStructs::KeyCode::Keypad2;
	inline bool just_shot = false;
	inline bool did_reload = false;
	inline bool reload_reset = false;
	inline bool reload_reset_2 = false;
	inline float time_since_last_shot = 0.0f;
	inline float fixed_time_last_shot = 0.0f;
	inline bool removefriend1 = false;
	inline bool removefriend2 = false;
	inline bool removefriend3 = false;
	inline bool ForceAutomatic = false;
	inline bool DoVelocityPrediction = false;

	inline bool LoadGalaxy = false;
	inline bool LoadRBP = false;
	inline bool LoadLightning = false;
	inline bool LoadGeometric = false;
	inline bool LoadWireFrame = false;

	inline RustStructs::KeyCode AutoshootKey = RustStructs::KeyCode::F;
	inline bool IncludeFatBullet = false;

	inline float recoilPercent = 100;
	inline int RecoilPercentY = 100;

	inline bool AdminFlags = false;
	inline bool AdminCheat = true;
	inline RustStructs::KeyCode AdminCheatKey = RustStructs::KeyCode::C;
	inline bool SmallerLocalRadius = false;
	inline bool SpiderMan = false;
	inline bool InfiniteJump = false;
	inline bool NoAttackRestrictions = false;
	inline bool AlwaysSprint = false;
	inline bool OmniSprint = false;
	inline bool InstantHeal = false;
	inline bool IgnoreTrees = false;
	inline bool IgnorePlayers = false;
	inline bool InstantRevive = false;
	inline bool PlayerFov = false;
	inline bool AntiDeathBarrier = false;
	inline float PlayerFovAmount = 90.f;
	inline bool Zoom = false;
	inline RustStructs::KeyCode ZoomKey = RustStructs::KeyCode::G;
	inline float ZoomAmount = 50.f;

	inline bool ChangeCameraMode = false;
	inline RustStructs::CameraMode CameraMode = RustStructs::CameraMode::FirstPerson;
	inline float CameraDistance = 3.f;

	inline RustStructs::KeyCode SuicideKey = RustStructs::KeyCode::K;
	inline bool Suicide = false;

	inline bool AutoFarmTree = false;
	inline bool AutoFarmOre = false;

	inline RustStructs::KeyCode InstantReviveKey = RustStructs::KeyCode::F;
	inline bool KeepTargetAlive = false;
	inline RustStructs::KeyCode KeepAliveKey = RustStructs::KeyCode::F;
	inline bool Spinbot = false;
	inline bool LootBodyThruWall = false;
	inline RustStructs::KeyCode LootBodyThruWallKey = RustStructs::KeyCode::X;
	inline bool LootCorpseThruWall = false;
	inline RustStructs::KeyCode LootCorpseThruWallKey = RustStructs::KeyCode::Z;

	inline bool LoadAmongusAsset = false;
	inline bool LoadHerbertAsset = false;

	inline bool ShotIndicators = false;

	inline float DGradientPos = 0.f;
	inline float DGradientSpread = 0.5f;
	inline bool Stash = false;
	inline bool Hemp = false;
	inline bool CollectablesIcon = false;
	inline bool WaitForInstantHit = false;
	inline bool ShowBulletTPAngle = false;
	inline bool DroppedItems = false;
	inline bool DroppedItemsChams = false;
	inline float DroppedItemColor[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float HempColor[4] = { 0.f, 176.f, 21.f, 255.f };
	inline float DieselColor[4] = { 72.f, 72.f, 72.f, 255.f };
	inline float StoneColor[4] = { 238.f, 238.f, 238.f, 255.f };
	inline float MetalColor[4] = { 100.f, 49.f, 49.f, 255.f };
	inline float SulfurColor[4] = { 238.f, 238.f, 0.f, 255.f };
	inline float TrapsColor[4] = { 245, 188, 66, 255.f };
	inline float MaxTCDistance = 250.f;
	inline float VehicleColor[4] = { 66, 245, 167, 255.f };
	inline float DeployableColor[4] = { 245, 87, 66, 255.f };
	inline float MaxDroppedDistance = 50.f;
	inline float MaxTrapsDistance = 50.f;
	inline float MaxDeployableDistance = 50.f;
	inline float MaxCrateDistance = 50.f;
	inline float MaxSupplyDropDistance = 500.f;
	inline float MaxFoodDistance = 50.f;
	inline float MaxAPCDistance = 1500.f;
	inline float MaxVehicleDistance = 100.f;
	inline float MaxPlayerDropsDistance = 50.f;
	inline float MaxAnimalDistance = 50.f;
	inline bool StoneOre = false;
	inline bool MetalOre = false;
	inline bool SulfurOre = false;
	inline bool OreIcons = false;
	inline float MaxOreDistance = 100.f;
	inline float MaxCollectableDistance = 50.f;
	inline float IconsScale = 24.f;

	inline bool Mushroom = false;
	inline bool Pumpkin = false;
	inline bool Corn = false;
	inline bool Potato = false;
	inline bool FoodIcons = false;
	inline bool cupboard = false;

	inline bool Bear = false;
	inline bool Wolf = false;
	inline bool Stag = false;
	inline bool Boar = false;
	
	inline bool T1Workbench = false;
	inline bool T2Workbench = false;
	inline bool T3Workbench = false;

	inline bool Recycler = false;

	inline bool DieselBarrel = false;
	inline float WorldFontSize = 8.f;

	inline float MushRoomColor[4] = { 66.f, 126.f, 51.f, 255.f };
	inline float PumpkinColor[4] = { 66.f, 126.f, 51.f, 255.f };
	inline float CornColor[4] = { 66.f, 126.f, 51.f, 255.f };
	inline float PotatoColor[4] = { 66.f, 126.f, 51.f, 255.f };

	inline bool Corpse = false;
	inline bool BackPack = false;

	inline static std::vector<bool> FoodOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> CrateOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> DeployableOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> TurretOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> OreOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> CollectableOpions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> LoadChams{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> LoadHitEffects{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> TrapsOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> VehicleOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> RaidOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline static std::vector<bool> CupboardOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	inline static std::vector<bool> DroppedOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	inline float CorpseColor[4] = { 201.f, 235.f, 168.f, 255.f };
	inline float BackPackColor[4] = { 238.f, 238.f, 238.f, 255.f };

	inline bool AutoTurret = false;
	inline bool ShotgunTrap = false;
	inline bool BearTrap = false;
	inline bool SpikesTrap = false;
	inline bool FlameTurret = false;
	inline bool LandMine = false;
	inline bool HackableCrate = false;
	inline bool BradleyCrate = false;
	inline bool HeliCrate = false;
	inline bool BradleyAPC = false;
	inline bool SamSite = false;

	inline bool StoneCollectable = false;
	inline bool MetalCollectable = false;
	inline bool SulfurCollectable = false;

	inline bool TurretRange = false;
	inline bool TurretAuthorizedPlayers = false;
	inline bool TurretTurningFlag = false;
	inline bool bottomhealthbar = false;
	inline bool PlayerChamss = false;
	inline bool lefthealthbar = false;
	inline bool InventoryIcons = false;
	inline bool InventoryText = false;
	inline bool TurretEquippedFlags = false;
	inline bool ClothingText = false;
	inline bool ClothingIcons = false;
	inline bool TurretHealth = false;
	inline float TurretColor[4] = { 238.f, 0.f, 0.f, 255.f };
	inline float CrateColor[4] = { 0.f, 255.f, 255.f, 255.f };
	inline float HeliColor[4] = { 255.f, 0.f, 0.f, 255.f };
	//esp
	inline bool SavePos = false;
	inline RustStructs::KeyCode SavePosKey = RustStructs::KeyCode::F;

	inline bool SaveHouse = false;
	inline RustStructs::KeyCode SaveHouseKey = RustStructs::KeyCode::F;

	inline float MaxExplosionDistance = 5000.f;
	inline float MaxRaidTimer = 120.f;

	inline bool ShowOutside = false;
	inline bool ShowInside = false;
	inline bool ExplosionEffect = false;
	inline bool GhostEffect = false;
	inline bool nameEsp = true;
	inline bool BoxEsp = false;
	inline bool Swastika = false;
	inline float SwastikaSpeed = 1.f;
	inline float SwastikaSize = 15.f;
	inline bool CornerBox = false;
	inline bool healthBar = true;
	inline bool Skeleton = true;
	inline bool helditem = false;
	inline bool ammoESP = false;
	inline bool EspVisCheck = false;
	inline float DrawBox_Color[4] = { 205.f, 5.0f, 2.0f, 255.f };
	inline float VisCheck_Color[4] = { 63.f, 210.0f, 0.0f, 255.f };
	inline float DrawNameTag_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float DrawHeldItem_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float Friend_Color[4] = { 0.f, 255.f, 255.f, 255.f };
	inline float Wounded_Color[4] = { 255.f, 149.f, 0.f, 255.f };
	inline float Scientist_color[4] = { 29.f, 31.f, 161.f, 255.f };
	inline float Dead_Color[4] = { 255.f, 255.f, 255.f, 255.f };
	inline float Safezone_Color[4] = { 204.f, 88.0f, 202.f, 255.f };
	inline float Target_Color[4] = { 91, 23, 227, 255.f };
	inline float fontsize = 10.f;
	inline float ESPFontsize = 10.f;
	inline bool TagsVisCheck = false;

	inline bool WorldOutlinedText = true;
	inline bool WorldShadedText = false;
	inline bool OutlinedText = true;
	inline bool ShadedText = false;

	inline int SelectedKillEffect = 0;
	inline bool KillEffects = false;
	inline bool LoadExplosionEffect = false;
	inline bool LoadGhostEffect = false;

	inline bool DrawNPC = false;
	inline float NPCDistance = 30.f;
	inline bool DrawDead = false;
	inline bool DrawAis = true;
	inline bool DrawSleepers = false;
	inline float Sleeper_Color[4] = { 0.0f, 255.f, 255.f, 255.f };
	inline bool DrawWounded = false;
	inline bool DrawTarget = false;
	inline bool DrawSafezone = false;
	inline float PlayerESPDistance = 500.f;

	inline bool Flyhack_Indicator = true;
	inline bool AntiFlyKick = false;
	inline float MaxVerticalFlyhack;
	inline float VerticalFlyhack;
	inline float MaxHorisontalFlyhack;
	inline float HorisontalFlyhack;

	inline bool GrenadePrediction = false;
	inline bool RocketPrediction = false;
	inline bool WalkToMarker = false;

	inline bool Teleport = false;
	inline RustStructs::KeyCode TeleportKey = RustStructs::KeyCode::F;

	inline bool AutoMini = false;
	inline float MaxMiniSpeed = 1.f;
	inline float HoverHeight = 150.f;
	inline bool HoverMini = false;
	inline bool NoSun = false;

	inline bool GestureSpam = false;
	inline int gesture = 0;
	inline bool AutoMed = false;
	inline int fonttype = 0;

	inline bool MemoryAimbot = false;
	inline RustStructs::KeyCode MemoryAimbotKey = RustStructs::KeyCode::F;

	inline bool Brightnight = false;
	inline bool CustomSky = false;
	inline bool BrightAmbient = false;
	inline bool Stars = false;
	inline bool SkyColorDay = false;
	inline bool SkyColorNight = false;
	inline bool BrightCave = false;
	inline bool SharpClouds = false;
	inline bool TimeChanger = false;
	inline float GameTime = 12.f;
	inline bool RemoveUnderwaterEffects = false;

	inline float last_tick_time = 0.f;
	inline float max_spoofed_eye_distance = 0.f;
	inline bool can_manipulate = false;
	inline bool StartShooting = false;
	inline bool Manipulation_Indicator = false;
	inline bool Thickbullet_Indicator = false;
	inline bool Thickbullet_AutoShoot = false;

	inline bool horseEsp = false;
	inline bool BasicCrate = false;
	inline bool NormalCrate = false;
	inline bool MinicopterEsp = false;

	inline bool OnlyGloves = false;
	inline bool OnlyHands = false;
	inline bool OnlyWeapon = false;
	inline bool MilitaryCrate = false;
	inline bool EliteCrate = false;
	inline bool SupplyDrop = false;
	inline bool LootBarrel = false;

	inline bool OilBarrel = false;
	inline bool TugBoat = false;
	inline bool Minicopter = false;
	inline bool ScrapHeli = false;
	inline bool Rhib = false;
	inline bool Rowboat = false;
	inline bool AttackHeli = false;

	inline bool IgnoreArms = false;

	inline bool HideWeaponMods = false;
	inline bool HideMeleeItems = false;
	inline bool HideTier1Weapons = false;
	inline bool HideTier2Weapons = false;
	inline bool HideTier3Weapons = false;
	inline bool HideWorkbenches = false;
	inline bool HideResources = false;
	inline bool HideArmor = false;
	inline bool HideTools = false;
	inline bool HideExplosive = false;
	inline bool HideMedical = false;
	inline bool HideAmmo = false;
	inline bool HideComponents = false;

};

//inline RustStructs::KeyCode ManipulationKey = RustStructs::KeyCode::F;
