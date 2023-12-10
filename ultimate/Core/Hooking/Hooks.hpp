#pragma once
#include "Hooker.hpp"

#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"

void projectile_shoot_original(AssemblyCSharp::BasePlayer* ent, FPSystem::String* str, ProtoBuf::ProjectileShoot* projectile_shoot, uint64_t method_info);

inline Il2CppClass* projectile_shoot_class;
inline memory::address_t o_projectile_shoot;

static inline Il2CppType* init_type_info(uint64_t address)
{
	static uint64_t method = 0;
	if (!method)
	{
		memory::address_t type_info_reference = CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS(""), XS("Client")), HASH("OnNetworkMessage"), 1);
		auto method_start = type_info_reference.get();
		auto call_loc = method_start.offset(0x24);
		auto init_func = call_loc.jmp();
		method = init_func.cast<uint64_t>();
	}
	return reinterpret_cast<Il2CppType * (*)(uint64_t)>(method)(address);
}


class Hooks {
public:

	static auto Instance() -> Hooks*
	{
		Hooks obj;
		return &obj;
	}

public:
	void BeginHooks();

private:
	HOOK(void, OnGUI, (AssemblyCSharp::ExplosionsFPS* _This))
	HOOK(void, Update_, (AssemblyCSharp::MainMenuSystem* _This))
	HOOK(void, ClientInput, (AssemblyCSharp::BasePlayer* a1, AssemblyCSharp::InputState* a2))
	HOOK(void, ProjectileShootHook, (ProtoBuf::ProjectileShoot* _This, ProtoBuf::Stream* Stream))
	HOOK(void, DoAttack, (AssemblyCSharp::BaseProjectile* _This))
	HOOK(void, ProjectileUpdate, (AssemblyCSharp::Projectile* _This))
	HOOK(void, PPA_WriteToStream, (ProtoBuf::PlayerProjectileAttack* _This, ProtoBuf::Stream* Stream))
	HOOK(void, PlayerWalkMovement, (AssemblyCSharp::PlayerWalkMovement* _This, AssemblyCSharp::InputState* _State, AssemblyCSharp::ModelState* _ModelState))
	HOOK(void, TryToMove, (AssemblyCSharp::ItemIcon* _This))
	HOOK(void, SkyUpdate, (AssemblyCSharp::TOD_Camera* _This))
	HOOK(void, SteamPlatformUpdate, (RustPlatformSteam::SteamPlatform* _This))
	HOOK(void, OnAttacked, (AssemblyCSharp::BasePlayer* instance, AssemblyCSharp::HitInfo* hitinfo))
	HOOK(void, LateUpdate, (AssemblyCSharp::TOD_Sky* TOD_Sky))
	HOOK(void, BlockSprint, (AssemblyCSharp::BasePlayer* instance, float duration))
	HOOK(void, OnNetworkMessage, (AssemblyCSharp::Client* _This, Network::Message* packet))
	HOOK(void, OnInput, (AssemblyCSharp::BaseMelee* _This))	
	HOOK(void, DoAttackBow, (AssemblyCSharp::BowWeapon* _This))
	HOOK(void, FlintStrikeWeaponDoAttack, (AssemblyCSharp::FlintStrikeWeapon* _This))
	HOOK(void, DoAttackMelee, (AssemblyCSharp::BaseMelee* _This))
	HOOK(void, UpdatePlayerModel, (AssemblyCSharp::Parachute* _This, AssemblyCSharp::BasePlayer* player))
	HOOK(bool, IsAiming, (AssemblyCSharp::BowWeapon* _This))
	HOOK(void, projectile_shoot, (AssemblyCSharp::BasePlayer* ent, void* unused, FPSystem::String* strstr, ProtoBuf::ProjectileShoot* projectile_shoot, uint64_t method_info))
	HOOK(void, ProcessAttack, (AssemblyCSharp::BaseMelee* _This, AssemblyCSharp::HitTest* hit))
	HOOK(float, GetRandomVelocity, (AssemblyCSharp::ItemModProjectile* _This))
};