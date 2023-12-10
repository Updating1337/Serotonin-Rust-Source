#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

void Hooks::ProcessAttack(AssemblyCSharp::BaseMelee* _This, AssemblyCSharp::HitTest* hit)
{
	if (!InGame)
		return Hooks::ProcessAttackhk.get_original< decltype(&ProcessAttack)>()(_This, hit);

	if (!_This || !hit)
		return Hooks::ProcessAttackhk.get_original< decltype(&ProcessAttack)>()(_This, hit);

	if (!IsAddressValid(Features().LocalPlayer))
		return Hooks::ProcessAttackhk.get_original< decltype(&ProcessAttack)>()(_This, hit);

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return Hooks::ProcessAttackhk.get_original< decltype(&ProcessAttack)>()(_This, hit);

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected())
	{
		return Hooks::ProcessAttackhk.get_original< decltype(&ProcessAttack)>()(_This, hit);
	}

	//Always Hotspot
	if (m_settings::AlwaysHotspot)
	{
		auto Entity = hit->HitEntity();

		if (!m_settings::AlwaysHotspot || !Entity)
			return _This->ProcessAttack(hit);

		if (IsAddressValid(Entity)) {
			f_object ore_hot_spot = f_object::get_closest_object(Features().LocalPlayer->get_bone_transform(47)->get_position(),
				XS(""),
				Vector3(),
				Vector3(),
				Vector3(),
				true,
				XS("OreHotSpot"));
			if (ore_hot_spot.valid) {
				Vector3 local = Features().LocalPlayer->ClosestPoint(ore_hot_spot.position);
				if (local.get_3d_dist(ore_hot_spot.position) <= 2.f) {
					auto hit_entity = (AssemblyCSharp::BaseEntity*)ore_hot_spot.entity;

					auto trans = hit_entity->get_transform();
					if (!IsAddressValid(trans))
						return;

					hit->HitTransform() = trans;
					hit->HitPoint() = trans->InverseTransformPoint(trans->get_position());
					hit->HitMaterial() = CIl2Cpp::il2cpp_string_new(XS("MetalOre"));
				}
			}	
			f_object tree_entity = f_object::get_closest_object(Features().LocalPlayer->get_bone_transform(48)->get_position(),
				XS(""),
				Vector3(),
				Vector3(),
				Vector3(),
				true,
				XS("TreeEntity"));
			if (tree_entity.valid) {
				Vector3 local = Features().LocalPlayer->ClosestPoint(tree_entity.position);
				if (local.get_3d_dist(tree_entity.position) <= 2.f) {
					{
						f_object tree_hot_spot = f_object::get_closest_object(Features().LocalPlayer->get_bone_transform(47)->get_position(),
							XS(""),
							Vector3(),
							Vector3(),
							Vector3(),
							true,
							XS("TreeMarker"));
						if (tree_hot_spot.valid) {
							Vector3 locala = Features().LocalPlayer->ClosestPoint(tree_hot_spot.position);
							if (locala.get_3d_dist(tree_hot_spot.position) <= 2.f) {
								auto hit_entity = (AssemblyCSharp::BaseEntity*)tree_hot_spot.entity;

								auto trans = hit_entity->get_transform();
								if (!IsAddressValid(trans))
									return;

								hit->HitTransform() = trans;
								hit->HitPoint() = trans->InverseTransformPoint(trans->get_position());
								hit->HitMaterial() = CIl2Cpp::il2cpp_string_new(XS("Wood"));
							}
						}
					}
				}
			}

		}

	}

	return _This->ProcessAttack(hit);
}