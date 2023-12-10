#include "UnityEngine.hpp"

namespace UnityEngine
{


	Vector2::Vector2()
		: x(0.f)
		, y(0.f)
	{ }

	Vector2::Vector2(float vector_x, float vector_y)
		: x(vector_x)
		, y(vector_y)
	{ }

	Vector2::Vector2(const Vector2& vector)
		: x(vector[0])
		, y(vector[1])
	{ }

	float Vector2::Dot(const Vector2& vector) const
	{
		return (x * vector[0] +
			y * vector[1]);
	}


	static float my_sqrt(float number)
	{
		long        i;
		float       x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y; // floating point bit level hacking [sic]
		i = 0x5f3759df - (i >> 1); // Newton's approximation
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
		y = y * (threehalfs - (x2 * y * y)); // 2nd iteration

		return 1 / y;
	}
	float Vector2::LengthSquared() const
	{
		return (x * x +
			y * y);
	}

	float Vector2::Length() const
	{
		return my_sqrt(x * x +
			y * y);
	}

	float Vector2::DistanceSquared(const Vector2& vector) const
	{
		const auto direction(*this - vector);
		return direction.LengthSquared();
	}


	float Vector2::Distance(const Vector2& vector) const
	{
		const auto direction(*this - vector);
		return direction.Length();
	}


	float Vector2::Normalize()
	{
		constexpr auto epsilon = std::numeric_limits< float >::epsilon();

		const auto length = Length();
		const auto factor = (1.f / (length + epsilon));

		x *= factor;
		y *= factor;

		return length;
	}



	Vector2 Vector2::Normalized()
	{
		auto vector(*this);
		vector.Normalize();
		return std::move(vector);
	}

	Vector2 Vector2::MemoryAimNormalize()
	{
		if (x < -89)
			x = -89;

		else if (x > 89)
			x = 89;

		if (y < -360)
			y += 360;

		else if (y > 360)
			y -= 360;

		return { x, y };
	}

	float Vector2::operator[](std::size_t index) const
	{
		return (&x)[index];
	}

	float& Vector2::operator[](std::size_t index)
	{
		return (&x)[index];
	}

	Vector2& Vector2::operator=(const Vector2& vector)
	{
		if (std::addressof(vector) != this)
		{
			x = vector[0];
			y = vector[1];
		}
		return (*this);
	}

	Vector2& Vector2::operator+=(float value)
	{
		x += value;
		y += value;
		return (*this);
	}

	Vector2& Vector2::operator-=(float value)
	{
		x -= value;
		y -= value;
		return (*this);
	}

	Vector2& Vector2::operator*=(float value)
	{
		x *= value;
		y *= value;
		return (*this);
	}

	Vector2& Vector2::operator/=(float value)
	{
		x /= value;
		y /= value;
		return (*this);
	}

	Vector2& Vector2::operator+=(const Vector2& vector)
	{
		x += vector[0];
		y += vector[1];
		return (*this);
	}

	Vector2& Vector2::operator-=(const Vector2& vector)
	{
		x -= vector[0];
		y -= vector[1];
		return (*this);
	}

	Vector2& Vector2::operator*=(const Vector2& vector)
	{
		x *= vector[0];
		y *= vector[1];
		return (*this);
	}

	Vector2& Vector2::operator/=(const Vector2& vector)
	{
		x /= vector[0];
		y /= vector[1];
		return (*this);
	}

	Vector2 Vector2::operator+(float value) const
	{
		return { x + value,
						 y + value };
	}

	Vector2 Vector2::operator-(float value) const
	{
		return { x - value,
						 y - value };
	}

	Vector2 Vector2::operator*(float value) const
	{
		return { x * value,
						 y * value };
	}

	Vector2 Vector2::operator/(float value) const
	{
		return { x / value,
						 y / value };
	}

	Vector2 Vector2::operator+(const Vector2& vector) const
	{
		return { x + vector[0],
						 y + vector[1] };
	}

	Vector2 Vector2::operator-(const Vector2& vector) const
	{
		return { x - vector[0],
						 y - vector[1] };
	}

	Vector2 Vector2::operator*(const Vector2& vector) const
	{
		return { x * vector[0],
						 y * vector[1] };
	}

	Vector2 Vector2::operator/(const Vector2& vector) const
	{
		return { x / vector[0],
						 y / vector[1] };
	}

	// 
	// [ Vector3 ] implementation
	// 
	Vector3::Vector3()
		: x(0.f)
		, y(0.f)
		, z(0.f)
	{ }

	Vector3::Vector3(float vector_x, float vector_y, float vector_z)
		: x(vector_x)
		, y(vector_y)
		, z(vector_z)
	{ }

	Vector3::Vector3(const Vector3& vector)
		: x(vector[0])
		, y(vector[1])
		, z(vector[2])
	{ }

	float Vector3::Dot(const Vector3& vector) const
	{
		return (x * vector[0] + y * vector[1] + z * vector[2]);
	}

	float Vector3::Length() const
	{
		return Math::sqrtf(x * x + y * y + z * z);
	}



	float Vector3::Length2D() const
	{
		return Math::sqrtf(x * x + z * z);
	}

	//float Vector3::UnityDistance(const Vector3& a, const Vector3& b) const
	//{
	//	float num = a.x - b.x;
	//	float num2 = a.y - a.y;
	//	float num3 = a.z - b.z;
	//	return (float)crt_sqrt((double)(num * num + num2 * num2 + num3 * num3));
	//}

	float Vector3::Distance(const Vector3& vector) const
	{
		const auto direction = (*this - vector);
		return direction.Length();
	}

	Vector3 Vector3::operator/(float fInput) const {/* Allows Vector to divide itself from a float */
		return Vector3{ x / fInput, y / fInput, z / fInput };
	}
	Vector3 Vector3::Normalized() const {
		return { x / Length(), y / Length(), z / Length() };
	}

	bool Vector3::operator!=(const Vector3& vInput) const {  /* Checks if Vector is NOT Equal with another Vector */
		if (x != vInput.x || y != vInput.y || z != vInput.z)
			return true;

		return false;
	}
	float Vector3::Distance2D(const Vector3& vector) const
	{
		const auto direction = (*this - vector);
		return direction.Length2D();
	}
	float Vector3::UnityMagnitude()
	{
		return (float)Math::sqrtf((double)(this->x * this->x + this->y * this->y + this->z * this->z));
	}

	float Vector3::Magnitude() {
		return my_sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	Vector3 Vector3::UnityNormalize()
	{
		Vector3 tis(x, y, z);
		float num = Vector3(x, y, z).Magnitude();
		if (num > 1E-05f)
		{
			tis /= num;
		}
		else
		{
			tis = Vector3(0, 0, 0);
		}
		x = tis.x;
		y = tis.y;
		z = tis.z;

		return { x,y,z };
	}

	float Vector3::Magnitude2D() {
		return Math::sqrtf(this->x * this->x + this->z * this->z);
	}


	float AngleNormalize(float angle)
	{
		angle = Math::fmod(angle, 360.f);

		if (angle > 180.f)
		{
			angle -= 360.f;
		}
		else if (angle < 180.f)
		{
			angle += 360.f;
		}

		return angle;
	}

	float Vector3::Normalize()
	{
		const auto length = Length();

		if (length > 0.f)
		{
			x /= length;
			y /= length;
			z /= length;
		}
		else
		{
			x = 0.f;
			y = 0.f;
			z = 0.f;
		}

		return length;
	}

	bool Vector3::IsZero() const
	{
		return (x == 0.f &&
			y == 0.f &&
			z == 0.f);
	}

	float Vector3::get_3d_dist(const Vector3& Dst) {
		return my_sqrt(powFFFFFFFFFFFFFFFFFFFFFF(x - Dst.x) + powFFFFFFFFFFFFFFFFFFFFFF(y - Dst.y) + powFFFFFFFFFFFFFFFFFFFFFF(z - Dst.z));
	}
	Vector3& Vector3::operator/=(const Vector3& vInput) { /* Allows Vector to be multiplied by another Vector */
		x /= vInput.x;
		y /= vInput.y;
		z /= vInput.z;
		return *this;
	}

	Vector3& Vector3::operator/=(float fInput) { /* Allows Vector to be divided by a float */
		x /= fInput;
		y /= fInput;
		z /= fInput;
		return *this;
	}

	float Vector3::operator[](std::size_t index) const
	{
		return (&x)[index];
	}

	float& Vector3::operator[](std::size_t index)
	{
		return (&x)[index];
	}

	Vector3 Vector3::operator-() const
	{
		return { -x, -y, -z };
	}

	Vector3 Vector3::operator*(float fInput) const { /* Allows Vector to multiply itself from a float */
		return Vector3{ x * fInput, y * fInput, z * fInput };
	}

	Vector3 Vector3::operator+(const Vector3& vector) const
	{
		return { x + vector[0],
						 y + vector[1],
						 z + vector[2] };
	}

	Vector3 Vector3::operator-(const Vector3& vector) const
	{
		return { x - vector[0],
						 y - vector[1],
						 z - vector[2] };
	}

	Vector3 Vector3::operator*(const Vector3& vector) const
	{
		return { x * vector[0],
						 y * vector[1],
						 z * vector[2] };
	}

	Vector3 Vector3::operator/(const Vector3& vector) const
	{
		return { x / vector[0],
						 y / vector[1],
						 z / vector[2] };
	}

	Vector3 Vector3::Scale(const float times) const
	{
		return { x * times, y * times, z * times };
	}

	Vector3& Vector3::operator-=(const Vector3& vInput) {/* Allows Vector to be subtracted by another Vector */
		x -= vInput.x;
		y -= vInput.y;
		z -= vInput.z;

		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& vInput) { /* Allows Vector to be added to another Vector */
		x += vInput.x;
		y += vInput.y;
		z += vInput.z;
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& vInput) { /* Allows Vector to be multiplied by another Vector */
		x *= vInput.x;
		y *= vInput.y;
		z *= vInput.z;
		return *this;
	}

	Vector3& Vector3::operator*=(float vInput) { /* Allows Vector to be multiplied by another Vector */
		x *= vInput;
		y *= vInput;
		z *= vInput;
		return *this;
	}

	Vector3 Vector3::Zero(0.f, 0.f, 0.f);
	Vector3 Vector3::Forward(0.f, 0.f, 1.f);
	Vector3 Vector3::Back(0.f, 0.f, -1.f);

	bool Object::IsA(const Il2CppClass* object)
	{
		if (!IsAddressValid(this))
			return false;


		auto super = klass;

		while (IsAddressValid(super))
		{
			if (super == object)
			{
				return true;
			}

			super = super->parent;
		}

		return false;
	}

#pragma optimize( "", off )

	Component* GameObject::AddComponent(FPSystem::Type* type)
	{
		if(!IsAddressValid(this)) return nullptr;
		const auto add_component = reinterpret_cast<Component * (*)(GameObject*, FPSystem::Type*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("AddComponent"), 1)));
		if (!add_component)
			return nullptr;

		return Call<Component*>((uintptr_t)add_component, this, type);
	}

#pragma optimize( "", on )

	bool Input::GetMouseButton(int a1) {
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetMouseButton"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, a1);
		}
		else
		{

			return false;
		}
	}

	Vector3 Input::GetMousePosition() {
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_mousePosition"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Vector3>(procedure);
		}
		else
		{

			return Vector3(0.f, 0.f, 0.f);
		}
	}

	bool Input::GetKey(RustStructs::KeyCode code)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetKey"), 1);
			if (IsAddressValid(method))
			{
				procedure = (uintptr_t)(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, code);
		}
		else
		{
			return false;
		}
	}

	void RenderSettings::set_ambientMode(RustStructs::AmbientMode value)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_ambientMode"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, value);
		}
		else
		{

			return;
		}
	}

	void RenderSettings::set_ambientIntensity(float value)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_ambientIntensity"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, value);
		}
		else
		{

			return;
		}
	}

	void RenderSettings::set_ambientLight(Color value)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_ambientLight"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, value);
		}
		else
		{

			return;
		}
	}

	bool Input::GetKeyDown(RustStructs::KeyCode code)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetKeyDown"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, code);
		}
		else
		{

			return false;
		}
	}



	Event* Event::Current()
	{
		const auto get_current = reinterpret_cast<Event * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Event")), HASH("get_current"), 0)));
		return Call<Event*>(ToAddress(get_current));
	}

	RustStructs::KeyCode Event::get_keyCode(Event* current) {
		const auto get_keyCode = reinterpret_cast<RustStructs::KeyCode(*)(Event*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Event")), HASH("get_keyCode"), 0)));
		return Call<RustStructs::KeyCode>(ToAddress(get_keyCode), current);
	}

	Vector2 Event::Delta()
	{
		if(!IsAddressValid(this)) return Vector2(0.f, 0.f);
		auto m_ptr = *reinterpret_cast<std::uint64_t*>(this + 0x10);
		if (!m_ptr) return Vector2(0.f, 0.f);;

		return *reinterpret_cast<Vector2*>(m_ptr + 0x10);
	}

	Vector2 Event::mousePosition()
	{
		if(!IsAddressValid(this)) return Vector2(0.f, 0.f);;
		auto m_ptr = *reinterpret_cast<std::uint64_t*>(this + 0x10);
		if (!m_ptr) return Vector2(0.f, 0.f);;

		return *reinterpret_cast<Vector2*>(m_ptr + 0x8);
	}

	RustStructs::EventType Event::Type()
	{
		if(!IsAddressValid(this)) return RustStructs::EventType::MouseDown;

		const auto get_type = reinterpret_cast<RustStructs::EventType(*)(Event*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Event")), HASH("get_type"), 0)));
		return Call<RustStructs::EventType>(ToAddress(get_type), this);
	}

	void GUIStyle::SetFontSize(int value)
	{
		const auto set_fontSize = reinterpret_cast<void(*)(GUIStyle*, int)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUIStyle")), HASH("set_fontSize"), 1)));
		return Call<void>(ToAddress(set_fontSize), this, value);
	}

	float GUIStyle::GetFontSize()
	{
		const auto get_fontSize = reinterpret_cast<float(*)(GUIStyle*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUIStyle")), HASH("get_fontSize"), 0)));
		return Call<float>(ToAddress(get_fontSize), this);
	}

	void GUIStyle::SetAlignment(GUIStyle* style, int text)
	{
		const auto set_alignment = reinterpret_cast<void (*)(GUIStyle*, int)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUIStyle")), HASH("set_alignment"), 1)));

		return Call<void>(ToAddress(set_alignment), style, text);
	}

	GUIStyle* GUISkin::GetLabel()
	{
		const auto get_label = reinterpret_cast<GUIStyle * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUISkin")), HASH("get_label"), 0)));
		return Call<GUIStyle*>(ToAddress(get_label));
	}

	GUISkin* GUI::GetSkin()
	{
		const auto get_skin = reinterpret_cast<GUISkin * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUI")), HASH("get_skin"), 0)));
		return Call<GUISkin*>(ToAddress(get_skin));
	}

	void GUI::SetColor(Color clr)
	{
		const auto set_color = reinterpret_cast<void(*)(Color)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUI")), HASH("set_color"), 1)));
		return Call<void>(ToAddress(set_color), clr);
	}

	void GUI::DrawTexture(UnityEngine::rect_t a1, UnityEngine::Texture2D* a2) {
		const auto draw_texture = reinterpret_cast<void(*)(UnityEngine::rect_t, UnityEngine::Texture2D*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUI")), HASH("DrawTexture"), 2)));
		if (!draw_texture)
			return;

		return Call<void>(ToAddress(draw_texture), a1, a2);
	}

	void GUI::Label(UnityEngine::rect_t position, Unity_String text, uintptr_t style) {
		const auto label = reinterpret_cast<void(*)(UnityEngine::rect_t, Unity_String, uintptr_t)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUI")), HASH("Label"), 3)));
		if (!label)
			return;

		return Call<void>(ToAddress(label), position, text, style);
	}

	void GUI::LabelTest(UnityEngine::rect_t position, Il2CppString* text, uintptr_t style) {
		const auto label = reinterpret_cast<void(*)(UnityEngine::rect_t, Il2CppString*, uintptr_t)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUI")), HASH("Label"), 3)));
		if (!label)
			return;

		return Call<void>(ToAddress(label), position, text, style);
	}

	Vector3 Transform::get_position()
	{
		if(!IsAddressValid(this))
			return Vector3();

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_position"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Vector3>(procedure, this);
		}
		else
		{

			return Vector3();
		}
	}



	auto Transform::InverseTransformPoint(Vector3 pt) -> Vector3 {
		if(!IsAddressValid(this)) return Vector3(0.f, 0.f, 0.f);
		const auto add_component = reinterpret_cast<Vector3(*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("InverseTransformPoint"), 1)));
		return add_component(this, pt);
	}

	auto Transform::InverseTransformDirection(Vector3 pt) -> Vector3 {
		if(!IsAddressValid(this)) return Vector3(0.f, 0.f, 0.f);
		const auto add_component = reinterpret_cast<Vector3(*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("InverseTransformDirection"), 1)));
		return add_component(this, pt);
	}

	Transform* Transform::get_parent() {
		if(!IsAddressValid(this)) return {};
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_parent"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call< Transform*>(procedure, this);
		}


		return {};
	}


	auto Transform::set_position(Vector3 pos) -> void {
		if(!IsAddressValid(this)) return;

		const auto add_component = reinterpret_cast<void* (*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("set_position"), 1)));
		return Call<void>((uintptr_t)add_component, this, pos);
	}

	auto Transform::set_rotation(Vector4 pos) -> void {
		if(!IsAddressValid(this)) return;

		const auto add_component = reinterpret_cast<void* (*)(Transform*, Vector4)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("set_rotation"), 1)));
		return Call<void>((uintptr_t)add_component, this, pos);
	}

	auto Transform::set_localscale(Vector3 amount) -> void {
		if(!IsAddressValid(this)) return;

		const auto add_component = reinterpret_cast<void* (*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("set_localScale"), 1)));
		return Call<void>((uintptr_t)add_component, this, amount);
	}

	Transform* Component::get_transform()
	{
		if(!IsAddressValid(this))
			return nullptr;

		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_transform"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<Transform*>(procedure, this);
		}
		else
		{

			return nullptr;
		}
	}

	Vector3 Component::get_positionz()
	{
		const auto transform = get_transform();

		if (IsAddressValid(transform))
		{
			return transform->get_position();
		}

		return Vector3::Zero;
	}

	auto Camera::viewMatrix() -> VMatrix
	{
		auto cam = get_main();
		if (cam) return {};

		auto camera_ = *reinterpret_cast<std::uintptr_t*>(cam + 0x10);
		if (!camera_) {
			return {};
		}

		auto matrix = *reinterpret_cast<VMatrix*>(camera_ + 0x2e4);
		if (!matrix.m) {
			return {};
		}
		return matrix;
	}

	Vector3 Camera::WorldToScreen(Vector3 position)
	{
		if (!IsAddressValid(view))
		{
			return Vector3(0.f, 0.f, 0.f);
		}

		auto matrix = view->viewMatrix;

		if (!matrix.m) {
			return { 0,0,0 };
		}
		Vector3 out;
		const auto temp = matrix.transpose();

		auto translation_vector = Vector3{ temp[3][0], temp[3][1], temp[3][2] };
		auto up = Vector3{ temp[1][0], temp[1][1], temp[1][2] };
		auto right = Vector3{ temp[0][0], temp[0][1], temp[0][2] };

		float w = translation_vector.Dot(position) + temp[3][3];

		if (w < 0.098f) {
			return Vector3(0, 0, 0);
		}

		float x = up.Dot(position) + temp._24;
		float y = right.Dot(position) + temp._14;

		out.x = (static_cast<float>(UnityEngine::Screen::get_width()) / 2) * (1 + y / w);
		out.y = (static_cast<float>(UnityEngine::Screen::get_height()) / 2) * (1 - x / w);
		out.z = w;

		return out;
	}


	bool Camera::WorldToScreen(const Vector3& position, Vector2& screen_pos)
	{
		if (!IsAddressValid(view))
		{
			return false;
		}

		auto view_matrix = view->viewMatrix;

		if (position.IsZero())
			return false;

		__m128 trans_vec = _mm_set_ps(0.0f, view_matrix.m[2][3], view_matrix.m[1][3], view_matrix.m[0][3]);
		__m128 right_vec = _mm_set_ps(0.0f, view_matrix.m[2][0], view_matrix.m[1][0], view_matrix.m[0][0]);
		__m128 up_vec = _mm_set_ps(0.0f, view_matrix.m[2][1], view_matrix.m[1][1], view_matrix.m[0][1]);

		__m128 element_pos = _mm_set_ps(0.0f, position.z, position.y, position.x);

		__m128 dot_trans = _mm_dp_ps(trans_vec, element_pos, 0x71);
		__m128 dot_right = _mm_dp_ps(right_vec, element_pos, 0x71);
		__m128 dot_up = _mm_dp_ps(up_vec, element_pos, 0x71);

		float result_trans[4];
		float result_right[4];
		float result_up[4];

		_mm_store_ps(result_trans, dot_trans);
		_mm_store_ps(result_right, dot_right);
		_mm_store_ps(result_up, dot_up);

		float w = result_trans[0] + view_matrix.m[3][3];

		if (w < 0.001f)
			return false;

		float x = result_right[0] + view_matrix.m[3][0];
		float y = result_up[0] + view_matrix.m[3][1];

		screen_pos = { (UnityEngine::screen_size.x / 2) * (1.f + x / w), (UnityEngine::screen_size.y / 2) * (1.f - y / w) };

		return true;
	}

	bool WorldToScreen(const Vector3& position, Vector2& output)
	{
		auto camera = Camera::get_main();

		if (!IsAddressValid(camera))
		{
			return false;
		}

		return camera->WorldToScreen(position, output);
	}

	bool Camera::WorldToScreen2(const Vector3& position, Vector3& output)
	{
		if (!IsAddressValid(view))
		{
			return false;
		}

		const auto matrix = view->viewMatrix;
		const auto translation = matrix.GetColumn(3);

		const auto w = translation.Dot(position) + matrix[3][3];

		if (w < 0.098f)
		{
			return false;
		}

		const auto right = matrix.GetColumn(0);
		const auto up = matrix.GetColumn(1);

		const auto x = right.Dot(position) + matrix[3][0];
		const auto y = up.Dot(position) + matrix[3][1];

		output[0] = (UnityEngine::Screen::get_width() * 0.5f) * (1.f + (x / w));
		output[1] = (UnityEngine::Screen::get_height() * 0.5f) * (1.f - (y / w));

		return true;
	}


	bool WorldToScreen2(const Vector3& position, Vector3& output)
	{
		auto camera = Camera::get_current();

		if (!IsAddressValid(camera))
		{
			return false;
		}

		return camera->WorldToScreen2(position, output);
	}

	void Object::DontDestroyOnLoad(Object* targ)
	{
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DontDestroyOnLoad"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, targ);
		}


		return;
	}

	Material* Renderer::material() {
		if(!IsAddressValid(this)) return nullptr;
		const auto get_component = reinterpret_cast<Material * (*)(Renderer*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("get_material"), 0)));
		return Call<Material*>((uintptr_t)get_component, this);
	}

	void Renderer::set_material(Material* value) {
		if(!IsAddressValid(this)) return;
		const auto get_component = reinterpret_cast<void* (*)(Renderer*, Material*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("set_material"), 1)));
		return Call<void>((uintptr_t)get_component, this, value);
	}

	void AssetBundle::Unload(bool all)
	{
		if(!IsAddressValid(this))return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Unload"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, all);
		}
		else
		{

			return;
		}
	}

	AssetBundle* AssetBundle::LoadFromMemory_Internal(FPSystem::c_system_array<FPSystem::Byte*>* assetBundle, uint32_t CRC, uint64_t offset) {
		auto load_from_memory_internal = reinterpret_cast<AssetBundle * (*)(FPSystem::c_system_array<FPSystem::Byte*>*assetBundle, uint32_t CRC, uint64_t offset)>(CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.AssetBundle::LoadFromMemory_Internal")));
		return load_from_memory_internal(assetBundle, CRC, offset);
	}



	const char* Component::class_name() {
		if(!IsAddressValid(this)) return XS("");
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return XS("");
		return *reinterpret_cast<char**>(oc + 0x10);
	}

	uint64_t Component::class_name_hash() {
		if(!IsAddressValid(this)) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		char* name = *reinterpret_cast<char**>(oc + 0x10);
		auto hashed = Hash(name, true);
		return hashed;
	}

	FPSystem::Array<Renderer*>* Component::GetComponentsInChildren(FPSystem::Type* type) {
		if (!this || !type) return nullptr;
		const auto get_component = reinterpret_cast<Renderer * (*)(Renderer*, FPSystem::Type*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetComponentsInChildren"), 1)));
		return Call<FPSystem::Array<Renderer*>*>((uintptr_t)get_component, this, type);
	}


	void Physics::IgnoreLayerCollision(int layer1, int layer2, bool ignore) {

		static uint64_t IgnoreLayerCollisionAddress = 0;
		if (!IgnoreLayerCollisionAddress)
			IgnoreLayerCollisionAddress = (uint64_t)CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.Physics::IgnoreLayerCollision"));

		return reinterpret_cast<void(*)(int, int, bool)>(IgnoreLayerCollisionAddress)(layer1, layer2, ignore);
	}

	bool Physics::CheckCapsule(Vector3 start, Vector3 end, float radius, int layerMask, RustStructs::QueryTriggerInteraction triggerInteraction) {
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CheckCapsule"), 5);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<bool>(procedure, start, end, radius, layerMask, triggerInteraction);
		}
		else
		{

			return false;
		}
	}

	GUISkin* DDraw::Arrow(Vector3 vPos, Vector3 vPosB, float headSize, Color color, float fDuration)
	{
		const auto get_skin = reinterpret_cast<GUISkin * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("DDraw")), HASH("Arrow"), 7)));
		return Call<GUISkin*>(ToAddress(get_skin), vPos, vPosB, headSize, color, fDuration, false, false);
	}


	void DDraw::Sphere(Vector3 vPos, float fRadius, Color color, float fDuration, bool distanceFade)
	{
		const auto get_skin = reinterpret_cast<GUISkin * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("DDraw")), HASH("Sphere"), 6)));
		return Call<void>(ToAddress(get_skin), vPos, fRadius, color, fDuration, distanceFade, false);
	}


	void DDraw::Line(Vector3 vPos, Vector3 vPosB, Color color, float fDuration, bool fade, bool ztest)
	{
		const auto get_skin = reinterpret_cast<GUISkin * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("DDraw")), HASH("Line"), 6)));
		if (!get_skin)
			return;

		return Call<void>(ToAddress(get_skin), vPos, vPosB, color, fDuration, fade, ztest);
	}

	void DDraw::Capsule(Vector3 pos, Vector4 rotation, float fRadius, float fHeight, Color color, float fDuration, bool distanceFade)
	{
		const auto get_skin = reinterpret_cast<GUISkin * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("DDraw")), HASH("Capsule"), 7)));
		if (!get_skin)
			return;

		return Call<void>(ToAddress(get_skin), pos, rotation, fRadius, fHeight, color, fDuration, distanceFade);
	}

	void DDraw::Text(const char* text, Vector3 vPos, Color color, float fDuration)
	{
		const auto get_skin = reinterpret_cast<GUISkin * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("DDraw")), HASH("Text"), 6)));
		return Call<void>(ToAddress(get_skin), CIl2Cpp::il2cpp_string_new(text), vPos, color, fDuration, 1.f, false);
	}

	void DDraw::SphereGizmo(Vector3 vPos, float fRadius, Color color, float fDuration, bool distanceFade, bool ztest)
	{
		const auto get_skin = reinterpret_cast<GUISkin * (*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("DDraw")), HASH("SphereGizmo"), 6)));
		return Call<void>(ToAddress(get_skin), vPos, fRadius, color, fDuration, distanceFade, ztest);
	}

	auto CapsuleCollider::get_height() -> float {
		if(!IsAddressValid(this)) return 0.f;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_height"), 0);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<float>(procedure, this);
		}


		return 0.f;
	}

	auto CapsuleCollider::set_radius(float value) -> void {
		if(!IsAddressValid(this)) return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_radius"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call< void>(procedure, this, value);
		}


		return;
	}

	void Rigidbody::set_velocity(Vector3 vel)
	{
		if(!IsAddressValid(this)) return;
		static uintptr_t procedure = 0;
		if (!IsAddressValid(procedure))
		{
			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_velocity"), 1);
			if (IsAddressValid(method))
			{
				procedure = ToAddress(method->methodPointer);
			}
		}

		if (IsAddressValid(procedure))
		{
			return Call<void>(procedure, this, vel);
		}


		return;
	}
}