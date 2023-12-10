#include "AssemblyCSharp.hpp"
#include "../../Features/Visuals/Visuals.hpp"

namespace AssemblyCSharp {

	bool BaseCombatEntity::IsDead()
	{
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsDead"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	bool BaseCombatEntity::IsAlive()
	{
		if (!IsAddressValid(this)) return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsAlive"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	Vector3 HitTest::HitPointWorld() {
		if (!IsAddressValid(this))  return Vector3();
		const auto do_hit = reinterpret_cast<Vector3(*)(HitTest*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("HitPointWorld"), 0)));
		return do_hit(this);
	}

	Vector3 HitTest::HitNormalWorld() {
		if (!IsAddressValid(this))  return Vector3();
		const auto do_hit = reinterpret_cast<Vector3(*)(HitTest*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("HitNormalWorld"), 0)));
		return do_hit(this);
	}

	Object* GameManifest::GUIDToObject(FPSystem::String* guid) {
		const auto rand_velo = reinterpret_cast<Object * (*)(FPSystem::String*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS(""), XS("GameManifest")), HASH("GUIDToObject"), 1)));
		return rand_velo(guid);
	}
	float ItemModProjectile::GetRandomVelocity() {
		const auto rand_velo = reinterpret_cast<float (*)(ItemModProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetRandomVelocity"), 0)));
		return rand_velo(this);
	}

	float ItemModProjectile::GetMinVelocity() {
		const auto rand_velo = reinterpret_cast<float (*)(ItemModProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetMinVelocity"), 0)));
		return rand_velo(this);
	}

	float ItemModProjectile::GetMaxVelocity() {
		const auto rand_velo = reinterpret_cast<float (*)(ItemModProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetMaxVelocity"), 0)));
		return rand_velo(this);
	}

	bool Projectile::IsAlive() {
		return (this->integrity() > 0.001f && this->traveledDistance() < this->maxDistance() && this->traveledTime() < 8.f);
	}
	void BasePlayer::SendProjectileUpdate(ProtoBuf::PlayerProjectileUpdate* ricochet)
	{
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SendProjectileUpdate"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, ricochet);
		}


		return;
	}

	void Projectile::UpdateVelocity(float deltaTime)
	{
		const auto do_hit = reinterpret_cast<void (*)(Projectile*, float)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("UpdateVelocity"), 1)));
		return do_hit(this, deltaTime);
	}

	bool Projectile::DoRicochet(HitTest* test, Vector3 point, Vector3 normal)
	{
		const auto do_hit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("DoRicochet"), 3)));
		return do_hit(this, test, point, normal);
	}


	bool Projectile::Reflect(int seed, Vector3 point, Vector3 normal)
	{
		const auto do_hit = reinterpret_cast<bool (*)(Projectile*, int, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("Reflect"), 3)));
		return do_hit(this, seed, point, normal);
	}

	bool Projectile::IsWaterMaterial(Il2CppString* name)
	{

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsWaterMaterial"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool*>(procedure, name);
		}
		else
		{

			return {};
		}
	}

	bool Projectile::DoHit(HitTest* test, Vector3 point, Vector3 normal)
	{
		const auto do_hit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("DoHit"), 3)));
		return do_hit(this, test, point, normal);
	}

	auto Projectile::Retire() -> void
	{
		if (!IsAddressValid(this))  return;

		const auto is_dead = reinterpret_cast<void (*)(Projectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("Retire"), 0)));
		return is_dead(this);
	}

	auto Projectile::get_isAlive() -> bool
	{
		if (!IsAddressValid(this))  return false;

		const auto is_dead = reinterpret_cast<bool (*)(Projectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("get_isAlive"), 0)));
		return is_dead(this);
	}

	auto Projectile::isAuthoritative() -> bool
	{
		if (!IsAddressValid(this))  return false;

		const auto is_dead = reinterpret_cast<bool (*)(Projectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("get_isAuthoritative"), 0)));
		return is_dead(this);
	}

	FPSystem::String* ItemDefinition::GetDisplayName(Item* item)
	{
		if (!IsAddressValid(this))  return {};

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetDisplayName"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<FPSystem::String*>(procedure, this, item);
		}
		else
		{

			return {};
		}
	}

	UnityEngine::Sprite* ItemDefinition::FindIconSprite(int id) {
		if (!IsAddressValid(this))  return {};

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("FindIconSprite"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<UnityEngine::Sprite*>(procedure, this, id);
		}
		else
		{

			return {};
		}
	}

	BaseEntity* Item::GetHeldEntity() {
		if (!IsAddressValid(this)) return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetHeldEntity"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<BaseEntity*>(procedure, this);
		}


		return {};
	}

	FPSystem::String* Item::GetItemName()
	{
		const auto item_definition = this->info();
		if (!IsAddressValid(item_definition))
		{
			return { };
		}

		const auto display_phrase = item_definition->displayName();
		if (!IsAddressValid(display_phrase))
		{
			return { };
		}

		const auto english = display_phrase->english();
		if (!IsAddressValid(english))
		{
			return { };
		}

		return english;
	}

	typedef struct Str
	{
		char stub[0x10];
		int len;
		wchar_t str[1];
	} *str;

	wchar_t* Item::get_weapon_name() {
			//const auto item_definition = this->info();
		const auto item_definition = this->info();
		if (!item_definition)
			return {};

		const auto display_name = item_definition->displayName();
		if (!display_name)
			return {};

		auto weapon_name = (str)(*reinterpret_cast<uintptr_t*>(display_name + 0x18));

		return weapon_name->str;
	}

	wchar_t* Item::GetItemName2()
	{
		const auto item_definition = this->info();
		if (!IsAddressValid(item_definition))
		{
			return { };
		}

		const auto display_phrase = item_definition->displayName();
		if (!IsAddressValid(display_phrase))
		{
			return { };
		}

		const auto english = display_phrase->english();
		if (!IsAddressValid(english))
		{
			return { };
		}

		return english->m_firstChar;
	}

	FPSystem::String* Item::GetItemShortName()
	{
		const auto definition = info();
		if (IsAddressValid(definition))
		{
			const auto short_name = definition->shortname();
			if (IsAddressValid(short_name))
			{
				return short_name;
			}
		}

		return { };
	}

	void BaseEntity::SetSkin(uint64_t skin_id)
	{
		skinID() = skin_id;
	}

	void Item::SetSkin(uint64_t skin_id)
	{
		skin() = skin_id;
	}


	auto BasePlayer::GetAimbotTarget(Vector3 Source, float MaxDist) -> BasePlayer::Target {
		if (!InGame)
			return {};

		return Visuals().GetAimbotTargetSafe(Source, MaxDist);
	}

	Item* ItemContainer::GetItem(int id)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!IsAddressValid(entity))
			return nullptr;

		auto item_list = this->itemList();
		if (!IsAddressValid(item_list))
			return nullptr;

		auto itmes = item_list->_items;

		uintptr_t items = *reinterpret_cast<uintptr_t*>(item_list + 0x10);
		if (!IsAddressValid(items))
			return nullptr;


		return *reinterpret_cast<Item**>(items + 0x20 + (id * 0x8));
	}

	Item* PlayerInventory::FindItemUID(ItemId2* id) {
		if (!IsAddressValid(this)) return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("FindItemByUID"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Item*>(procedure, this, id);
		}


		return {};
	}

	ItemContainer* PlayerInventory::get_belt()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!IsAddressValid(entity))
			return nullptr;

		auto address = this->containerBelt(); //il2cpp::value(xorstr_("PlayerInventory"), xorstr_("containerBelt"));
		if (!address)
			return nullptr;

		return address;
	}

	ItemId2* BasePlayer::GetHeldItemID() {
		if (!IsAddressValid(this))  return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetHeldItemID"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<ItemId2*>(procedure, this);
		}


		return {};
	}

	auto BasePlayer::ActiveItem() -> Item*
	{
		auto item_id = GetHeldItemID();
		if (IsAddressValid(item_id))
		{
			if (IsAddressValid(item_id) && IsAddressValid(inventory()))
			{
				return inventory()->FindItemUID(item_id);
			}
		}

		return nullptr;
	}

	Item* BasePlayer::GetHeldItemSafe()
	{
		if (!IsAddressValid(this)) return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetHeldItem"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Item*>(procedure, this);
		}


		return {};
	}

	BaseVehicle* BasePlayer::GetMountedVehicle()
	{
		if (!IsAddressValid(this))  return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetMountedVehicle"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<BaseVehicle*>(procedure, this);
		}


		return {};
	}

	void Door::KnockDoor(AssemblyCSharp::BasePlayer* player)
	{
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Menu_KnockDoor"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, player);
		}


		return;
	}

	bool BasePlayer::IsLocalPlayer()
	{
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsLocalPlayer"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	bool BasePlayer::HasFlag(uint16_t flag)
	{
		if (!IsAddressValid(this))  return false;

		return (playerFlags() & flag) == flag;
	}

	bool BasePlayer::IsReceivingSnapshot()
	{
		return HasFlag(8);
	}

	bool BasePlayer::IsConnected()
	{
		return HasFlag(256);
	}

	bool BasePlayer::IsSleeper()
	{
		return HasFlag(16);
	}

	bool BasePlayer::IsAdmin()
	{
		return HasFlag(4);
	}

	bool BasePlayer::IsSleeping()
	{
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsSleeping"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	UnityEngine::Transform* BasePlayer::get_bone_transform(int bone_id) {
		const auto model = this->model();
		if (IsAddressValid(model))
		{
			const auto bone_transforms = model->boneTransforms();
			if (IsAddressValid(bone_transforms))
			{
				const auto bone_transform = bone_transforms->m_Items[bone_id];
				if (IsAddressValid(bone_transform))
				{
					return bone_transform;
				}
			}
		}
	}

	auto GamePhysics::LineOfSightRadius(Vector3 p0, Vector3 p1, int layerMask, float radius, float padding, BaseEntity* ignoreEntity) -> bool
	{
		const auto LOS = reinterpret_cast<bool (*)(Vector3 p0, Vector3 p1, int layerMask, float radius, float padding, BaseEntity * ignoreEntity)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("LineOfSightRadius"), 6)));
		return LOS(p0, p1, layerMask, radius, padding, ignoreEntity);
	}

	auto GamePhysics::LineOfSightRadius_3(Vector3 p0, Vector3 p1, int layerMask, float padding, BaseEntity* ignoreEntity) -> bool
	{
		const auto LOS = reinterpret_cast<bool (*)(Vector3 p0, Vector3 p1, int layerMask, float padding, BaseEntity * ignoreEntity)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("LineOfSightRadius"), 5)));
		return LOS(p0, p1, layerMask, padding, ignoreEntity);
	}

	auto GamePhysics::LineOfSight(Vector3 p0, Vector3 p1, int layerMask, BaseEntity* ignoreEntity) -> bool
	{
		const auto LOS = reinterpret_cast<bool (*)(Vector3 p0, Vector3 p1, int layerMask, BaseEntity * ignoreEntity)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("LineOfSight"), 4)));
		return LOS(p0, p1, layerMask, ignoreEntity);
	}

	FPSystem::String* BasePlayer::get_displayName() {
		if (!IsAddressValid(this))  return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_displayName"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<FPSystem::String*>(procedure, this);
		}


		return {};
	}

	std::string* BasePlayer::get_displayNameTest() {
		if (!IsAddressValid(this))  return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_displayName"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<std::string*>(procedure, this);
		}


		return {};
	}

	bool PlayerModel::isNpc() {
		if (!IsAddressValid(this))  return false;

		static std::size_t offset = 0;
		const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<IsNpc>k__BackingField"));
		if (IsAddressValid(field))
		{
			offset = CIl2Cpp::il2cpp_field_get_offset(field);
		}

		return *reinterpret_cast<bool*>(ToAddress(this) + offset);
	}

	void BuildingBlock::UpgradeToGrade(RustStructs::BuildingGrade grade, int xd, BasePlayer* player) {
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("UpgradeToGrade"), 3);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, grade, xd, player);
		}


		return;
	}

	bool BuildingBlock::CanChangeToGrade(RustStructs::BuildingGrade grade, int xd, BasePlayer* player) {
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CanChangeToGrade"), 3);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this, grade, xd, player);
		}


		return false;
	}

	bool BuildingBlock::CanAffordUpgrade(RustStructs::BuildingGrade grade, int xd, BasePlayer* player) {
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CanAffordUpgrade"), 3);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this, grade, xd, player);
		}


		return false;
	}

	bool BuildingBlock::IsUpgradeBlocked() {
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsUpgradeBlocked"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	Vector3 BaseEntity::ClosestPoint(Vector3 position)
	{
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ClosestPoint"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Vector3>(procedure, this, position);
		}


		return Vector3(0.f, 0.f, 0.f);
	}

	void BaseEntity::OnSignal(RustStructs::Signal a, char* str = XS("")) {
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("OnSignal"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, a, CIl2Cpp::il2cpp_string_new(str));
		}


		return;
	}

	void BaseEntity::SendSignalBroadcast(RustStructs::Signal a, char* str = XS("")) {
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SendSignalBroadcast"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, a, CIl2Cpp::il2cpp_string_new(str));
		}


		return;
	}

	void BaseEntity::ServerRPC(const char* msg) {
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ServerRPC"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(msg));
		}


		return;
	}

	void PlayerEyes::set_position(Vector3 pos) {
		if (!IsAddressValid(this))  return;

		auto get_pos = reinterpret_cast<void(*)(PlayerEyes*, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), Hash(XS("set_position"), true), 1)));
		return get_pos(this, pos);
	}

	Vector3 PlayerEyes::MovementRight() {
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		auto get_pos = reinterpret_cast<Vector3(*)(PlayerEyes*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), Hash(XS("MovementRight"), true), 0)));
		return get_pos(this);
	}

	Vector3 PlayerEyes::MovementForward() {
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		auto get_pos = reinterpret_cast<Vector3(*)(PlayerEyes*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), Hash(XS("MovementForward"), true), 0)));
		return get_pos(this);
	}

	Vector3 PlayerEyes::BodyForward() {
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		auto get_pos = reinterpret_cast<Vector3(*)(PlayerEyes*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), Hash(XS("BodyForward"), true), 0)));
		return get_pos(this);
	}


	Vector3 PlayerEyes::BodyRight() {
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		auto get_pos = reinterpret_cast<Vector3(*)(PlayerEyes*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), Hash(XS("BodyRight"), true), 0)));
		return get_pos(this);
	}

	Vector3 PlayerEyes::HeadForward() {
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		auto get_pos = reinterpret_cast<Vector3(*)(PlayerEyes*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), Hash(XS("HeadForward"), true), 0)));
		return get_pos(this);
	}

	bool ConsoleSystemArg::HasPermissionn()
	{
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("HasPermission"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	void PlayerEyes::SetBodyRotation(Vector4 rot)
	{
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_bodyRotation"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, rot);
		}


		return;
	}

	Vector3 ThrownWeapon::GetInheritedVelocity(BasePlayer* ply, Vector3 dir)
	{
		if (!IsAddressValid(this))  return { 0, 0, 0 };

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetInheritedVelocity"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Vector3>(procedure, ply, dir);
		}


		return Vector3(0, 0, 0);
	}

	Vector3 BaseMelee::GetInheritedVelocity(AssemblyCSharp::BasePlayer* player, Vector3 dir)
	{
		if (!IsAddressValid(this))  return Vector3();
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetInheritedVelocity"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Vector3>(procedure, this, player, dir);
		}


		return Vector3();
	}

	Vector4 PlayerEyes::bodyRotation() {
		auto body_rotation = *reinterpret_cast<Vector4*>(this + 0x44);

		if (body_rotation.empty())
			return Vector4(0.f, 0.f, 0.f, 0.f);

		return body_rotation;
	}

	auto BasePlayer::BoundsPadding() -> float {
		const auto get_is_ducked = reinterpret_cast<float (*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("BoundsPadding"), 0)));
		return get_is_ducked(this);
	}

	auto BasePlayer::GetJumpHeight() -> float {
		if (!IsAddressValid(this))  return 0.f;
		const auto is_dead = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetJumpHeight"), 0)));
		return is_dead(this);
	}


	float BaseProjectile::GetProjectileVelocityScale(bool max) {
		const auto rand_velo = reinterpret_cast<float (*)(BaseProjectile*, bool)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetProjectileVelocityScale"), 1)));
		return rand_velo(this, max);
	}


	auto BaseNetworkable::PlayerDestroyed() -> bool
	{
		if (!IsAddressValid(this))  return false;
		return *reinterpret_cast<bool*>(this + 0x38);
	}

	bool BaseNetworkable::PlayerValid() {
		if (!IsAddressValid(this))  return false;
		return !this->PlayerDestroyed() && this->net() != nullptr;
	}

	auto BaseEntity::GetWorldVelocity() -> Vector3 {
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		const auto is_dead = reinterpret_cast<Vector3(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetWorldVelocity"), 0)));
		return is_dead(this);
	}

	auto BaseEntity::GetParentVelocity() -> Vector3 {

		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		const auto is_dead = reinterpret_cast<Vector3(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetParentVelocity"), 0)));
		return is_dead(this);
	}

	



	auto BasePlayer::IsWeapon() -> bool {
		const auto item = ActiveItem();
		if (item)
		{
			const bool bIsWeapon = !item->IsA(AssemblyCSharp::BaseMelee::StaticClass()) &&
				!item->IsA(AssemblyCSharp::ThrownWeapon::StaticClass()) &&
				!item->IsA(AssemblyCSharp::TorchWeapon::StaticClass());


			if (!bIsWeapon)
				return false;

			const auto held_entity = item->GetHeldEntity();
			if (bIsWeapon && IsAddressValid(held_entity) && (
				held_entity->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) ||
				held_entity->IsA(AssemblyCSharp::BowWeapon::StaticClass()) ||
				held_entity->IsA(AssemblyCSharp::CompoundBowWeapon::StaticClass()) ||
				held_entity->IsA(AssemblyCSharp::CrossbowWeapon::StaticClass()) ||
				held_entity->IsA(AssemblyCSharp::FlintStrikeWeapon::StaticClass())))
				return true;

		}
	}

	auto BasePlayer::IsMelee() -> bool {

		if (const auto item = ActiveItem(); (item))
		{
			const auto held_entity = item->GetHeldEntity();

			if (IsAddressValid(held_entity) && !held_entity->IsA(AssemblyCSharp::FlameThrower::StaticClass()) && !held_entity->IsA(AssemblyCSharp::TorchWeapon::StaticClass()) && (
				held_entity->IsA(AssemblyCSharp::ThrownWeapon::StaticClass()) ||
				held_entity->IsA(AssemblyCSharp::BaseMelee::StaticClass())))
				return true;
		}

		return false;
	}

	void BaseMelee::ProcessAttack(HitTest* hit) {
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ProcessAttack"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, hit);
		}


		return;
	}

	void BaseMelee::DoThrow() {
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DoThrow"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this);
		}


		return;
	}

	void BaseMelee::ClientAttack() {
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ClientAttack"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this);
		}


		return;
	}

	bool AttackEntity::IsFullyDeployed()
	{
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsFullyDeployed"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	ItemDefinition* AttackEntity::GetOwnerItemDefinition()
	{
		if (!IsAddressValid(this))  return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetOwnerItemDefinition"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<ItemDefinition*>(procedure, this);
		}


		return {};
	}

	bool AttackEntity::HasAttackCooldown() {
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("HasAttackCooldown"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	auto AttackEntity::StartAttackCooldown(float coolDown) -> void
	{
		if (!IsAddressValid(this)) return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("StartAttackCooldown"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, coolDown);
		}
		else
		{

			return;
		}
	}

	auto ModelState::SetMounted(bool value) -> void {
		const auto set_mounted = reinterpret_cast<void (*)(ModelState*, bool)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("set_mounted"), 1)));
		return set_mounted(this, value);
	}

	auto ModelState::get_ducked() -> bool {
		const auto get_is_ducked = reinterpret_cast<bool (*)(ModelState*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("get_ducked"), 0)));
		return get_is_ducked(this);
	}

	auto ModelState::SetOnLadder(bool value) -> void {
		const auto set_on_Ladder = reinterpret_cast<void (*)(ModelState*, bool)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("set_onLadder"), 1)));
		return set_on_Ladder(this, value);
	}

	void ModelState::SetSprinting(bool Value)
	{
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_sprinting"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, Value);
		}


		return;
	}

	void ModelState::set_flag(RustStructs::ModelState_Flag flag) {
		int flags = this->flags();

		this->flags() = flags |= (int)flag;
	}

	void ModelState::remove_flag(RustStructs::ModelState_Flag flag) {
		int flags = this->flags();
		flags &= ~(int)flag;

		this->flags() = flags;
	}

	bool InputState::IsDown(RustStructs::BUTTON btn)
	{
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsDown"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this, btn);
		}


		return false;
	}

	bool InputState::WasJustPressed(RustStructs::BUTTON btn)
	{
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("WasJustPressed"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this, btn);
		}


		return false;
	}

	bool Collider::set_enabled(bool value) {
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_enabled"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this, value);
		}


		return false;
	}

	Vector3 AimConeUtil::GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetModifiedAimConeDirection"), 3);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Vector3>(procedure, aimCone, inputVec, anywhereInside);
		}


		return Vector3(0, 0, 0);
	}

	auto BasePlayer::GetMaxSpeed() -> float {
		const auto get_is_ducked = reinterpret_cast<float (*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("GetMaxSpeed"), 0)));
		return get_is_ducked(this);
	}

	auto BasePlayer::MaxEyeVelocity() -> float
	{
		if (!IsAddressValid(this))  return 0.0f;

		float speed = this->GetMaxSpeed();

		/*	const auto mounted = this->mounted();
			if (mounted)
			{
				return speed * 4.0f;
			}*/
		return speed;
	}

	bool BaseProjectile::HasReloadCooldown() {
		return UnityEngine::Time().get_time() < nextReloadTime();
	}

	void BaseProjectile::ShotFired() {
		const auto rand_velo = reinterpret_cast<void (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("ShotFired"), 0)));
		return rand_velo(this);
	}

	void BaseProjectile::BeginCycle() {
		const auto rand_velo = reinterpret_cast<void (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("BeginCycle"), 0)));
		return rand_velo(this);
	}

	void BaseProjectile::DidAttackClientside() {
		const auto rand_velo = reinterpret_cast<void (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("DidAttackClientside"), 0)));
		return rand_velo(this);
	}

	void BaseProjectile::UpdateAmmoDisplay() {
		const auto rand_velo = reinterpret_cast<void (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("UpdateAmmoDisplay"), 0)));
		return rand_velo(this);
	}
	void BaseProjectile::DoAttack() {
		const auto rand_velo = reinterpret_cast<void (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("DoAttack"), 0)));
		return rand_velo(this);
	}

	void BaseProjectile::LaunchProjectile() {
		const auto rand_velo = reinterpret_cast<void (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("LaunchProjectile"), 0)));
		return rand_velo(this);
	}

	OBB BasePlayer::WorldSpaceBounds()
	{
		if (!IsAddressValid(this)) return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("WorldSpaceBounds"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<OBB>(procedure, this);
		}


		return {};
	}

	auto ItemIcon::SetTimedLootAction(int a1, void* a2) -> void {
		const auto LOS = reinterpret_cast<void (*)(ItemIcon*, int, void*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("SetTimedLootAction"), 2)));
		return LOS(this, a1, a2);
	}

	void ItemIcon::RunTimedAction() {
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("RunTimedAction"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this);
		}


		return;
	}

	auto ItemIcon::StartTimedLootAction(float delay) -> void {
		const auto LOS = reinterpret_cast<void (*)(ItemIcon*, float)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("StartTimedLootAction"), 1)));
		return LOS(this, delay);
	}

	void PlayerWalkMovement::TeleportTo(Vector3 pos, BasePlayer* player) {
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("TeleportTo"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, pos, player);
		}


		return;
	}

	auto PlayerWalkMovement::FallVelocity() -> Vector3 {

		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		const auto is_dead = reinterpret_cast<Vector3(*)(PlayerWalkMovement*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("FallVelocity"), 0)));
		return is_dead(this);
	}

	void PlayerWalkMovement::Jump(AssemblyCSharp::ModelState* ms)
	{
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Jump"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, ms, false);
		}


		return;
	}


	void BaseMovement::TeleportTo(Vector3 pos, BasePlayer* player) {
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("TeleportTo"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, pos, player);
		}


		return;
	}

	float BaseMovement::ducking() {
		if (!IsAddressValid(this))  return false;

		static std::size_t offset = 0;
		const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<Ducking>k__BackingField"));
		if (IsAddressValid(field))
		{
			offset = CIl2Cpp::il2cpp_field_get_offset(field);
		}

		return *reinterpret_cast<float*>(ToAddress(this) + offset);
	}

	Vector3 BaseMovement::InheritedVelocity() {
		if (!IsAddressValid(this))  return Vector3(0.f, 0.f, 0.f);

		static std::size_t offset = 0;
		const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<InheritedVelocity>k__BackingField"));
		if (IsAddressValid(field))
		{
			offset = CIl2Cpp::il2cpp_field_get_offset(field);
		}

		return *reinterpret_cast<Vector3*>(ToAddress(this) + offset);
	}

	float BaseMovement::Crawling() {
		if (!IsAddressValid(this))  return 0.f;

		static std::size_t offset = 0;
		const auto field = CIl2Cpp::FindField(this->StaticClass(), HASH("<Crawling>k__BackingField"));
		if (IsAddressValid(field))
		{
			offset = CIl2Cpp::il2cpp_field_get_offset(field);
		}

		return *reinterpret_cast<float*>(ToAddress(this) + offset);
	}

	void BaseMovement::set_TargetMovement(Vector3 value)
	{
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_TargetMovement"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, value);
		}


		return;
	}

	void BaseMovement::set_Grounded(float value)
	{
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_Grounded"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, value);
		}


		return;
	}

	BaseMovement* BasePlayer::GetBaseMovement() {
		auto base_movement = this->movement();

		return (BaseMovement*)base_movement;
	}

	bool BasePlayer::IsSwimming() {
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsSwimming"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	bool BasePlayer::IsRunning() {
		if (!IsAddressValid(this))  return false;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsRunning"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, this);
		}


		return false;
	}

	float BasePlayer::GetRadius() {
		if (!IsAddressValid(this))  return 0.f;
		const auto radius = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetRadius"), 0)));
		return radius(this);
	}

	float BasePlayer::GetHeight(bool ducked) {
		if (!IsAddressValid(this))  return 0.f;
		const auto height = reinterpret_cast<float(*)(BasePlayer*, bool)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetHeight"), 1)));
		return height(this, ducked);
	}

	void BasePlayer::SetVA(const Vector2& VA)
	{
		//if (IsAddressValid(this->input()))
		//{
		//	this->input()->bodyAngles() = VA;
		//}
	}

	Vector2 BasePlayer::GetVA()
	{
		//if (IsAddressValid(this->input()))
		//{
		//	Vector2 Angles = this->input()->bodyAngles();
		//	return Angles;
		//}
		return Vector2{ 0, 0 };
	}

	Vector2 BasePlayer::GetRA()
	{
		if (IsAddressValid(this->input()))
		{
			Vector2 Angles = this->input()->recoilAngles();
			return Angles;
		}
		return Vector2{ 0, 0 };
	}

	uint64_t StringPool::Get(const char* name)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethodFullArgs(HASH("Assembly-CSharp::StringPool::Get(String): UInt32"));
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<uint64_t>(procedure, CIl2Cpp::il2cpp_string_new(name));
		}


		return 0;
	}

	void ViewModel::Play(const char* name, int layer) {
		if (!IsAddressValid(this))  return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Play"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(name), layer);
		}


		return;
	}
	auto GamePhysics::Trace(UnityEngine::Ray ray, float radius, UnityEngine::RaycastHit hitInfo, float maxDistance, int layerMask, RustStructs::QueryTriggerInteraction triggerInteraction, BaseEntity* ignoreEntity) -> bool
	{

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Trace"), 7);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, ray, radius, hitInfo, maxDistance, layerMask, triggerInteraction, ignoreEntity);
		}


		return false;
	}
	auto GamePhysics::Trace2(UnityEngine::Ray* ray, float radius, UnityEngine::RaycastHit hitInfo, float maxDistance, int layerMask, RustStructs::QueryTriggerInteraction triggerInteraction, BaseEntity* ignoreEntity) -> bool
	{

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Trace"), 7);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, ray, radius, hitInfo, maxDistance, layerMask, triggerInteraction, ignoreEntity);
		}


		return false;
	}
	auto BasePlayer::OnLand(float fVelocity) -> float {
		if (!IsAddressValid(this))  return 0.f;
		const auto is_dead = reinterpret_cast<float(*)(BasePlayer*, float)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("OnLand"), 1)));
		return is_dead(this, fVelocity);
	}

	void BasePlayer::SendClientTick()
	{
		if (!IsAddressValid(this))  return;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SendClientTick"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this);
		}


		return;
	}

	void Graphics::SetFov(float value)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_fov"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, value);
		}


		return;
	}

	bool GameTrace::Trace(HitTest* test, int layerMask)
	{
		if (!test)
			return false;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Trace"), 2);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, test, layerMask);
		}


		return false;
	}

	bool ConsoleNetwork::ClientRunOnServer(Unity_String strCommand)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ClientRunOnServer"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, strCommand);
		}


		return false;
	}
}

