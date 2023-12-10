#include "Configs.hpp"
#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../SDK/System/System.hpp"
inline bool gggg = false;
#include "../Utils/json.hpp"
#include "../Features/Notifications/Notifications.hpp"
using json = nlohmann::json;

void Configs::LoadConfig()
{
    std::string file_name;
    if (m_settings::SelectedConfig == 0)
    {
        file_name = XS("Legit.json");
    }
    else if (m_settings::SelectedConfig == 1)
    {
        file_name = XS("Rage.json");
    }
    else if (m_settings::SelectedConfig == 2)
    {
        file_name = XS("Config1.json");
    }
    else if (m_settings::SelectedConfig == 3)
    {
        file_name = XS("Config2.json");
    }
    else if (m_settings::SelectedConfig == 4)
    {
        file_name = XS("Config3.json");
    }

    FILE* file = LI_FN(fopen)(file_name.c_str(), XS("r"));
    if (file == nullptr) {
        // Handle error: Unable to open the file
        return;
    }

    LI_FN(fseek)(file, 0, SEEK_END);
    long fileSize = LI_FN(ftell)(file);
    LI_FN(fseek)(file, 0, SEEK_SET);

    if (fileSize <= 0) {
        LI_FN(fclose)(file);
        return;
    }

    char* buffer = new char[fileSize + 1];
    LI_FN(fread)(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    LI_FN(fclose)(file);

    nlohmann::json config = nlohmann::json::parse(buffer);

    // Set your variables from the loaded JSON data
    m_settings::SilentAim = config[XS("SilentAim")];
    m_settings::RotationAimbot = config[XS("RotationAimbot")];
    m_settings::VelocityAimbot = config[XS("VelocityAimbot")];
    m_settings::MeleeAimbot = config[XS("MeleeAimbot")];
    m_settings::SilentMelee = config[XS("SilentMelee")];
    m_settings::AimbotNPC = config[XS("AimbotNPC")];
    m_settings::TargetWounded = config[XS("TargetWounded")];
    m_settings::Autoshoot = config[XS("Autoshoot")];
    m_settings::Manipulation = config[XS("Manipulation")];
    m_settings::BulletTP = config[XS("BulletTP")];
    m_settings::CacheBulletTP = config[XS("CacheBulletTP")];
    m_settings::AdvancedChecks = config[XS("AdvancedChecks")];
    m_settings::BehindWall = config[XS("BehindWall")];
    m_settings::AlwaysAutoshoot = config[XS("AlwaysAutoshoot")];
    m_settings::StopPlayer = config[XS("StopPlayer")];
    m_settings::PierceMaterials = config[XS("PierceMaterials")];
    m_settings::InstantKill = config[XS("InstantKill")];
    m_settings::InstantBullet = config[XS("InstantBullet")];
    m_settings::WaitForInstantHit = config[XS("WaitForInstantHit")];
    m_settings::AutoReload = config[XS("AutoReload")];
    m_settings::HitboxOverride = config[XS("HitboxOverride")];
    m_settings::Crosshair = config[XS("Crosshair")];
    m_settings::Swastika = config[XS("Swastika")];
    m_settings::DrawFov = config[XS("DrawFov")];
    m_settings::Aimline = config[XS("Aimline")];
    m_settings::AimMarker = config[XS("AimMarker")];
    m_settings::Target_Indicator = config[XS("Target_Indicator")];
    m_settings::BulletTracers = config[XS("BulletTracers")];
    m_settings::ManipFlags = config[XS("ManipFlags")];
    m_settings::DrawManipPoints = config[XS("DrawManipPoints")];
    m_settings::BulletTPFlags = config[XS("BulletTPFlags")];
    m_settings::ShowBulletTPAngle = config[XS("ShowBulletTPAngle")];
    m_settings::Thickbullet_Arrows = config[XS("Thickbullet_Arrows")];
    m_settings::ShowCachedLOS = config[XS("ShowCachedLOS")];
    m_settings::ShowCachedPoint = config[XS("ShowCachedPoint")];
    m_settings::SnickerBullet = config[XS("SnickerBullet")];
    m_settings::nameEsp = config[XS("nameEsp")];
    m_settings::Skeleton = config[XS("Skeleton")];
    m_settings::DroppedItems = config[XS("DroppedItems")];
    m_settings::Flyhack_Indicator = config[XS("Flyhack_Indicator")];
    m_settings::AntiFlyKick = config[XS("AntiFlyKick")];
    m_settings::AntiDeathBarrier = config[XS("AntiDeathBarrier")];
    m_settings::SpiderMan = config[XS("SpiderMan")];
    m_settings::SmallerLocalRadius = config[XS("SmallerLocalRadius")];
    m_settings::AdminFlags = config[XS("AdminFlags")];
    m_settings::InfiniteJump = config[XS("InfiniteJump")];
    m_settings::OmniSprint = config[XS("OmniSprint")];
    m_settings::AlwaysSprint = config[XS("AlwaysSprint")];
    m_settings::NoMovementRestrictions = config[XS("NoMovementRestrictions")];
    m_settings::IgnoreTrees = config[XS("IgnoreTrees")];
    m_settings::IgnorePlayers = config[XS("IgnorePlayers")];
    m_settings::NameSpoofer = config[XS("NameSpoofer")];
    m_settings::InstantLoot = config[XS("InstantLoot")];
    m_settings::InstantHeal = config[XS("InstantHeal")];
    m_settings::FixDebugCamera = config[XS("FixDebugCamera")];
    m_settings::Spinbot = config[XS("Spinbot")];
    m_settings::AdminCheat = config[XS("AdminCheat")];
    m_settings::InstantRevive = config[XS("InstantRevive")];
    m_settings::KeepTargetAlive = config[XS("KeepTargetAlive")];
    m_settings::LootBodyThruWall = config[XS("LootBodyThruWall")];
    m_settings::LootCorpseThruWall = config[XS("LootCorpseThruWall")];
    m_settings::InteractiveDebug = config[XS("InteractiveDebug")];
    m_settings::SilentWalk = config[XS("SilentWalk")];
    m_settings::TeleportMax = config[XS("TeleportMax")];
    m_settings::Zoom = config[XS("Zoom")];
    m_settings::PlayerFov = config[XS("PlayerFov")];
    m_settings::AutoFarmTree = config[XS("AutoFarmTree")];
    m_settings::AutoFarmOre = config[XS("AutoFarmOre")];
    m_settings::AutoUpgrade = config[XS("AutoUpgrade")];
    m_settings::DoorSpammer = config[XS("DoorSpammer")];
    m_settings::Brightnight = config[XS("Brightnight")];
    m_settings::BrightAmbient = config[XS("BrightAmbient")];
    m_settings::Stars = config[XS("Stars")];
    m_settings::SkyColorDay = config[XS("SkyColorDay")];
    m_settings::SkyColorNight = config[XS("SkyColorNight")];
    m_settings::SharpClouds = config[XS("SharpClouds")];
    m_settings::BrightCave = config[XS("BrightCave")];
    m_settings::CustomSky = config[XS("CustomSky")];
    m_settings::TimeChanger = config[XS("TimeChanger")];
    m_settings::NoAttackRestrictions = config[XS("NoAttackRestrictions")];
    m_settings::ChangeRecoil = config[XS("ChangeRecoil")];
    m_settings::NormalThickBullet = config[XS("NormalThickBullet")];
    m_settings::NormalFastBullet = config[XS("NormalFastBullet")];
    m_settings::ForceAutomatic = config[XS("ForceAutomatic")];
    m_settings::NoWeaponBob = config[XS("NoWeaponBob")];
    m_settings::NoSway = config[XS("NoSway")];
    m_settings::InstantEoka = config[XS("InstantEoka")];
    m_settings::RemoveAttackAnimations = config[XS("RemoveAttackAnimations")];
    m_settings::DisableHitSounds = config[XS("DisableHitSounds")];
    m_settings::CustomHitSounds = config[XS("CustomHitSounds")];
    m_settings::LongMelee = config[XS("LongMelee")];
    m_settings::WeaponSpammer = config[XS("WeaponSpammer")];
    m_settings::KillEffects = config[XS("KillEffects")];
    m_settings::WeaponChams = config[XS("WeaponChams")];
    m_settings::IgnoreArms = config[XS("IgnoreArms")];
    m_settings::OutlinedText = config[XS("OutlinedText")];
    m_settings::ShadedText = config[XS("ShadedText")];
    m_settings::WorldOutlinedText = config[XS("WorldOutlinedText")];
    m_settings::WorldShadedText = config[XS("WorldShadedText")];

    //// Load the rest of the settings in a similar manner
    m_settings::WeaponSpamKey = static_cast<RustStructs::KeyCode>(config[XS("WeaponSpamKey")]);
    m_settings::RotationKey = static_cast<RustStructs::KeyCode>(config[XS("RotationKey")]);
    m_settings::AimbotKey = static_cast<RustStructs::KeyCode>(config[XS("AimbotKey")]);
    m_settings::AutoshootKey = static_cast<RustStructs::KeyCode>(config[XS("AutoshootKey")]);
    m_settings::ManipKey = static_cast<RustStructs::KeyCode>(config[XS("ManipKey")]);
    m_settings::AdminCheatKey = static_cast<RustStructs::KeyCode>(config[XS("AdminCheatKey")]);
    m_settings::InstantReviveKey = static_cast<RustStructs::KeyCode>(config[XS("InstantReviveKey")]);
    m_settings::KeepAliveKey = static_cast<RustStructs::KeyCode>(config[XS("KeepAliveKey")]);
    m_settings::LootBodyThruWallKey = static_cast<RustStructs::KeyCode>(config[XS("LootBodyThruWallKey")]);
    m_settings::LootCorpseThruWallKey = static_cast<RustStructs::KeyCode>(config[XS("LootCorpseThruWallKey")]);
    m_settings::InteractiveKey = static_cast<RustStructs::KeyCode>(config[XS("InteractiveKey")]);
    m_settings::SilentWalkKey = static_cast<RustStructs::KeyCode>(config[XS("SilentWalkKey")]);
    m_settings::TeleportMaxKey = static_cast<RustStructs::KeyCode>(config[XS("TeleportMaxKey")]);
    m_settings::ZoomKey = static_cast<RustStructs::KeyCode>(config[XS("ZoomKey")]);



    //// Load the remaining integer settings
    m_settings::WeaponSpamDelay = static_cast<int>(config[XS("WeaponSpamDelay")]);
    m_settings::SilentSpread = static_cast<int>(config[XS("SilentSpread")]);
    m_settings::NormalThickBulletThickness = static_cast<int>(config[XS("NormalThickBulletThickness")]);
    m_settings::recoilPercent = static_cast<int>(config[XS("recoilPercent")]);
    m_settings::GameTime = static_cast<int>(config[XS("GameTime")]);
    m_settings::PlayerFovAmount = static_cast<int>(config[XS("PlayerFovAmount")]);
    m_settings::AimbotAccuracy = static_cast<int>(config[XS("AimbotAccuracy")]);
    m_settings::AimbotFOV = static_cast<int>(config[XS("AimbotFOV")]);
    m_settings::SwastikaSize = static_cast<int>(config[XS("SwastikaSize")]);
    m_settings::MaxOreDistance = static_cast<int>(config[XS("MaxOreDistance")]);
    m_settings::MaxCollectableDistance = static_cast<int>(config[XS("MaxCollectableDistance")]);
    m_settings::MaxFoodDistance = static_cast<int>(config[XS("MaxFoodDistance")]);
    m_settings::MaxCrateDistance = static_cast<int>(config[XS("MaxCrateDistance")]);
    m_settings::MaxSupplyDropDistance = static_cast<int>(config[XS("MaxSupplyDropDistance")]);
    m_settings::MaxDroppedDistance = static_cast<int>(config[XS("MaxDroppedDistance")]);
    m_settings::MaxTrapsDistance = static_cast<int>(config[XS("MaxTrapsDistance")]);
    m_settings::MaxAPCDistance = static_cast<int>(config[XS("MaxAPCDistance")]);
    m_settings::MaxVehicleDistance = static_cast<int>(config[XS("MaxVehicleDistance")]);
    m_settings::MaxExplosionDistance = static_cast<int>(config[XS("MaxExplosionDistance")]);
    m_settings::AuthorizedPlayersDistance = static_cast<int>(config[XS("AuthorizedPlayersDistance")]);
    m_settings::MaxRaidTimer = static_cast<int>(config[XS("MaxRaidTimer")]);
    m_settings::ZoomAmount = static_cast<int>(config[XS("ZoomAmount")]);

    m_settings::SelectedBoxESP = static_cast<int>(config[XS("SelectedBoxESP")]);
    m_settings::HeldItemType = static_cast<int>(config[XS("HeldItemType")]);
    m_settings::SelectedHealthBar = static_cast<int>(config[XS("SelectedHealthBar")]);
    m_settings::SelectedHotbar = static_cast<int>(config[XS("SelectedHotbar")]);
    m_settings::SelectedClothing = static_cast<int>(config[XS("SelectedClothing")]);
    m_settings::SelectedOutsideType = static_cast<int>(config[XS("SelectedOutsideType")]);
    m_settings::VisCheckType = static_cast<int>(config[XS("VisCheckType")]);
    m_settings::HitMaterial = static_cast<int>(config[XS("HitMaterial")]);
    m_settings::BulletTPIntensity = static_cast<int>(config[XS("BulletTPIntensity")]);
    m_settings::ManipMode = static_cast<int>(config[XS("ManipMode")]);
    m_settings::SelectedHitbox = static_cast<int>(config[XS("SelectedHitbox")]);
    // m_settings::SelectedAimbone = static_cast<int>(config[XS("SelectedAimbone")]);
    // m_settings::BuildingGrade = static_cast<int>(config[XS("BuildingGrade")]);

    m_settings::RaidOptions[0] = config[XS("RaidOptions0")];
    m_settings::RaidOptions[1] = config[XS("RaidOptions1")];
    m_settings::RaidOptions[2] = config[XS("RaidOptions2")];
    m_settings::RaidOptions[3] = config[XS("RaidOptions3")];
    m_settings::RaidOptions[4] = config[XS("RaidOptions4")];
    m_settings::RaidOptions[5] = config[XS("RaidOptions5")];
    m_settings::RaidOptions[6] = config[XS("RaidOptions6")];
    m_settings::RaidOptions[7] = config[XS("RaidOptions7")];

    m_settings::TurretOptions[0] = config[XS("TurretOptions0")];
    m_settings::TurretOptions[1] = config[XS("TurretOptions1")];
    m_settings::TurretOptions[2] = config[XS("TurretOptions2")];
    m_settings::TurretOptions[3] = config[XS("TurretOptions3")];
    m_settings::TurretOptions[4] = config[XS("TurretOptions4")];
    m_settings::TurretOptions[5] = config[XS("TurretOptions5")];
    m_settings::TurretOptions[6] = config[XS("TurretOptions6")];
    m_settings::TurretOptions[7] = config[XS("TurretOptions7")];
    m_settings::TurretOptions[8] = config[XS("TurretOptions8")];

    m_settings::VehicleOptions[0] = config[XS("VehicleOptions0")];
    m_settings::VehicleOptions[1] = config[XS("VehicleOptions1")];
    m_settings::VehicleOptions[2] = config[XS("VehicleOptions2")];
    m_settings::VehicleOptions[3] = config[XS("VehicleOptions3")];
    m_settings::VehicleOptions[4] = config[XS("VehicleOptions4")];
    m_settings::VehicleOptions[5] = config[XS("VehicleOptions5")];
    m_settings::VehicleOptions[6] = config[XS("VehicleOptions6")];
    m_settings::VehicleOptions[7] = config[XS("VehicleOptions7")];
    m_settings::VehicleOptions[8] = config[XS("VehicleOptions8")];

    m_settings::TrapsOptions[0] = config[XS("TrapsOptions0")];
    m_settings::TrapsOptions[1] = config[XS("TrapsOptions1")];
    m_settings::TrapsOptions[2] = config[XS("TrapsOptions2")];
    m_settings::TrapsOptions[3] = config[XS("TrapsOptions3")];
    m_settings::TrapsOptions[4] = config[XS("TrapsOptions4")];
    m_settings::TrapsOptions[5] = config[XS("TrapsOptions5")];
    m_settings::TrapsOptions[6] = config[XS("TrapsOptions6")];
    m_settings::TrapsOptions[7] = config[XS("TrapsOptions7")];
    m_settings::TrapsOptions[8] = config[XS("TrapsOptions8")];

    m_settings::CupboardOptions[0] = config[XS("CupboardOptions0")];
    m_settings::CupboardOptions[1] = config[XS("CupboardOptions1")];
    m_settings::CupboardOptions[2] = config[XS("CupboardOptions2")];
    m_settings::CupboardOptions[3] = config[XS("CupboardOptions3")];
    m_settings::CupboardOptions[4] = config[XS("CupboardOptions4")];
    m_settings::CupboardOptions[5] = config[XS("CupboardOptions5")];
    m_settings::CupboardOptions[6] = config[XS("CupboardOptions6")];

    m_settings::CrateOptions[0] = config[XS("CrateOptions0")];
    m_settings::CrateOptions[1] = config[XS("CrateOptions1")];
    m_settings::CrateOptions[2] = config[XS("CrateOptions2")];
    m_settings::CrateOptions[3] = config[XS("CrateOptions3")];
    m_settings::CrateOptions[4] = config[XS("CrateOptions4")];
    m_settings::CrateOptions[5] = config[XS("CrateOptions5")];
    m_settings::CrateOptions[6] = config[XS("CrateOptions6")];
    m_settings::CrateOptions[7] = config[XS("CrateOptions7")];
    m_settings::CrateOptions[8] = config[XS("CrateOptions8")];
    m_settings::CrateOptions[9] = config[XS("CrateOptions9")];

    m_settings::OreOptions[0] = config[XS("OreOptions0")];
    m_settings::OreOptions[1] = config[XS("OreOptions1")];
    m_settings::OreOptions[2] = config[XS("OreOptions2")];
    m_settings::OreOptions[3] = config[XS("OreOptions3")];
    m_settings::OreOptions[4] = config[XS("OreOptions4")];
    m_settings::OreOptions[5] = config[XS("OreOptions5")];
    m_settings::OreOptions[6] = config[XS("OreOptions6")];
    m_settings::OreOptions[7] = config[XS("OreOptions7")];

    m_settings::CollectableOpions[0] = config[XS("CollectableOptions0")];
    m_settings::CollectableOpions[1] = config[XS("CollectableOptions1")];
    m_settings::CollectableOpions[2] = config[XS("CollectableOptions2")];
    m_settings::CollectableOpions[3] = config[XS("CollectableOptions3")];
    m_settings::CollectableOpions[4] = config[XS("CollectableOptions4")];
    m_settings::CollectableOpions[5] = config[XS("CollectableOptions5")];
    m_settings::CollectableOpions[6] = config[XS("CollectableOptions6")];
    m_settings::CollectableOpions[7] = config[XS("CollectableOptions7")];
    m_settings::CollectableOpions[8] = config[XS("CollectableOptions8")];

    m_settings::FoodOptions[0] = config[XS("FoodOptions0")];
    m_settings::FoodOptions[1] = config[XS("FoodOptions1")];
    m_settings::FoodOptions[2] = config[XS("FoodOptions2")];
    m_settings::FoodOptions[3] = config[XS("FoodOptions3")];
    m_settings::FoodOptions[4] = config[XS("FoodOptions4")];
    m_settings::FoodOptions[5] = config[XS("FoodOptions5")];
    m_settings::FoodOptions[6] = config[XS("FoodOptions6")];
    m_settings::FoodOptions[7] = config[XS("FoodOptions7")];
    m_settings::FoodOptions[8] = config[XS("FoodOptions8")];

    m_settings::DeployableOptions[0] = config[XS("DeployableOptions0")];
    m_settings::DeployableOptions[1] = config[XS("DeployableOptions1")];
    m_settings::DeployableOptions[2] = config[XS("DeployableOptions2")];
    m_settings::DeployableOptions[3] = config[XS("DeployableOptions3")];
    m_settings::DeployableOptions[4] = config[XS("DeployableOptions4")];
    m_settings::DeployableOptions[5] = config[XS("DeployableOptions5")];
    m_settings::DeployableOptions[6] = config[XS("DeployableOptions6")];
    m_settings::DeployableOptions[7] = config[XS("DeployableOptions7")];
    m_settings::DeployableOptions[8] = config[XS("DeployableOptions8")];
    m_settings::DeployableOptions[9] = config[XS("DeployableOptions9")];

    m_settings::StoneOre = config[XS("StoneOre")];
    m_settings::MetalOre = config[XS("MetalOre")];
    m_settings::SulfurOre = config[XS("SulfurOre")];
    m_settings::Hemp = config[XS("Hemp")];
    m_settings::DieselBarrel = config[XS("DieselBarrel")];
    m_settings::StoneCollectable = config[XS("StoneCollectable")];
    m_settings::MetalCollectable = config[XS("MetalCollectable")];
    m_settings::SulfurCollectable = config[XS("SulfurCollectable")];
    m_settings::Corn = config[XS("Corn")];
    m_settings::Pumpkin = config[XS("Pumpkin")];
    m_settings::Potato = config[XS("Potato")];
    m_settings::Mushroom = config[XS("Mushroom")];
    m_settings::Stash = config[XS("Stash")];
    m_settings::cupboard = config[XS("cupboard")];
    m_settings::T1Workbench = config[XS("T1Workbench")];
    m_settings::T2Workbench = config[XS("T2Workbench")];
    m_settings::T3Workbench = config[XS("T3Workbench")];
    m_settings::SupplyDrop = config[XS("SupplyDrop")];
    m_settings::BradleyAPC = config[XS("BradleyAPC")];
    m_settings::PatrolHelicopter = config[XS("PatrolHelicopter")];
    m_settings::HackableCrate = config[XS("HackableCrate")];
    m_settings::BasicCrate = config[XS("BasicCrate")];
    m_settings::NormalCrate = config[XS("NormalCrate")];
    m_settings::MilitaryCrate = config[XS("MilitaryCrate")];
    m_settings::EliteCrate = config[XS("EliteCrate")];
    m_settings::LootBarrel = config[XS("LootBarrel")];
    m_settings::AutoTurret = config[XS("AutoTurret")];
    m_settings::FlameTurret = config[XS("FlameTurret")];
    m_settings::BearTrap = config[XS("BearTrap")];
    m_settings::SpikesTrap = config[XS("SpikesTrap")];
    m_settings::LandMine = config[XS("LandMine")];
    m_settings::SamSite = config[XS("SamSite")];
    m_settings::Minicopter = config[XS("Minicopter")];
    m_settings::ScrapHeli = config[XS("ScrapHeli")];
    m_settings::TugBoat = config[XS("TugBoat")];
    m_settings::Rhib = config[XS("Rhib")];
    m_settings::Rowboat = config[XS("Rowboat")];
    m_settings::ShowC4 = config[XS("ShowC4")];
    m_settings::ShowRocket = config[XS("ShowRocket")];
    m_settings::ShowSatchel = config[XS("ShowSatchel")];
    m_settings::ShowExplosiveAmmo = config[XS("ShowExplosiveAmmo")];
    m_settings::ShowAlerts = config[XS("ShowAlerts")];
    m_settings::Radar = config[XS("Radar")];
    m_settings::RadarSize = static_cast<int>(config[XS("RadarSize")]);
    m_settings::Weather = config[XS("Weather")];
    m_settings::AtmosphereContrast = config[XS("AtmosphereContrast")];
    m_settings::NoClouds = config[XS("NoClouds")];
    m_settings::RainbowSky = config[XS("RainbowSky")];
    m_settings::RainbowAmount = static_cast<int>(config[XS("RainbowAmount")]);

    m_settings::helditem = config[XS("HeldItem")];
    m_settings::BoxEsp = config[XS("PlayerBox")];
    m_settings::CornerBox = config[XS("PlayerCornerBox")];
    m_settings::bottomhealthbar = config[XS("BottomHealthBar")];
    m_settings::lefthealthbar = config[XS("LeftHealthBar")];
    m_settings::ShowOutside = config[XS("ShowOutside")];
    m_settings::ShowInside = config[XS("ShowInside")];
    m_settings::DrawWounded = config[XS("DrawWounded")];
    m_settings::DrawSafezone = config[XS("DrawSafezone")];
    m_settings::DrawNPC = config[XS("DrawNPC")];
    m_settings::DrawSleepers = config[XS("DrawSleepers")];
    m_settings::InventoryText = config[XS("InventoryText")];
    m_settings::InventoryIcons = config[XS("InventoryIcons")];
    m_settings::ClothingText = config[XS("ClothingText")];
    m_settings::ClothingIcons = config[XS("ClothingIcons")];
    m_settings::DrawTarget = config[XS("DrawTarget")];
    m_settings::Corpse = config[XS("Corpse")];
    m_settings::BackPack = config[XS("BackPack")];
    m_settings::MaxPlayerDropsDistance = static_cast<int>(config[XS("MaxPlayerDropsDistance")]);
    m_settings::SavePos = config[XS("SavePos")];
    m_settings::SaveHouse = config[XS("SaveHouse")];
    m_settings::AuthorizedPlayers = config[XS("TCAuthorizedPlayers")];
    m_settings::TC_Upkeep = config[XS("TCUpkeep")];
    m_settings::TC_Health = config[XS("TCHealth")];
    m_settings::BradleyCrate = config[XS("BradleyCrate")];
    m_settings::HeliCrate = config[XS("HeliCrate")];
    m_settings::MaxTCDistance = static_cast<int>(config[XS("MaxTCDistance")]);
    m_settings::MaxDeployableDistance = static_cast<int>(config[XS("MaxDeployableDistance")]);
    m_settings::ShotgunTrap = config[XS("ShotgunTrap")];
    m_settings::TurretAuthorizedPlayers = config[XS("TurretAuthorizedPlayers")];
    m_settings::TurretEquippedFlags = config[XS("TurretEquippedFlags")];
    m_settings::TurretOnFlags = config[XS("TurretOnFlags")];
    m_settings::TurretTurningFlag = config[XS("TurretTurningFlag")];
    m_settings::TurretRange = config[XS("TurretRange")];
    m_settings::TurretHealth = config[XS("TurretHealth")];
    m_settings::DroppedItemsChams = config[XS("DroppedItemsChams")];
    m_settings::MaxTurretDistance = static_cast<int>(config[XS("MaxTurretDistance")]);
    m_settings::DroppedOptions[0] = config[XS("DroppedOptions0")];
    m_settings::DroppedOptions[1] = config[XS("DroppedOptions1")];
    m_settings::DroppedOptions[2] = config[XS("DroppedOptions2")];
    m_settings::DroppedOptions[3] = config[XS("DroppedOptions3")];
    m_settings::DroppedOptions[4] = config[XS("DroppedOptions4")];
    m_settings::DroppedOptions[5] = config[XS("DroppedOptions5")];
    m_settings::DroppedOptions[6] = config[XS("DroppedOptions6")];
    m_settings::DroppedOptions[7] = config[XS("DroppedOptions7")];
    m_settings::DroppedOptions[8] = config[XS("DroppedOptions8")];
    m_settings::DroppedOptions[9] = config[XS("DroppedOptions9")];
    m_settings::DroppedOptions[10] = config[XS("DroppedOptions10")];
    m_settings::DroppedOptions[11] = config[XS("DroppedOptions11")];
    m_settings::DroppedOptions[12] = config[XS("DroppedOptions12")];
    m_settings::DroppedOptions[13] = config[XS("DroppedOptions13")];
    m_settings::AdjustNoClipSpeed = config[XS("AdjustNoClipSpeed")];
    m_settings::NameSpoofer = config[XS("NameSpoofer")];
    m_settings::Suicide = config[XS("Suicide")];
    m_settings::BuildingGrade = static_cast<int>(config[XS("BuildingGrade")]);
    m_settings::GestureSpam = config[XS("GestureSpam")];
    m_settings::gesture = static_cast<int>(config[XS("gesture")]);
    m_settings::HammerSpam = config[XS("HammerSpam")];
    m_settings::HammerMaterialType = static_cast<int>(config[XS("HammerMaterialType")]);
    m_settings::SelectedAimbone = static_cast<int>(config[XS("AimbotBone")]);
    m_settings::AutoReloadIcon = config[XS("AutoReloadIcon")];
    m_settings::ManipPoints = static_cast<int>(config[XS("ManipPoints")]);
    m_settings::LOSCheckAmount = static_cast<int>(config[XS("SimulatedPoints")]);
    m_settings::PlayerESPDistance = static_cast<int>(config[XS("PlayerESPDistance")]);
    m_settings::NPCDistance = static_cast<int>(config[XS("NPCDistance")]);
    m_settings::PlayerChams = config[XS("PlayerChams")];
    m_settings::Recycler = config[XS("Recycler")];
    m_settings::horseEsp = config[XS("Horse")];
    m_settings::Bear = config[XS("Bear")];
    m_settings::Boar = config[XS("Boar")];
    m_settings::Stag = config[XS("Stag")];
    m_settings::Wolf = config[XS("Wolf")];
    m_settings::MaxAnimalDistance = static_cast<int>(config[XS("AnimalDistance")]);
    m_settings::BlockServerCommands = config[XS("BlockServerCommands")];
    m_settings::DebugCamera = config[XS("DebugCamera")];
    m_settings::DebugCameraKey = static_cast<RustStructs::KeyCode>(config[XS("DebugCameraKey")]);
    m_settings::SuicideKey = static_cast<RustStructs::KeyCode>(config[XS("SuicideKey")]);
    m_settings::report_player = config[XS("ReportPlayer")];
    m_settings::report_key = static_cast<RustStructs::KeyCode>(config[XS("ReportKey")]);
    m_settings::ChangeCameraMode = config[XS("ChangeCameraMode")];
    m_settings::CameraMode = static_cast<RustStructs::CameraMode>(config[XS("CameraMode")]);
    m_settings::CameraDistance = static_cast<int>(config[XS("CameraDistance")]);
    m_settings::AlwaysHotspot = config[XS("AlwaysHotspot")];
    m_settings::HammerSpamKey = static_cast<RustStructs::KeyCode>(config[XS("HammerSpamKey")]);
    m_settings::AmongusPrefabSpawn = config[XS("SpawnAmongus")];
    m_settings::AmongusKey = static_cast<RustStructs::KeyCode>(config[XS("AmongusKey")]);
    m_settings::HerbertPrefabSpawn = config[XS("SpawnHerbert")];
    m_settings::HerbertKey = static_cast<RustStructs::KeyCode>(config[XS("SpawnHerbertKey")]);
    m_settings::Speedhack = config[XS("Speedhack")];
    m_settings::SpeedhackSpeed = static_cast<int>(config[XS("SpeedhackSpeed")]);
    m_settings::SpeedhackKey = static_cast<RustStructs::KeyCode>(config[XS("SpeedhackKey")]);
    m_settings::SkyColorNight = config[XS("SkyColor")];
    m_settings::Rainbows = config[XS("SkyRainbows")];
    m_settings::NoClouds = config[XS("WeatherNoClouds")];
    m_settings::NoSun = config[XS("WeatherNoSun")];
    m_settings::NoFog = config[XS("WeatherNoFog")];
    m_settings::NoRain = config[XS("WeatherNoRain")];
    m_settings::NoThunder = config[XS("WeatherNoThunder")];
    m_settings::NoWind = config[XS("WeatherNoWind")];
    m_settings::GhostEffect = config[XS("GhostAttackEffect")];

    //// Load TagsVisCheck from JSON
    //if (config.find(XS("TagsVisCheck")) != config.end()) {
    //    m_settings::TagsVisCheck = config[XS("TagsVisCheck")];
    //}


    config.clear();

    const auto string = std::wstring(XS(L"[Serotonin] Loaded Config!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}


void Configs::SaveConfig()
{

    json config;
    /* Bools */
    config[XS("SilentAim")] = m_settings::SilentAim;
    config[XS("RotationAimbot")] = m_settings::RotationAimbot;
    config[XS("VelocityAimbot")] = m_settings::VelocityAimbot;
    config[XS("MeleeAimbot")] = m_settings::MeleeAimbot;
    config[XS("SilentMelee")] = m_settings::SilentMelee;
    config[XS("AimbotNPC")] = m_settings::AimbotNPC;
    config[XS("TargetWounded")] = m_settings::TargetWounded;
    config[XS("Autoshoot")] = m_settings::Autoshoot;
    config[XS("Manipulation")] = m_settings::Manipulation;
    config[XS("BulletTP")] = m_settings::BulletTP;
    config[XS("CacheBulletTP")] = m_settings::CacheBulletTP;
    config[XS("AdvancedChecks")] = m_settings::AdvancedChecks;
    config[XS("BehindWall")] = m_settings::BehindWall;
    config[XS("AlwaysAutoshoot")] = m_settings::AlwaysAutoshoot;
    config[XS("StopPlayer")] = m_settings::StopPlayer;
    config[XS("PierceMaterials")] = m_settings::PierceMaterials;
    config[XS("InstantKill")] = m_settings::InstantKill;
    config[XS("InstantBullet")] = m_settings::InstantBullet;
    config[XS("WaitForInstantHit")] = m_settings::WaitForInstantHit;
    config[XS("AutoReload")] = m_settings::AutoReload;
    config[XS("HitboxOverride")] = m_settings::HitboxOverride;
    config[XS("Crosshair")] = m_settings::Crosshair;
    config[XS("Swastika")] = m_settings::Swastika;
    config[XS("DrawFov")] = m_settings::DrawFov;
    config[XS("Aimline")] = m_settings::AimMarker;
    config[XS("AimMarker")] = m_settings::AimMarker;
    config[XS("Target_Indicator")] = m_settings::Target_Indicator;
    config[XS("BulletTracers")] = m_settings::BulletTracers;
    config[XS("ManipFlags")] = m_settings::ManipFlags;
    config[XS("DrawManipPoints")] = m_settings::DrawManipPoints;
    config[XS("BulletTPFlags")] = m_settings::BulletTPFlags;
    config[XS("ShowBulletTPAngle")] = m_settings::ShowBulletTPAngle;
    config[XS("Thickbullet_Arrows")] = m_settings::Thickbullet_Arrows;
    config[XS("ShowCachedLOS")] = m_settings::ShowCachedLOS;
    config[XS("ShowCachedPoint")] = m_settings::ShowCachedPoint;
    config[XS("SnickerBullet")] = m_settings::SnickerBullet;
    config[XS("nameEsp")] = m_settings::nameEsp;
    config[XS("Skeleton")] = m_settings::Skeleton;
    config[XS("DroppedItems")] = m_settings::DroppedItems;
    config[XS("Flyhack_Indicator")] = m_settings::Flyhack_Indicator;
    config[XS("AntiFlyKick")] = m_settings::AntiFlyKick;
    config[XS("AntiDeathBarrier")] = m_settings::AntiDeathBarrier;
    config[XS("SpiderMan")] = m_settings::SpiderMan;
    config[XS("SmallerLocalRadius")] = m_settings::SmallerLocalRadius;
    config[XS("AdminFlags")] = m_settings::AdminFlags;
    config[XS("InfiniteJump")] = m_settings::InfiniteJump;
    config[XS("OmniSprint")] = m_settings::OmniSprint;
    config[XS("AlwaysSprint")] = m_settings::AlwaysSprint;
    config[XS("NoMovementRestrictions")] = m_settings::NoMovementRestrictions;
    config[XS("IgnoreTrees")] = m_settings::IgnoreTrees;
    config[XS("IgnorePlayers")] = m_settings::IgnorePlayers;
    config[XS("NameSpoofer")] = m_settings::NameSpoofer;
    config[XS("InstantLoot")] = m_settings::InstantLoot;
    config[XS("InstantHeal")] = m_settings::InstantHeal;
    config[XS("FixDebugCamera")] = m_settings::FixDebugCamera;
    config[XS("Spinbot")] = m_settings::Spinbot;
    config[XS("AdminCheat")] = m_settings::AdminCheat;
    config[XS("InstantRevive")] = m_settings::InstantRevive;
    config[XS("KeepTargetAlive")] = m_settings::KeepTargetAlive;
    config[XS("LootBodyThruWall")] = m_settings::LootBodyThruWall;
    config[XS("LootCorpseThruWall")] = m_settings::LootCorpseThruWall;
    config[XS("InteractiveDebug")] = m_settings::InteractiveDebug;
    config[XS("SilentWalk")] = m_settings::SilentWalk;
    config[XS("TeleportMax")] = m_settings::TeleportMax;
    config[XS("Zoom")] = m_settings::Zoom;
    config[XS("PlayerFov")] = m_settings::PlayerFov;
    config[XS("AutoFarmTree")] = m_settings::AutoFarmTree;
    config[XS("AutoFarmOre")] = m_settings::AutoFarmOre;
    config[XS("AutoUpgrade")] = m_settings::AutoUpgrade;
    config[XS("DoorSpammer")] = m_settings::DoorSpammer;
    config[XS("Brightnight")] = m_settings::Brightnight;
    config[XS("BrightAmbient")] = m_settings::BrightAmbient;
    config[XS("Stars")] = m_settings::Stars;
    config[XS("SkyColorDay")] = m_settings::SkyColorDay;
    config[XS("SkyColorNight")] = m_settings::SkyColorNight;
    config[XS("SharpClouds")] = m_settings::SharpClouds;
    config[XS("BrightCave")] = m_settings::BrightCave;
    config[XS("CustomSky")] = m_settings::CustomSky;
    config[XS("TimeChanger")] = m_settings::TimeChanger;
    config[XS("NoAttackRestrictions")] = m_settings::NoAttackRestrictions;
    config[XS("ChangeRecoil")] = m_settings::ChangeRecoil;
    config[XS("NormalThickBullet")] = m_settings::NormalThickBullet;
    config[XS("NormalFastBullet")] = m_settings::NormalFastBullet;
    config[XS("ForceAutomatic")] = m_settings::ForceAutomatic;
    config[XS("NoWeaponBob")] = m_settings::NoWeaponBob;
    config[XS("NoSway")] = m_settings::NoSway;
    config[XS("InstantEoka")] = m_settings::InstantEoka;
    config[XS("RemoveAttackAnimations")] = m_settings::RemoveAttackAnimations;
    config[XS("DisableHitSounds")] = m_settings::DisableHitSounds;
    config[XS("CustomHitSounds")] = m_settings::CustomHitSounds;
    config[XS("LongMelee")] = m_settings::LongMelee;
    config[XS("WeaponSpammer")] = m_settings::WeaponSpammer;
    config[XS("KillEffects")] = m_settings::KillEffects;
    config[XS("WeaponChams")] = m_settings::WeaponChams;
    config[XS("IgnoreArms")] = m_settings::IgnoreArms;
    config[XS("OutlinedText")] = m_settings::OutlinedText;
    config[XS("ShadedText")] = m_settings::ShadedText;
    config[XS("WorldOutlinedText")] = m_settings::WorldOutlinedText;
    config[XS("WorldShadedText")] = m_settings::WorldShadedText;

    ///* KeyBinds */
    config[XS("WeaponSpamKey")] = static_cast<RustStructs::KeyCode>(m_settings::WeaponSpamKey);
    config[XS("RotationKey")] = static_cast<RustStructs::KeyCode>(m_settings::RotationKey);
    config[XS("AimbotKey")] = static_cast<RustStructs::KeyCode>(m_settings::AimbotKey);
    config[XS("AutoshootKey")] = static_cast<RustStructs::KeyCode>(m_settings::AutoshootKey);
    config[XS("ManipKey")] = static_cast<RustStructs::KeyCode>(m_settings::ManipKey);
    config[XS("AdminCheatKey")] = static_cast<RustStructs::KeyCode>(m_settings::AdminCheatKey);
    config[XS("InstantReviveKey")] = static_cast<RustStructs::KeyCode>(m_settings::InstantReviveKey);
    config[XS("KeepAliveKey")] = static_cast<RustStructs::KeyCode>(m_settings::KeepAliveKey);
    config[XS("LootBodyThruWallKey")] = static_cast<RustStructs::KeyCode>(m_settings::LootBodyThruWallKey);
    config[XS("LootCorpseThruWallKey")] = static_cast<RustStructs::KeyCode>(m_settings::LootCorpseThruWallKey);
    config[XS("InteractiveKey")] = static_cast<RustStructs::KeyCode>(m_settings::InteractiveKey);
    config[XS("SilentWalkKey")] = static_cast<RustStructs::KeyCode>(m_settings::SilentWalkKey);
    config[XS("TeleportMaxKey")] = static_cast<RustStructs::KeyCode>(m_settings::TeleportMaxKey);
    config[XS("ZoomKey")] = static_cast<RustStructs::KeyCode>(m_settings::ZoomKey);


    ///* Floats / Ints */
    config[XS("WeaponSpamDelay")] = static_cast<int>(m_settings::WeaponSpamDelay);
    config[XS("SilentSpread")] = static_cast<int>(m_settings::SilentSpread);
    config[XS("NormalThickBulletThickness")] = static_cast<int>(m_settings::NormalThickBulletThickness);
    config[XS("recoilPercent")] = static_cast<int>(m_settings::recoilPercent);
    config[XS("GameTime")] = static_cast<int>(m_settings::GameTime);
    config[XS("PlayerFovAmount")] = static_cast<int>(m_settings::PlayerFovAmount);
    config[XS("AimbotAccuracy")] = static_cast<int>(m_settings::AimbotAccuracy);
    config[XS("AimbotFOV")] = static_cast<int>(m_settings::AimbotFOV);
    config[XS("SwastikaSize")] = static_cast<int>(m_settings::SwastikaSize);
    config[XS("MaxOreDistance")] = static_cast<int>(m_settings::MaxOreDistance);
    config[XS("MaxCollectableDistance")] = static_cast<int>(m_settings::MaxCollectableDistance);
    config[XS("MaxFoodDistance")] = static_cast<int>(m_settings::MaxFoodDistance);
    config[XS("MaxCrateDistance")] = static_cast<int>(m_settings::MaxCrateDistance);
    config[XS("MaxSupplyDropDistance")] = static_cast<int>(m_settings::MaxSupplyDropDistance);
    config[XS("MaxDroppedDistance")] = static_cast<int>(m_settings::MaxDroppedDistance);
    config[XS("MaxTrapsDistance")] = static_cast<int>(m_settings::MaxTrapsDistance);
    config[XS("MaxAPCDistance")] = static_cast<int>(m_settings::MaxAPCDistance);
    config[XS("MaxVehicleDistance")] = static_cast<int>(m_settings::MaxVehicleDistance);
    config[XS("MaxExplosionDistance")] = static_cast<int>(m_settings::MaxExplosionDistance);
    config[XS("AuthorizedPlayersDistance")] = static_cast<int>(m_settings::AuthorizedPlayersDistance);
    config[XS("MaxRaidTimer")] = static_cast<int>(m_settings::MaxRaidTimer);
    config[XS("ZoomAmount")] = static_cast<int>(m_settings::ZoomAmount);

    ///* ComboBox shit */
    config[XS("SelectedBoxESP")] = static_cast<int>(m_settings::SelectedBoxESP);
    config[XS("HeldItemType")] = static_cast<int>(m_settings::HeldItemType);
    config[XS("SelectedHealthBar")] = static_cast<int>(m_settings::SelectedHealthBar);
    config[XS("SelectedHotbar")] = static_cast<int>(m_settings::SelectedHotbar);
    config[XS("SelectedClothing")] = static_cast<int>(m_settings::SelectedClothing);
    config[XS("SelectedOutsideType")] = static_cast<int>(m_settings::SelectedOutsideType);
    config[XS("VisCheckType")] = static_cast<int>(m_settings::VisCheckType);
    config[XS("HitMaterial")] = static_cast<int>(m_settings::HitMaterial);
    config[XS("BulletTPIntensity")] = static_cast<int>(m_settings::BulletTPIntensity);
    config[XS("ManipMode")] = static_cast<int>(m_settings::ManipMode);
    config[XS("SelectedHitbox")] = static_cast<int>(m_settings::SelectedHitbox);
    //  config[XS("SelectedAimbone")] = static_cast<int>(m_settings::SelectedAimbone);
    //  config[XS("BuildingGrade")] = static_cast<int>(m_settings::BuildingGrade);

      ///* MultiBox shit */

    config[XS("RaidOptions0")] = m_settings::RaidOptions[0];
    config[XS("RaidOptions1")] = m_settings::RaidOptions[1];
    config[XS("RaidOptions2")] = m_settings::RaidOptions[2];
    config[XS("RaidOptions3")] = m_settings::RaidOptions[3];
    config[XS("RaidOptions4")] = m_settings::RaidOptions[4];
    config[XS("RaidOptions5")] = m_settings::RaidOptions[5];
    config[XS("RaidOptions6")] = m_settings::RaidOptions[6];
    config[XS("RaidOptions7")] = m_settings::RaidOptions[7];

    config[XS("TurretOptions0")] = m_settings::TurretOptions[0];
    config[XS("TurretOptions1")] = m_settings::TurretOptions[1];
    config[XS("TurretOptions2")] = m_settings::TurretOptions[2];
    config[XS("TurretOptions3")] = m_settings::TurretOptions[3];
    config[XS("TurretOptions4")] = m_settings::TurretOptions[4];
    config[XS("TurretOptions5")] = m_settings::TurretOptions[5];
    config[XS("TurretOptions6")] = m_settings::TurretOptions[6];
    config[XS("TurretOptions7")] = m_settings::TurretOptions[7];
    config[XS("TurretOptions8")] = m_settings::TurretOptions[8];

    config[XS("VehicleOptions0")] = m_settings::VehicleOptions[0];
    config[XS("VehicleOptions1")] = m_settings::VehicleOptions[1];
    config[XS("VehicleOptions2")] = m_settings::VehicleOptions[2];
    config[XS("VehicleOptions3")] = m_settings::VehicleOptions[3];
    config[XS("VehicleOptions4")] = m_settings::VehicleOptions[4];
    config[XS("VehicleOptions5")] = m_settings::VehicleOptions[5];
    config[XS("VehicleOptions6")] = m_settings::VehicleOptions[6];
    config[XS("VehicleOptions7")] = m_settings::VehicleOptions[7];
    config[XS("VehicleOptions8")] = m_settings::VehicleOptions[8];

    config[XS("TrapsOptions0")] = m_settings::TrapsOptions[0];
    config[XS("TrapsOptions1")] = m_settings::TrapsOptions[1];
    config[XS("TrapsOptions2")] = m_settings::TrapsOptions[2];
    config[XS("TrapsOptions3")] = m_settings::TrapsOptions[3];
    config[XS("TrapsOptions4")] = m_settings::TrapsOptions[4];
    config[XS("TrapsOptions5")] = m_settings::TrapsOptions[5];
    config[XS("TrapsOptions6")] = m_settings::TrapsOptions[6];
    config[XS("TrapsOptions7")] = m_settings::TrapsOptions[7];
    config[XS("TrapsOptions8")] = m_settings::TrapsOptions[8];

    config[XS("CupboardOptions0")] = m_settings::CupboardOptions[0];
    config[XS("CupboardOptions1")] = m_settings::CupboardOptions[1];
    config[XS("CupboardOptions2")] = m_settings::CupboardOptions[2];
    config[XS("CupboardOptions3")] = m_settings::CupboardOptions[3];
    config[XS("CupboardOptions4")] = m_settings::CupboardOptions[4];
    config[XS("CupboardOptions5")] = m_settings::CupboardOptions[5];
    config[XS("CupboardOptions6")] = m_settings::CupboardOptions[6];

    config[XS("CrateOptions0")] = m_settings::CrateOptions[0];
    config[XS("CrateOptions1")] = m_settings::CrateOptions[1];
    config[XS("CrateOptions2")] = m_settings::CrateOptions[2];
    config[XS("CrateOptions3")] = m_settings::CrateOptions[3];
    config[XS("CrateOptions4")] = m_settings::CrateOptions[4];
    config[XS("CrateOptions5")] = m_settings::CrateOptions[5];
    config[XS("CrateOptions6")] = m_settings::CrateOptions[6];
    config[XS("CrateOptions7")] = m_settings::CrateOptions[7];
    config[XS("CrateOptions8")] = m_settings::CrateOptions[8];
    config[XS("CrateOptions9")] = m_settings::CrateOptions[9];

    config[XS("OreOptions0")] = m_settings::OreOptions[0];
    config[XS("OreOptions1")] = m_settings::OreOptions[1];
    config[XS("OreOptions2")] = m_settings::OreOptions[2];
    config[XS("OreOptions3")] = m_settings::OreOptions[3];
    config[XS("OreOptions4")] = m_settings::OreOptions[4];
    config[XS("OreOptions5")] = m_settings::OreOptions[5];
    config[XS("OreOptions6")] = m_settings::OreOptions[6];
    config[XS("OreOptions7")] = m_settings::OreOptions[7];

    config[XS("CollectableOptions0")] = m_settings::CollectableOpions[0];
    config[XS("CollectableOptions1")] = m_settings::CollectableOpions[1];
    config[XS("CollectableOptions2")] = m_settings::CollectableOpions[2];
    config[XS("CollectableOptions3")] = m_settings::CollectableOpions[3];
    config[XS("CollectableOptions4")] = m_settings::CollectableOpions[4];
    config[XS("CollectableOptions5")] = m_settings::CollectableOpions[5];
    config[XS("CollectableOptions6")] = m_settings::CollectableOpions[6];
    config[XS("CollectableOptions7")] = m_settings::CollectableOpions[7];
    config[XS("CollectableOptions8")] = m_settings::CollectableOpions[8];

    config[XS("FoodOptions0")] = m_settings::FoodOptions[0];
    config[XS("FoodOptions1")] = m_settings::FoodOptions[1];
    config[XS("FoodOptions2")] = m_settings::FoodOptions[2];
    config[XS("FoodOptions3")] = m_settings::FoodOptions[3];
    config[XS("FoodOptions4")] = m_settings::FoodOptions[4];
    config[XS("FoodOptions5")] = m_settings::FoodOptions[5];
    config[XS("FoodOptions6")] = m_settings::FoodOptions[6];
    config[XS("FoodOptions7")] = m_settings::FoodOptions[7];
    config[XS("FoodOptions8")] = m_settings::FoodOptions[8];

    config[XS("DeployableOptions0")] = m_settings::DeployableOptions[0];
    config[XS("DeployableOptions1")] = m_settings::DeployableOptions[1];
    config[XS("DeployableOptions2")] = m_settings::DeployableOptions[2];
    config[XS("DeployableOptions3")] = m_settings::DeployableOptions[3];
    config[XS("DeployableOptions4")] = m_settings::DeployableOptions[4];
    config[XS("DeployableOptions5")] = m_settings::DeployableOptions[5];
    config[XS("DeployableOptions6")] = m_settings::DeployableOptions[6];
    config[XS("DeployableOptions7")] = m_settings::DeployableOptions[7];
    config[XS("DeployableOptions8")] = m_settings::DeployableOptions[8];
    config[XS("DeployableOptions9")] = m_settings::DeployableOptions[9];

    config[XS("StoneOre")] = m_settings::StoneOre;
    config[XS("MetalOre")] = m_settings::MetalOre;
    config[XS("SulfurOre")] = m_settings::SulfurOre;
    config[XS("Hemp")] = m_settings::Hemp;
    config[XS("DieselBarrel")] = m_settings::DieselBarrel;
    config[XS("StoneCollectable")] = m_settings::StoneCollectable;
    config[XS("MetalCollectable")] = m_settings::MetalCollectable;
    config[XS("SulfurCollectable")] = m_settings::SulfurCollectable;
    config[XS("Corn")] = m_settings::Corn;
    config[XS("Pumpkin")] = m_settings::Pumpkin;
    config[XS("Potato")] = m_settings::Potato;
    config[XS("Mushroom")] = m_settings::Mushroom;
    config[XS("Stash")] = m_settings::Stash;
    config[XS("cupboard")] = m_settings::cupboard;
    config[XS("T1Workbench")] = m_settings::T1Workbench;
    config[XS("T2Workbench")] = m_settings::T2Workbench;
    config[XS("T3Workbench")] = m_settings::T3Workbench;
    config[XS("SupplyDrop")] = m_settings::SupplyDrop;
    config[XS("BradleyAPC")] = m_settings::BradleyAPC;
    config[XS("PatrolHelicopter")] = m_settings::PatrolHelicopter;
    config[XS("HackableCrate")] = m_settings::HackableCrate;
    config[XS("BasicCrate")] = m_settings::BasicCrate;
    config[XS("NormalCrate")] = m_settings::NormalCrate;
    config[XS("MilitaryCrate")] = m_settings::MilitaryCrate;
    config[XS("EliteCrate")] = m_settings::EliteCrate;
    config[XS("LootBarrel")] = m_settings::LootBarrel;
    config[XS("AutoTurret")] = m_settings::AutoTurret;
    config[XS("FlameTurret")] = m_settings::FlameTurret;
    config[XS("BearTrap")] = m_settings::BearTrap;
    config[XS("SpikesTrap")] = m_settings::SpikesTrap;
    config[XS("LandMine")] = m_settings::LandMine;
    config[XS("SamSite")] = m_settings::SamSite;
    config[XS("Minicopter")] = m_settings::Minicopter;
    config[XS("ScrapHeli")] = m_settings::ScrapHeli;
    config[XS("TugBoat")] = m_settings::TugBoat;
    config[XS("Rhib")] = m_settings::Rhib;
    config[XS("Rowboat")] = m_settings::Rowboat;
    config[XS("ShowC4")] = m_settings::ShowC4;
    config[XS("ShowRocket")] = m_settings::ShowRocket;
    config[XS("ShowSatchel")] = m_settings::ShowSatchel;
    config[XS("ShowExplosiveAmmo")] = m_settings::ShowExplosiveAmmo;
    config[XS("ShowAlerts")] = m_settings::ShowAlerts;
    config[XS("Radar")] = m_settings::Radar;
    config[XS("RadarSize")] = static_cast<int>(m_settings::RadarSize);
    config[XS("Weather")] = m_settings::Weather;
    config[XS("AtmosphereContrast")] = m_settings::AtmosphereContrast;
    config[XS("NoClouds")] = m_settings::NoClouds;
    config[XS("RainbowSky")] = m_settings::RainbowSky;
    config[XS("RainbowAmount")] = static_cast<int>(m_settings::RainbowAmount);

    config[XS("HeldItem")] = m_settings::helditem;
    config[XS("PlayerBox")] = m_settings::BoxEsp;
    config[XS("PlayerCornerBox")] = m_settings::CornerBox;
    config[XS("BottomHealthBar")] = m_settings::bottomhealthbar;
    config[XS("LeftHealthBar")] = m_settings::lefthealthbar;
    config[XS("ShowOutside")] = m_settings::ShowOutside;
    config[XS("ShowInside")] = m_settings::ShowInside;
    config[XS("DrawWounded")] = m_settings::DrawWounded;
    config[XS("DrawSafezone")] = m_settings::DrawSafezone;
    config[XS("DrawNPC")] = m_settings::DrawNPC;
    config[XS("DrawSleepers")] = m_settings::DrawSleepers;
    config[XS("InventoryText")] = m_settings::InventoryText;
    config[XS("InventoryIcons")] = m_settings::InventoryIcons;
    config[XS("ClothingText")] = m_settings::ClothingText;
    config[XS("ClothingIcons")] = m_settings::ClothingIcons;
    config[XS("DrawTarget")] = m_settings::DrawTarget;

    config[XS("Corpse")] = m_settings::Corpse;
    config[XS("BackPack")] = m_settings::BackPack;
    config[XS("MaxPlayerDropsDistance")] = static_cast<int>(m_settings::MaxPlayerDropsDistance);
    config[XS("SavePos")] = m_settings::SavePos;
    config[XS("SaveHouse")] = m_settings::SaveHouse;

    config[XS("TCAuthorizedPlayers")] = m_settings::AuthorizedPlayers;
    config[XS("TCUpkeep")] = m_settings::TC_Upkeep;
    config[XS("TCHealth")] = m_settings::TC_Health;
    config[XS("BradleyCrate")] = m_settings::BradleyCrate;
    config[XS("HeliCrate")] = m_settings::HeliCrate;
    config[XS("MaxTCDistance")] = static_cast<int>(m_settings::MaxTCDistance);
    config[XS("MaxDeployableDistance")] = static_cast<int>(m_settings::MaxDeployableDistance);

    config[XS("ShotgunTrap")] = m_settings::ShotgunTrap;
    config[XS("TurretAuthorizedPlayers")] = m_settings::TurretAuthorizedPlayers;
    config[XS("TurretEquippedFlags")] = m_settings::TurretEquippedFlags;
    config[XS("TurretOnFlags")] = m_settings::TurretOnFlags;
    config[XS("TurretTurningFlag")] = m_settings::TurretTurningFlag;
    config[XS("TurretRange")] = m_settings::TurretRange;
    config[XS("TurretHealth")] = m_settings::TurretHealth;
    config[XS("DroppedItemsChams")] = m_settings::DroppedItemsChams;

    config[XS("MaxTurretDistance")] = static_cast<int>(m_settings::MaxTurretDistance);

    config[XS("DroppedOptions0")] = m_settings::DroppedOptions[0];
    config[XS("DroppedOptions1")] = m_settings::DroppedOptions[1];
    config[XS("DroppedOptions2")] = m_settings::DroppedOptions[2];
    config[XS("DroppedOptions3")] = m_settings::DroppedOptions[3];
    config[XS("DroppedOptions4")] = m_settings::DroppedOptions[4];
    config[XS("DroppedOptions5")] = m_settings::DroppedOptions[5];
    config[XS("DroppedOptions6")] = m_settings::DroppedOptions[6];
    config[XS("DroppedOptions7")] = m_settings::DroppedOptions[7];
    config[XS("DroppedOptions8")] = m_settings::DroppedOptions[8];
    config[XS("DroppedOptions9")] = m_settings::DroppedOptions[9];
    config[XS("DroppedOptions10")] = m_settings::DroppedOptions[10];
    config[XS("DroppedOptions11")] = m_settings::DroppedOptions[11];
    config[XS("DroppedOptions12")] = m_settings::DroppedOptions[12];
    config[XS("DroppedOptions13")] = m_settings::DroppedOptions[13];
    config[XS("AdjustNoClipSpeed")] = m_settings::AdjustNoClipSpeed;
    config[XS("NameSpoofer")] = m_settings::NameSpoofer;
    config[XS("Suicide")] = m_settings::Suicide;
    config[XS("BuildingGrade")] = static_cast<int>(m_settings::BuildingGrade);
    config[XS("GestureSpam")] = m_settings::GestureSpam;
    config[XS("gesture")] = static_cast<int>(m_settings::gesture);
    config[XS("HammerSpam")] = m_settings::HammerSpam;
    config[XS("HammerMaterialType")] = static_cast<int>(m_settings::HammerMaterialType);
    config[XS("AimbotBone")] = static_cast<int>(m_settings::SelectedAimbone);
    config[XS("AutoReloadIcon")] = m_settings::AutoReloadIcon;
    config[XS("ManipPoints")] = static_cast<int>(m_settings::ManipPoints);
    config[XS("SimulatedPoints")] = static_cast<int>(m_settings::LOSCheckAmount);
    config[XS("PlayerESPDistance")] = static_cast<int>(m_settings::PlayerESPDistance);
    config[XS("NPCDistance")] = static_cast<int>(m_settings::NPCDistance);
    config[XS("PlayerChams")] = m_settings::PlayerChams;
    config[XS("Recycler")] = m_settings::Recycler;
    config[XS("Horse")] = m_settings::horseEsp;
    config[XS("Bear")] = m_settings::Bear;
    config[XS("Boar")] = m_settings::Boar;
    config[XS("Stag")] = m_settings::Stag;
    config[XS("Wolf")] = m_settings::Wolf;
    config[XS("AnimalDistance")] = static_cast<int>(m_settings::MaxAnimalDistance);
    config[XS("BlockServerCommands")] = m_settings::BlockServerCommands;
    config[XS("DebugCamera")] = m_settings::DebugCamera;
    config[XS("DebugCameraKey")] = static_cast<RustStructs::KeyCode>(m_settings::DebugCameraKey);
    config[XS("SuicideKey")] = static_cast<RustStructs::KeyCode>(m_settings::SuicideKey);
    config[XS("ReportPlayer")] = m_settings::report_player;
    config[XS("ReportKey")] = static_cast<RustStructs::KeyCode>(m_settings::report_key);
    config[XS("ChangeCameraMode")] = m_settings::ChangeCameraMode;
    config[XS("CameraMode")] = static_cast<RustStructs::CameraMode>(m_settings::CameraMode);
    config[XS("CameraDistance")] = static_cast<int>(m_settings::CameraDistance);
    config[XS("AlwaysHotspot")] = m_settings::AlwaysHotspot;
    config[XS("HammerSpamKey")] = static_cast<RustStructs::KeyCode>(m_settings::HammerSpamKey);
    config[XS("SpawnAmongus")] = m_settings::AmongusPrefabSpawn;
    config[XS("AmongusKey")] = static_cast<RustStructs::KeyCode>(m_settings::AmongusKey);
    config[XS("SpawnHerbert")] = m_settings::HerbertPrefabSpawn;
    config[XS("SpawnHerbertKey")] = static_cast<RustStructs::KeyCode>(m_settings::HerbertKey);
    config[XS("Speedhack")] = m_settings::Speedhack;
    config[XS("SpeedhackSpeed")] = static_cast<int>(m_settings::SpeedhackSpeed);
    config[XS("SpeedhackKey")] = static_cast<RustStructs::KeyCode>(m_settings::SpeedhackKey);
    config[XS("SkyColor")] = m_settings::SkyColorNight;
    config[XS("SkyRainbows")] = m_settings::Rainbows;
    config[XS("WeatherNoClouds")] = m_settings::NoClouds;
    config[XS("WeatherNoSun")] = m_settings::NoSun;
    config[XS("WeatherNoFog")] = m_settings::NoFog;
    config[XS("WeatherNoRain")] = m_settings::NoRain;
    config[XS("WeatherNoThunder")] = m_settings::NoThunder;
    config[XS("WeatherNoWind")] = m_settings::NoWind;
    config[XS("GhostAttackEffect")] = m_settings::GhostEffect;
    
    std::string jsonString = config.dump(4);

    std::string file_name;
    if (m_settings::SelectedConfig == 0)
    {
        file_name = XS("Legit.json");
    }
    else if (m_settings::SelectedConfig == 1)
    {
        file_name = XS("Rage.json");
    }
    else if (m_settings::SelectedConfig == 2)
    {
        file_name = XS("Config1.json");
    }
    else if (m_settings::SelectedConfig == 3)
    {
        file_name = XS("Config2.json");
    }
    else if (m_settings::SelectedConfig == 4)
    {
        file_name = XS("Config3.json");
    }

    FILE* file = LI_FN(fopen)(file_name.c_str(), XS("w"));
    if (file == nullptr) {
        return;
    }

    size_t dataSize = jsonString.size();
    size_t bytesWritten = LI_FN(fwrite)(jsonString.c_str(), 1, dataSize, file);

    if (bytesWritten != dataSize) {
        LI_FN(fclose)(file);
        return;
    }

    LI_FN(fclose)(file);
    config.clear();
    const auto string = std::wstring(XS(L"[Serotonin] Saved Config!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());

}

void Buttons::ClearRaidCache() {

    LogSystem::loggedExplosions.clear();

    const auto string = std::wstring(XS(L"[Serotonin] Cleared Raid Cache!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}

void Buttons::ClearLOSPoints() {

    Features().GeneratedPoints = false;

    const auto string = std::wstring(XS(L"[Serotonin] Reset LOS Points!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}

void Buttons::LoadLegitCheat() {
    m_settings::LoadLegit = true;
    m_settings::LoadRage = false;
    m_settings::SelectedOption = true;

    const auto string = std::wstring(XS(L"[Serotonin] Loaded Legit Menu!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}

void Buttons::LoadRageCheat() {
    m_settings::LoadLegit = false; 
    m_settings::LoadRage = true; 
    m_settings::SelectedOption = true; 

    const auto string = std::wstring(XS(L"[Serotonin] Loaded Rage Menu!"));
    notifcations::object.push(string.c_str(), UnityEngine::Time::get_time());
}