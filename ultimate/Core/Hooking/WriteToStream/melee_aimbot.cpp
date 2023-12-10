//#pragma once
//
//#include "../Hooks.hpp"
//
//#include "Prediction.hpp"
//#include "../../Features/Features/Features.hpp"
//
//
//void projectile_shoot_original(AssemblyCSharp::BasePlayer* ent, FPSystem::String* str, ProtoBuf::ProjectileShoot* projectile_shoot, uint64_t method_info)
//{
//    init_type_info((uint64_t)projectile_shoot_class);
//    o_projectile_shoot.cast<void(*)(AssemblyCSharp::BasePlayer*, void*, FPSystem::String*, ProtoBuf::ProjectileShoot*, uint64_t)>()(ent, 0, str, projectile_shoot, method_info);
//}
//
//void Hooks::projectile_shoot(AssemblyCSharp::BasePlayer* ent, void* unused, FPSystem::String* str, ProtoBuf::ProjectileShoot* projectile_shoot, uint64_t method_info)
//{
//	static bool first_shot = true;
//	if (first_shot)
//	{
//		first_shot = false;
//		return projectile_shoot_original(ent, str, projectile_shoot, method_info);
//	}
//
//
//
//	auto camera = UnityEngine::Camera::get_main();
//	if (!IsAddressValid(camera))
//		return projectile_shoot_original(ent, str, projectile_shoot, method_info);
//
//	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
//	if (!IsAddressValid(AimbotTarget.m_player))
//		return projectile_shoot_original(ent, str, projectile_shoot, method_info);
//
//	if (Features().BulletTPAngle.IsZero())
//	{
//		Features().BulletTPAngle = AimbotTarget.m_position;
//	}
//
//	auto serverside_projectiles = projectile_shoot->projectiles();
//	auto held_entity = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
//	if (!held_entity)
//		return projectile_shoot_original(ent, str, projectile_shoot, method_info);
//
//	memory::address_t clientside_projectiles = held_entity->createdProjectiles()->_items;
//	uint64_t buffer = (uint64_t)serverside_projectiles->_items;
//	uint32_t size = serverside_projectiles->_size;
//	if (!buffer || size == 0)
//		return projectile_shoot_original(ent, str, projectile_shoot, method_info);
//
//	Projectile* projectile = clientside_projectiles.offset(0x20).get().cast<Projectile*>();
//	if (!IsAddressValid(projectile))
//		return projectile_shoot_original(ent, str, projectile_shoot, method_info);
//
//	const uint64_t typeHash = Hash(str->str, true);
//	bool flag = typeHash == HASH(L"CLProject");
//
//	UnityEngine::Transform* transform = projectile->get_transform();
//
//	Vector3 StartPosition;
//	for (int i = 0; i < size; ++i)
//	{
//		ProjectileShoot_Shoot* server_projectile = *(ProjectileShoot_Shoot**)(buffer + 0x20 + (0x8 * i));;
//		if (!IsAddressValid(server_projectile))
//			continue;
//
//
//		Projectile* client_projectile = clientside_projectiles.offset(0x20 + (0x8 * i)).get().cast<Projectile*>();
//		if (!IsAddressValid(client_projectile))
//			continue;
//
//
//		StartPosition = server_projectile->startPos();
//
//		StartPosition += Vector3(5.f, 0.f, 0.f);
//
//		AssemblyCSharp::ItemModProjectile* itemModProjectile = held_entity->GetOwnerItemDefinition()->GetComponent<AssemblyCSharp::ItemModProjectile>((FPSystem::Type*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS(""), XS("ItemModProjectile"))));
//
//
//		Vector3 aim_angle = GetAimDirectionToTarget(Features().LocalPlayer, Features().BaseProjectile, Features().BulletTPAngle, AimbotTarget.m_velocity, itemModProjectile, StartPosition) - StartPosition;
//		Vector3 m_aim_angle = (aim_angle).Normalized() * server_projectile->startVel().Length();
//
//
//
//		server_projectile->startVel() = m_aim_angle;
//		client_projectile->initialVelocity() = m_aim_angle;
//		client_projectile->currentVelocity() = m_aim_angle;
//		client_projectile->currentPosition() = StartPosition;
//		server_projectile->startPos() = StartPosition;
//
//		auto g = client_projectile->get_gameObject();
//		if (!IsAddressValid(g))
//			continue;
//
//
//		auto t = g->get_transform();
//		if (!IsAddressValid(t))
//			continue;
//
//
//		t->set_position(StartPosition);
//	}
//
//	projectile_shoot_original(ent, str, projectile_shoot, method_info);
//	held_entity->createdProjectiles()->Clear();
//}