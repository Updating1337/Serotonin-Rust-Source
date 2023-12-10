#pragma once
#include "../../Includes/includes.hpp"
#include "../System/System.hpp"
#include "../RustStructs.h"
#include "../../CRT/math.hpp"
#include "../../Includes/settings.hpp"

#define powFFFFFFFFFFFFFFFFFFFFFF(n) (n)*(n)
#define CIRCLE_AUTO_SEGMENT_MIN 4
#define CIRCLE_AUTO_SEGMENT_MAX 512
#define CIRCLE_AUTO_SEGMENT_MAXERROR 0.3f
#define CLAMP(val, min, max) ((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val))
#define ROUNDUP_TO_EVEN(_V) ((((_V) + 1) / 2) * 2)

namespace UnityEngine {
	IL2CPP_NAME_SPACE("UnityEngine");

	constexpr auto PiRadians = static_cast<float>(3.1415926535897932);
	constexpr auto PiDegrees = static_cast<float>(180.0);

	struct Vector2;
	struct Vector3;
	struct Bounds;
	struct Matrix4x4;

	struct Object;
	struct Component;
	struct Behaviour;
	struct MonoBehaviour;
	struct Transform;
	struct GameObject;
	struct Camera;
	struct Material;
	struct Input;

	class Vector2
	{
	public:
		Vector2();
		Vector2(float vector_x, float vector_y);
		Vector2(const Vector2& vector);

	public:
		float Dot(const Vector2& vector) const;

		float LengthSquared() const;
		float Length() const;

		float DistanceSquared(const Vector2& vector) const;
		float Distance(const Vector2& vector) const;

		float Normalize();

		float distance_2d(Vector2 input) {
			return Math::sqrtf(Math::powf(x - input.x, 2) + Math::powf(y - input.y, 2));
		}
		inline Vector2 normalize()
		{
			if (x > 89.f)
				x -= 180.f;
			else if (x < -89.f)
				x += 180.f;

			while (y < -180.0f)
				y += 360.0f;

			while (y > 180.0f)
				y -= 360.0f;

			return *this;
		}

	public:
		Vector2 Normalized();
		Vector2 MemoryAimNormalize();

	public:
		float operator[](std::size_t index) const;
		float& operator[](std::size_t index);

	public:
		Vector2& operator=(const Vector2& vector);

	public:
		Vector2& operator+=(float value);
		Vector2& operator-=(float value);
		Vector2& operator*=(float value);
		Vector2& operator/=(float value);

		Vector2& operator+=(const Vector2& vector);
		Vector2& operator-=(const Vector2& vector);
		Vector2& operator*=(const Vector2& vector);
		Vector2& operator/=(const Vector2& vector);

	public:
		Vector2 operator+(float value) const;
		Vector2 operator-(float value) const;
		Vector2 operator*(float value) const;
		Vector2 operator/(float value) const;

		Vector2 operator+(const Vector2& vector) const;
		Vector2 operator-(const Vector2& vector) const;
		Vector2 operator*(const Vector2& vector) const;
		Vector2 operator/(const Vector2& vector) const;
		bool operator==(const Vector2& input) const
		{
			return x == input.x && y == input.y;
		}
		bool IsZero() const
		{
			return (x == 0.f &&
				y == 0.f);
		}
	public:
		float x = 0.f;	// 0x0000
		float y = 0.f;	// 0x0004
	};

	struct Vector3
	{
		Vector3();
		Vector3(float vector_x, float vector_y, float vector_z);
		Vector3(const Vector3& vector);

		float Dot(const Vector3& vector) const;
		Vector3 operator/(float fInput) const;
		float Length() const;
		float Length2D() const;

		float dot(const Vector3& vector)
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}

		float length()
		{
			return Math::my_sqrt(dot(*this));
		}

		static inline bool IsNaN(float f)
		{
			return (*(int*)(&f) & 2147483647) > 2139095040;
		}

		static inline bool IsInfinity(float f)
		{
			return (*(int*)(&f) & 2147483647) == 2139095040;
		}

		static inline bool IsNaNOrInfinity(Vector3 v)
		{
			return IsNaN(v.x) || IsNaN(v.y) || IsNaN(v.z) || IsInfinity(v.x) || IsInfinity(v.y) || IsInfinity(v.z);
		}

		Vector3 Cross(Vector3 rhs)
		{
			return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
		}

		static float Clamp01(float value)
		{
			if (value < 0.f)
				return 0.f;
			else if (value > 1.f)
				return 1.f;
			else
				return value;
		}
		static float InverseLerp(float a, float b, float value)
		{
			float result;
			if (a != b)
			{
				result = Clamp01((value - a) / (b - a));
			}
			else
			{
				result = 0.f;
			}
			return result;
		}
		Vector3 lerp(Vector3 v, float x, bool clamp = true)
		{
			auto delta = (v - *this);
			if (clamp)
				delta.clamp();

			auto result = (*this + delta * x);
			if (clamp)
				result.clamp();

			return result;
		}

		static float Distance(Vector3 a, Vector3 b)
		{
			float num = a.x - b.x;
			float num2 = a.y - b.y;
			float num3 = a.z - b.z;
			return (float)Math::sqrtf((double)(num * num + num2 * num2 + num3 * num3));
		}

		static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
		{
			float num = target.x - current.x;
			float num2 = target.y - current.y;
			float num3 = target.z - current.z;
			float num4 = num * num + num2 * num2 + num3 * num3;
			Vector3 result;
			if (num4 == 0.f || num4 <= maxDistanceDelta * maxDistanceDelta)
			{
				result = target;
			}
			else
			{
				float num5 = (float)Math::sqrtf((double)num4);
				result = Vector3(current.x + num / num5 * maxDistanceDelta, current.y + num2 / num5 * maxDistanceDelta, current.z + num3 / num5 * maxDistanceDelta);
			}
			return result;
		}

		static Vector3 Lerp(Vector3 a, Vector3 b, float t)
		{
			t = Clamp01(t);
			return Vector3(
				a.x + (b.x - a.x) * t,
				a.y + (b.y - a.y) * t,
				a.z + (b.z - a.z) * t
			);
		}
		static Vector3 move_towards(Vector3 current, Vector3 target, float maxDistanceDelta)
		{
			float toVector_x = target.x - current.x;
			float toVector_y = target.y - current.y;
			float toVector_z = target.z - current.z;

			float sqdist = toVector_x * toVector_x + toVector_y * toVector_y + toVector_z * toVector_z;

			if (sqdist == 0 || (maxDistanceDelta >= 0 && sqdist <= maxDistanceDelta * maxDistanceDelta))
				return target;
			auto dist = (float)Math::my_sqrt(sqdist);

			return Vector3(current.x + toVector_x / dist * maxDistanceDelta,
				current.y + toVector_y / dist * maxDistanceDelta,
				current.z + toVector_z / dist * maxDistanceDelta);
		}
		template<typename T>
		T get_remainder(T val, T min, T max)
		{
			while (val > max)
				val -= max * 2;
			while (val < min)
				val += max * 2;
			return val;
		}

		static Vector3 XZ3D(Vector3 v)
		{
			return Vector3(v.x, 0.f, v.z);
		}
		void angle_vectors(Vector3* forward, Vector3* right, Vector3* up)
		{
			float sp, sy, cp, cy, sr, cr;

			constexpr auto PI = 3.14159265358979323846;
			sy = Math::sinf(y / 180.f * (float)PI);
			cy = Math::cosf(y / 180.f * (float)PI);

			sp = Math::sinf(x / 180.f * (float)PI);
			cp = Math::cosf(x / 180.f * (float)PI);

			sr = 0.f;
			cr = 1.f;

			if (forward) {
				*forward = { cp * cy, -sp, cp * sy };
			}

			if (right) {
				right->x = cp * sy;
				right->y = (cr * sp * sy + -sr * cy);
				right->z = (sr * sp * sy + cr * cy);
			}

			if (up) {
				up->x = (cr * sp * cy + -sr * -sy);
				up->y = cr * cp;
				up->z = (cr * sp * sy + -sr * cy);
			}
		}

		Vector3 clamp()
		{
			constexpr auto yaw_limit = static_cast<float>(180);
			constexpr auto pitch_limit = static_cast<float>(90);

			y = get_remainder(y, -yaw_limit, yaw_limit);
			x = get_remainder(x, -pitch_limit, pitch_limit);

			/*if ( x > 180 )
				x -= 360;
			else if ( x < -180 )
				x += 360;

			if ( y > 180 )
				y -= 360;
			else if ( y < -180 )
				y += 360;

			if ( x < -89 )
				x = -89;

			if ( x > 89 )
				x = 89;

			while ( y < -180 )
				y += 360;

			while ( y > 180 )
				y -= 360;

			z = 0;*/

			if (x != x)
				x = 0;
			if (y != y)
				y = 0;
			if (z != z)
				z = 0;

			return *this;
		}



		float Distance(const Vector3& vector) const;
		float Distance2D(const Vector3& vector) const;
		float Magnitude();
		float Normalize();
		Vector3 Normalized() const;
		float Magnitude2D();
		Vector3 UnityNormalize();
		bool IsZero() const;
		float UnityMagnitude();
		Vector3 ToVector() const;
		Vector3 ToEulerAngles() const;

		float get_3d_dist(const Vector3& Dst);
		float operator[](std::size_t index) const;
		float& operator[](std::size_t index);

		Vector3 operator-() const;

		Vector3& operator-=(const Vector3& vInput);

		Vector3& operator+=(const Vector3& vInput);
		Vector3& operator*=(const Vector3& vInput);
		Vector3& operator*=(float vInput);
		Vector3 operator*(float fInput) const;
		Vector3 operator+(const Vector3& vector) const;
		Vector3 operator-(const Vector3& vector) const;
		Vector3 operator*(const Vector3& vector) const;
		Vector3 operator/(const Vector3& vector) const;
		bool operator!=(const Vector3& vInput) const;
		bool operator==(const Vector3& input) const
		{
			return x == input.x && y == input.y && z == input.z;
		}

		Vector3& operator/=(const Vector3& vInput);

		Vector3& operator/=(float fInput);

		Vector3 Scale(const float times) const;

		static Vector3 Zero;

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		template<typename genType>
		static bool epsilonEqual(genType const& x, genType const& y, genType const& epsilon)
		{
			genType diff = x - y;
			return Math::abs(diff) <= epsilon;
		}

		static float Clamp(float value, float min, float max)
		{
			bool flag = value < min;
			if (flag)
			{
				value = min;
			}
			else
			{
				bool flag2 = value > max;
				if (flag2)
				{
					value = max;
				}
			}
			return value;
		}

		Vector3 normalizeeee()
		{
			Vector3 out = *this;
			auto l = length();
			if (l == 0)
				return *this;
			;
			out.x /= l;
			out.y /= l;
			out.z /= l;
			return out;
		}

		float distanceeee(const Vector3& vector)
		{
			return Math::my_sqrt(
				(x - vector.x) * (x - vector.x) +
				(y - vector.y) * (y - vector.y) +
				(z - vector.z) * (z - vector.z));
		}

		static Vector3 Forward;
		static Vector3 Back;
	};

	inline Vector2 screen_size = { 0.f,0.f };

	inline float FlipVertical(float y)
	{
		return screen_size.y - y;
	}

	struct RaycastHit // TypeDefIndex: 3913
	{
		// Fields
		Vector3 m_Point; // 0x0
		Vector3 m_Normal; // 0xC
		uintptr_t m_FaceID; // 0x18
		float m_Distance; // 0x1C
		Vector2 m_UV; // 0x20
		int m_Collider; // 0x28
	};

	inline float ToRadians(float degrees)
	{
		return (degrees * (PiRadians / PiDegrees));
	}

	class Vector4
	{
	public:
		Vector4()
		{
			x = y = z = w = 0.f;
		}

		Vector4(float fx, float fy, float fz, float fw)
		{
			x = fx;
			y = fy;
			z = fz;
			w = fw;
		}

		static Vector3 QuatMult(Vector4 rotation, Vector3 point)
		{
			float num = rotation.x * 2.f;
			float num2 = rotation.y * 2.f;
			float num3 = rotation.z * 2.f;
			float num4 = rotation.x * num;
			float num5 = rotation.y * num2;
			float num6 = rotation.z * num3;
			float num7 = rotation.x * num2;
			float num8 = rotation.x * num3;
			float num9 = rotation.y * num3;
			float num10 = rotation.w * num;
			float num11 = rotation.w * num2;
			float num12 = rotation.w * num3;
			Vector3 result;
			result.x = (1.f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
			result.y = (num7 + num12) * point.x + (1.f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
			result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.f - (num4 + num5)) * point.z;
			return result;
		}

		float x, y, z, w;

		Vector4 operator+(const Vector4& input) const
		{
			return Vector4{ x + input.x, y + input.y, z + input.z, w + input.w };
		}

		Vector4 operator-(const Vector4& input) const
		{
			return Vector4{ x - input.x, y - input.y, z - input.z, w - input.w };
		}

		Vector4 operator/(float input) const
		{
			return Vector4{ x / input, y / input, z / input, w / input };
		}

		Vector4 operator*(float input) const
		{
			return Vector4{ x * input, y * input, z * input, w * input };
		}

		Vector4& operator-=(const Vector4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;

			return *this;
		}

		Vector4& operator/=(float input)
		{
			x /= input;
			y /= input;
			z /= input;
			w /= input;
			return *this;
		}

		Vector4& operator*=(float input)
		{
			x *= input;
			y *= input;
			z *= input;
			w *= input;
			return *this;
		}

		bool operator==(const Vector4& input) const
		{
			return x == input.x && y == input.y && z == input.z && w == input.w;
		}

		static Vector4 QuaternionLookRotation(Vector3 forward, Vector3 up)
		{

			Vector3 vector = forward.UnityNormalize();
			Vector3 vector2 = (up).Cross(vector).UnityNormalize();
			Vector3 vector3 = (vector).Cross(vector2);
			auto m00 = vector2.x;
			auto m01 = vector2.y;
			auto m02 = vector2.z;
			auto m10 = vector3.x;
			auto m11 = vector3.y;
			auto m12 = vector3.z;
			auto m20 = vector.x;
			auto m21 = vector.y;
			auto m22 = vector.z;


			float num8 = (m00 + m11) + m22;
			auto quaternion = Vector4();
			if (num8 > 0.f)
			{
				auto num = (float)Math::sqrtf(num8 + 1.f);
				quaternion.w = num * 0.5f;
				num = 0.5f / num;
				quaternion.x = (m12 - m21) * num;
				quaternion.y = (m20 - m02) * num;
				quaternion.z = (m01 - m10) * num;
				return quaternion;
			}
			if ((m00 >= m11) && (m00 >= m22))
			{
				auto num7 = (float)Math::sqrtf(((1.f + m00) - m11) - m22);
				auto num4 = 0.5f / num7;
				quaternion.x = 0.5f * num7;
				quaternion.y = (m01 + m10) * num4;
				quaternion.z = (m02 + m20) * num4;
				quaternion.w = (m12 - m21) * num4;
				return quaternion;
			}
			if (m11 > m22)
			{
				auto num6 = (float)Math::sqrtf(((1.f + m11) - m00) - m22);
				auto num3 = 0.5f / num6;
				quaternion.x = (m10 + m01) * num3;
				quaternion.y = 0.5f * num6;
				quaternion.z = (m21 + m12) * num3;
				quaternion.w = (m20 - m02) * num3;
				return quaternion;
			}
			auto num5 = (float)Math::sqrtf(((1.f + m22) - m00) - m11);
			auto num2 = 0.5f / num5;
			quaternion.x = (m20 + m02) * num2;
			quaternion.y = (m21 + m12) * num2;
			quaternion.z = 0.5f * num5;
			quaternion.w = (m01 - m10) * num2;
			return quaternion;
		}


		Vector3 Multiply(CONST Vector3& Point)
		{
			float num = x * 2.00f;
			float num2 = y * 2.00f;
			float num3 = z * 2.00f;
			float num4 = x * num;
			float num5 = y * num2;
			float num6 = z * num3;
			float num7 = x * num2;
			float num8 = x * num3;
			float num9 = y * num3;
			float num10 = w * num;
			float num11 = w * num2;
			float num12 = w * num3;

			Vector3 result;
			result.x = (1.00f - (num5 + num6)) * Point.x +
				(num7 - num12) * Point.y + (num8 + num11) * Point.z;
			result.y = (num7 + num12) * Point.x +
				(1.00f - (num4 + num6)) * Point.y +
				(num9 - num10) * Point.z;
			result.z = (num8 - num11) * Point.x + (num9 + num10) * Point.y +
				(1.00f - (num4 + num5)) * Point.z;
			return result;
		}
		void make_absolute()
		{
			x = Math::abs(x);
			y = Math::abs(y);
			z = Math::abs(z);
			w = Math::abs(w);
		}

		float length_sqr() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}

		float length() const
		{
			return Math::sqrtf(length_sqr());
		}

		float length_2d() const
		{
			return Math::sqrtf((x * x) + (y * y));
		}

		Vector4 normalized() const
		{
			return { x / length(), y / length(), z / length(), w / length() };
		}

		float dot_product(Vector4 input) const
		{
			return (x * input.x) + (y * input.y) + (z * input.z) + (w * input.w);
		}

		float distance(Vector4 input) const
		{
			return (*this - input).length();
		}

		float distance_2d(Vector4 input) const
		{
			return (*this - input).length_2d();
		}


		bool empty() const
		{
			return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
		}
	};

	struct Bounds
	{
		Vector3 m_Center = { };		// 0x0000
		Vector3 m_Extents = { };	// 0x000C
	};

	class Quaternion {
	public:
		float x, y, z, w;

		Quaternion() {
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 0.0f;
		}

		Quaternion(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Quaternion operator*(Quaternion rhs) {
			return Quaternion(
				this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y,
				this->w * rhs.y + this->y * rhs.w + this->z * rhs.x - this->x * rhs.z,
				this->w * rhs.z + this->z * rhs.w + this->x * rhs.y - this->y * rhs.x,
				this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z
			);
		}

		float Dot(Quaternion b) {
			return x * x + y * y + z * z + w * w;
		}

		Vector3 operator*(Vector3 point) {
			float num = this->x * 2.f;
			float num2 = this->y * 2.f;
			float num3 = this->z * 2.f;
			float num4 = this->x * num;
			float num5 = this->y * num2;
			float num6 = this->z * num3;
			float num7 = this->x * num2;
			float num8 = this->x * num3;
			float num9 = this->y * num3;
			float num10 = this->w * num;
			float num11 = this->w * num2;
			float num12 = this->w * num3;
			Vector3 result;
			result.x = (1.f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
			result.y = (num7 + num12) * point.x + (1.f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
			result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.f - (num4 + num5)) * point.z;
			return result;
		}
	};

	struct Object : Il2CppObject
	{
		bool IsA(const Il2CppClass* object);

		IL2CPP_CLASS("Object");

		IL2CPP_FIELD(uintptr_t, m_CachedPtr);
		IL2CPP_PROPERTY(FPSystem::String*, name);

		static void DestroyImmediate(Object* object)
		{
			if (!object)
				return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DestroyImmediate"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, object);
			}


			return;
		}

		static void Destroy(Object* object)
		{
			if (!object)
				return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Destroy"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, object);
			}


			return;
		}


		void set_active(bool value)
		{
			if(!IsAddressValid(this))return;
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_active"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, value);
			}


			return;
		}

		static Object* Instantiate(Object* Original, Vector3 Position, Vector4 Rotation)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Internal_InstantiateSingle"), 3);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<Object*>(procedure, Original, Position, Rotation);
			}


			return {};
		}

		void set_name(const char* str)
		{
			if(!IsAddressValid(this))return;
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_name"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(str));
			}


			return;
		}

		static void DontDestroyOnLoad(Object* targ);

		static bool IsNativeObjectAlive(Object* objvc)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("IsNativeObjectAlive"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, objvc);
			}


			return false;
		}

		/*	bool IsNativeObjectAlive()
			{
				auto load_from_memory_internal = reinterpret_cast<bool * (*)(Object*)>(CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.Object::IsNativeObjectAlive")));
				return load_from_memory_internal(this);
			}*/
	};

	struct AssetBundle : Il2CppObject {
		IL2CPP_CLASS("AssetBundle");

		template<typename T = uintptr_t>
		T* LoadAsset(const char* name, Il2CppType* type) {
			auto _this = ToAddress(this);
			auto load_from_memory_internal = reinterpret_cast<T * (*)(AssetBundle*, Il2CppString*, Il2CppType*)>(CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.AssetBundle::LoadAsset_Internal")));
			return load_from_memory_internal(this, CIl2Cpp::il2cpp_string_new(name), type);
		}
		static AssetBundle* LoadFromMemory_Internal(FPSystem::c_system_array<FPSystem::Byte*>* assetBundle, uint32_t CRC, uint64_t offset);
		void Unload(bool all);


		static AssetBundle* LoadFromFile_Internal(const char* a1, int a2, int a3)
		{
			auto load_from_memory_internal = reinterpret_cast<AssetBundle * (*)(Il2CppString*, uint32_t CRC, uint64_t offset)>(CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.AssetBundle::LoadFromFile_Internal")));
			return load_from_memory_internal(CIl2Cpp::il2cpp_string_new(a1), a2, a3);
		}
	};

	struct JsonUtility : Il2CppObject {
		IL2CPP_CLASS("JsonUtility");


		template<typename T = GameObject>
		static T* FromJson(const char* name, FPSystem::Type* type) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("FromJson"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<T*>(procedure, CIl2Cpp::il2cpp_string_new(name), type);
			}
			else
			{

				return {};
			}
		}
	};

	struct Shader : Il2CppObject {
		IL2CPP_CLASS("Shader");

		static Shader* Find(char* name) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Find"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<Shader*>(procedure, CIl2Cpp::il2cpp_string_new(name));
			}
			else
			{

				return 0;
			}
		}
		static int PropertyToID(char* name) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("PropertyToID"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<int>(procedure, CIl2Cpp::il2cpp_string_new(name));
			}
			else
			{

				return 0;
			}
		}
	};


	struct Material : Object
	{
		IL2CPP_CLASS("Material");

		void SetColor(FPSystem::String* proper, Color value) {
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetColor"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				Call<void>(procedure, this, proper, value);
			}
			else
			{

				return;
			}
		}
		bool SetPass(int value)
		{
			const auto set_int = reinterpret_cast<bool (*)(Material*, int)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("SetPass"), 1)));
			return set_int(this, value);
		}

		inline static void CreateWithShader(Material* a1, Shader* a2) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CreateWithShader"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);

				}
			}

			if ((procedure))
			{
				Call<void>(procedure, a1, a2);
			}
			else
			{

				return;
			}
		}
		void SetColor(char* proper, Color value) {
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetColor"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(proper), value);
			}
			else
			{

				return;
			}
		}
		void SetInt(char* name, int value) {
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetInt"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(name), value);
			}
			else
			{

				return;
			}
		}
		void SetFloat(char* name, float value) {
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetFloat"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(name), value);
			}
			else
			{

				return;
			}
		}
		Shader* shader() {
			if(!IsAddressValid(this)) return nullptr;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_shader"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<Shader*>(procedure, this);
			}
			else
			{

				return nullptr;
			}
		}
		void set_shader(Shader* val) {
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_shader"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				Call<void>(procedure, this, val);
			}
			else
			{

				return;
			}
		}
	};

	//struct RenderSettings : Object
	//{
	//	IL2CPP_CLASS("RenderSettings");

	//	IL2CPP_STATIC_FIELD(Material*, skybox);


	//	static Material* get_skybox()
	//	{
	//		static uintptr_t procedure = 0;
	//		if (!(procedure))
	//		{
	//			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_skybox"), 0);
	//			if ((method))
	//			{
	//				procedure = ToAddress(method->methodPointer);
	//			}
	//		}

	//		if ((procedure))
	//		{
	//			return Call<Material*>(procedure);
	//		}
	//		else
	//		{
	//			
	//			return {};
	//		}
	//	}

	//	static void SetSkybox(Material* Value)
	//	{
	//		static uintptr_t procedure = 0;
	//		if (!(procedure))
	//		{
	//			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_skybox"), 1);
	//			if ((method))
	//			{
	//				procedure = ToAddress(method->methodPointer);
	//			}
	//		}

	//		if ((procedure))
	//		{
	//			return Call<void>(procedure, Value);
	//		}
	//		else
	//		{
	//			
	//			return;
	//		}
	//	}

	//	static void SetAmbientMode(RustStructs::AmbientMode Value)
	//	{
	//		static uintptr_t procedure = 0;
	//		if (!(procedure))
	//		{
	//			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_ambientMode"), 1);
	//			if ((method))
	//			{
	//				procedure = ToAddress(method->methodPointer);
	//			}
	//		}

	//		if ((procedure))
	//		{
	//			return Call<void>(procedure, Value);
	//		}
	//		else
	//		{
	//			
	//			return;
	//		}
	//	}

	//	static void SetAmbientIntensity(float Value)
	//	{
	//		static uintptr_t procedure = 0;
	//		if (!(procedure))
	//		{
	//			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_ambientIntensity"), 1);
	//			if ((method))
	//			{
	//				procedure = ToAddress(method->methodPointer);
	//			}
	//		}

	//		if ((procedure))
	//		{
	//			return Call<void>(procedure, Value);
	//		}
	//		else
	//		{
	//			
	//			return;
	//		}
	//	}

	//	static void SetAmbientLight(Color Value)
	//	{
	//		static uintptr_t procedure = 0;
	//		if (!(procedure))
	//		{
	//			const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_ambientLight"), 1);
	//			if ((method))
	//			{
	//				procedure = ToAddress(method->methodPointer);
	//			}
	//		}

	//		if ((procedure))
	//		{
	//			return Call<void>(procedure, Value);
	//		}
	//		else
	//		{
	//			
	//			return;
	//		}
	//	}
	//};

	struct GameObject : Object
	{
		IL2CPP_CLASS("GameObject");
		IL2CPP_PROPERTY(Transform*, transform);
		IL2CPP_PROPERTY(std::int32_t, layer);
		IL2CPP_PROPERTY(FPSystem::String*, tag);
		IL2CPP_PROPERTY(GameObject*, gameObject);


		UnityEngine::Component* AddComponent(FPSystem::Type* type);

		template<typename T = GameObject>
		T* GetComponent(FPSystem::Type* type) {
			if (!this || !type) return nullptr;

			const auto get_component = reinterpret_cast<T * (*)(GameObject*, FPSystem::Type*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetComponent"), 1)));
			return Call<T*>((uintptr_t)get_component, this, type);
		}

		void Internal_CreateGameObject(const char* shader)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Internal_CreateGameObject"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(shader));
			}
			else
			{

				return;
			}
		}
	};

	enum AnisotropicFiltering // TypeDefIndex: 10489
	{
		// Fields
		Disable = 0,
		Enable = 1,
		ForceEnable = 2,
	};

	struct Texture : Object
	{
		IL2CPP_CLASS("Texture");

		void set_anisoLevel(int alias)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_anisoLevel"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, alias);
			}
			else
			{

				return;
			}
		}

		void set_mipMapBias(float alias)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_mipMapBias"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, alias);
			}
			else
			{

				return;
			}
		}

		static void set_anisotropicFiltering(AnisotropicFiltering filter)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_anisotropicFiltering"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, filter);
			}
			else
			{

				return;
			}
		}

		int get_width()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_width"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<int>(procedure, this);
			}
			else
			{

				return 0;
			}
		}

		int get_height()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_height"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<int>(procedure, this);
			}
			else
			{

				return 0;
			}
		}


	};
	struct Random : Il2CppObject {
		IL2CPP_CLASS("Random");


		inline static float Range(float a1, float a2) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Range"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<float>(procedure, a1, a2);
			}
			else
			{

				return false;
			}
		}
	};

	struct rect_t
	{
		float x, y, w, h;
		rect_t(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h) { }
		rect_t() : x(0), y(0), w(0), h(0) { }

		auto contains(Vector2 point) -> bool
		{
			return point.x >= x && point.x < (x + w) && point.y >= y && point.y < (y + h);
		}
	};

	struct RenderTexture : Il2CppObject {
		IL2CPP_CLASS("RenderTexture");

		IL2CPP_STATIC_FIELD(RenderTexture*, active);

		IL2CPP_STATIC_PROPERTY(int, width);
		IL2CPP_STATIC_PROPERTY(int, height);

		void _cctor(int width, int height, int dep)
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 3);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, width, height, dep);
			}
			else
			{

				return;
			}

		}

		static RenderTexture* New(int width, int height, int dep)
		{
			uintptr_t Texture2DClass = 0;
			if (!Texture2DClass)
			{
				Texture2DClass = (uintptr_t)CIl2Cpp::FindClass(XS("UnityEngine"), XS("RenderTexture"));
			}
			UnityEngine::RenderTexture* texture2D = reinterpret_cast<UnityEngine::RenderTexture*>(CIl2Cpp::il2cpp_object_new(ToPointer(Texture2DClass)));

			texture2D->_cctor(width, height, dep);
			return texture2D;
		}
	};


	struct Texture2D : Texture
	{
		IL2CPP_CLASS("Texture2D");


		IL2CPP_STATIC_PROPERTY(Texture2D*, whiteTexture);
		IL2CPP_STATIC_PROPERTY(Texture2D*, blackTexture);

		void ReadPixels(rect_t rect, int desx, int desy)
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ReadPixels"), 3);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, rect, desx, desy);
			}
			else
			{

				return;
			}
		}

		void _cctor(int width, int height)
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, width, height);
			}
			else
			{

				return;
			}

		}


		void SetPixel(int width, int height, Color clr)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetPixel"), 3);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, width, height, clr);
			}
			else
			{

				return;
			}
		}

		void Apply()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Apply"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}
		}

		//static Texture2D* _cctor(Texture2D* tex,int width, int height, RustStructs::TextureFormat textureFormat, bool mipChain)
		//{
		//	static uintptr_t procedure = 0;
		//	if (!(procedure))
		//	{
		//		const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 4);
		//		if ((method))
		//		{
		//			procedure = ToAddress(method->methodPointer);
		//		}

		//		printfz("\n procedure2 - %p", procedure);
		//	}

		//	if ((procedure))
		//	{
		//		return Call<Texture2D*>(procedure, tex, width, height, textureFormat, mipChain);
		//	}
		//	else
		//	{
		//		
		//		return;
		//	}
		//}

		static Texture2D* New2()
		{


			uintptr_t Texture2DClass = 0;
			if (!Texture2DClass)
			{
				Texture2DClass = (uintptr_t)CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture2D"));
			}
			UnityEngine::Texture2D* texture2D = reinterpret_cast<UnityEngine::Texture2D*>(CIl2Cpp::il2cpp_object_new(ToPointer(Texture2DClass)));
			return texture2D;
		}
		static Texture2D* New(int width, int height)
		{


			uintptr_t Texture2DClass = 0;
			if (!Texture2DClass)
			{
				Texture2DClass = (uintptr_t)CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture2D"));
			}
			UnityEngine::Texture2D* texture2D = reinterpret_cast<UnityEngine::Texture2D*>(CIl2Cpp::il2cpp_object_new(ToPointer(Texture2DClass)));

			texture2D->_cctor(width, height);
			return texture2D;
		}



		Texture2D* FillTextureWithColor(Texture2D* originalTexture, Color color)
		{
			if (!originalTexture)
				return {};

			Texture2D* newTexture = New(originalTexture->get_width(), originalTexture->get_height());

			for (int x = 0; x < originalTexture->get_width(); x++)
			{
				for (int y = 0; y < originalTexture->get_height(); y++)
				{
					newTexture->SetPixel(x, y, color);
				}
			}

			newTexture->Apply();
			return newTexture;
		}


	};

	struct Graphics : Il2CppObject {
		IL2CPP_CLASS("Graphics");


		static void Blit(UnityEngine::Texture* src, UnityEngine::RenderTexture* tex)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Blit"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, src, tex);
			}
			else
			{

				return;
			}
		}
	};


	struct Renderer;
	struct Component : Object
	{
		Vector3 get_positionz();
		IL2CPP_CLASS("Component");

		IL2CPP_PROPERTY(GameObject*, gameObject);


		Transform* get_transform();
		const char* class_name();


		uint64_t class_name_hash();

		template<typename T = Component>
		T* GetComponent(FPSystem::Type* type) {
			if(!IsAddressValid(this)) return nullptr;
			const auto get_component = reinterpret_cast<T * (*)(Component*, FPSystem::Type*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("GetComponent"), 1)));
			return Call<T*>((uintptr_t)get_component, this, type);
		}

		FPSystem::Array<Renderer*>* GetComponentsInChildren(FPSystem::Type* type);


		bool IsEntity()
		{
			if(!IsAddressValid(this))
				return false;

			return !strcmp(this->class_name(), XS("BuildingBlock"))
				|| !strcmp(this->class_name(), XS("StabilityEntity"))
				|| !strcmp(this->class_name(), XS("SimpleBuildingBlock"))
				|| !strcmp(this->class_name(), XS("Door"))
				|| !strcmp(this->class_name(), XS("ShopFront"))
				|| !strcmp(this->class_name(), XS("VehicleSpawner"))
				|| !strcmp(this->class_name(), XS("AnimatedBuildingBlock"))
				|| !strcmp(this->class_name(), XS("ProceduralLift"))
				|| !strcmp(this->class_name(), XS("TreeEntity"))
				|| !strcmp(this->class_name(), XS("Signage"))
				|| !strcmp(this->class_name(), XS("ElectricSwitch"))
				|| !strcmp(this->class_name(), XS("BaseOven"))
				|| !strcmp(this->class_name(), XS("Splitter"));
		}

		bool IsPlayer() {
			if(!IsAddressValid(this)) return false;

			return !strcmp(this->class_name(), XS("BasePlayer")) ||
				!strcmp(this->class_name(), XS("NPCPlayerApex")) ||
				!strcmp(this->class_name(), XS("NPCMurderer")) ||
				!strcmp(this->class_name(), XS("NPCPlayer")) ||
				!strcmp(this->class_name(), XS("HumanNPC")) ||
				!strcmp(this->class_name(), XS("Scientist")) ||
				!strcmp(this->class_name(), XS("TunnelDweller")) ||
				!strcmp(this->class_name(), XS("HTNPlayer")) ||
				!strcmp(this->class_name(), XS("ScientistNPC")) ||
				!strcmp(this->class_name(), XS("NPCShopKeeper"));
		}
	};


	struct Renderer : Il2CppObject
	{
		IL2CPP_CLASS("Renderer");

		Material* material();

		void set_material(Material* value);
	};

	struct Ray {
		Vector3 origin;
		Vector3 dir;
		Ray(Vector3 o, Vector3 d) {
			origin = o;
			dir = d;
		}
	};

	struct Time
	{
		IL2CPP_CLASS("Time");


		IL2CPP_STATIC_PROPERTY(float, timeScale);
		IL2CPP_STATIC_PROPERTY(float, deltaTime);
		IL2CPP_STATIC_PROPERTY(float, fixedTime);
		IL2CPP_STATIC_PROPERTY(float, time);
		IL2CPP_STATIC_PROPERTY(float, realtimeSinceStartup);
		IL2CPP_STATIC_PROPERTY(float, fixedDeltaTime);
		IL2CPP_STATIC_PROPERTY(float, smoothDeltaTime);
		//SPOOF_STATIC_PROPERTY(Vector3, gravity);

		static void set_timeScale(float value) {

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_timeScale"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, value);
			}
			else
			{

				return;
			}
		}
	};


	struct Physics
	{
		IL2CPP_CLASS("Physics");

		IL2CPP_STATIC_PROPERTY(Vector3, gravity);


		static void IgnoreLayerCollision(int layer1, int layer2, bool ignore);
		static bool CheckCapsule(Vector3 start, Vector3 end, float radius, int layerMask, RustStructs::QueryTriggerInteraction triggerInteraction);

		inline static bool Linecast(Vector3 start, Vector3 end, RaycastHit hitInfo, int layerMask)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Linecast"), 4);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, start, end, hitInfo, layerMask);
			}
			else
			{

				return false;
			}
		}

		inline static bool BoxCast(Vector3 center, Vector3 halfExtents, Vector3 direction, UnityEngine::RaycastHit hitInfo, Vector4 orientation, float maxDistance, int layerMask, RustStructs::QueryTriggerInteraction queryTriggerInteraction)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("BoxCast"), 8);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, center, halfExtents, direction, hitInfo, orientation, maxDistance, layerMask, queryTriggerInteraction);
			}
			else
			{

				return false;
			}
		}

		inline static bool SphereCast(Ray ray, float radius, float maxDistance, int layerMask, RustStructs::QueryTriggerInteraction queryTriggerInteraction) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SphereCast"), 5);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, ray, radius, maxDistance, layerMask, queryTriggerInteraction);
			}
			else
			{

				return false;
			}
		}

		inline static bool SphereCast(Ray a1, float a2, float a3, int a4) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SphereCast"), 4);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, a1, a2, a3, a4);
			}
			else
			{

				return false;
			}
		}

		inline static bool Raycast(Ray a1, UnityEngine::RaycastHit hit, float a3, int a4, RustStructs::QueryTriggerInteraction a5) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Raycast"), 5);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, a1, hit, a3, a4, a5);
			}
			else
			{

				return false;
			}
		}

		inline static bool Raycast2(Vector3 origin, Vector3 direction, float maxDistance, int layerMask, RustStructs::QueryTriggerInteraction queryTriggerInteraction) {
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Raycast"), 5);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, origin, direction, maxDistance, layerMask, queryTriggerInteraction);
			}
			else
			{

				return false;
			}
		}


	};

	struct Matrix4x4 : Il2CppObject {
		IL2CPP_CLASS("Matrix4x4");


		Vector3 MultiplyPoint(Vector3 value)
		{
			if(!IsAddressValid(this))
				return Vector3();

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethodFullArgs(HASH("UnityEngine.CoreModule::UnityEngine::Matrix4x4::MultiplyPoint(Vector3): Vector3"));
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<Vector3>(procedure, this, value);
			}


			return Vector3();
		}

		Vector3 MultiplyPoint3x4(Vector3 value)
		{
			if(!IsAddressValid(this))
				return Vector3();

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethodFullArgs(HASH("UnityEngine.CoreModule::UnityEngine::Matrix4x4::MultiplyPoint3x4(Vector3): Vector3"));
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<Vector3>(procedure, this, value);
			}


			return Vector3();
		}
	};

	


	struct VMatrix
	{
		VMatrix()
			: m{ { 0, 0, 0, 0 },
				 { 0, 0, 0, 0 },
				 { 0, 0, 0, 0 },
				 { 0, 0, 0, 0 } }
		{}

		VMatrix(const VMatrix&) = default;

		VMatrix transpose() {
			VMatrix m;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m.m[i][j] = this->m[j][i];

			return m;
		}

		void matrix_identity() {
			memset(this, 0, sizeof(VMatrix));
			m[0][0] = 1.0f;
			m[1][1] = 1.0f;
			m[2][2] = 1.0f;
			m[3][3] = 1.0f;
		}
		Vector3 GetRow(std::size_t index) const
		{
			return { m[index][0], m[index][1], m[index][2] };
		}

		Vector3 GetColumn(std::size_t index) const
		{
			return { m[0][index], m[1][index], m[2][index] };
		}

		Vector3 GetAxis(std::size_t index) const
		{
			return { m[index][0], m[index][1], m[index][2] };
		}
		bool is_empty() {
			if (!m[3][0] && !m[3][1] && !m[3][2] && !m[2][1] && !m[2][0] && !m[2][2])
				return true;

			return false;
		}

		Vector3 operator*(const Vector3& vec) {
			VMatrix m;

			m[3][0] = vec.x;
			m[3][1] = vec.y;
			m[3][2] = vec.z;

			m[0][0] = 1;
			m[1][1] = 1;
			m[2][2] = 1;


			m[0][3] = 0.0f;
			m[1][3] = 0.0f;
			m[2][3] = 0.0f;
			m[3][3] = 1.0f;

			auto result = m * (*this);

			return Vector3{ result[3][0], result[3][1], result[3][2] };
		}

		VMatrix operator*(const VMatrix& _m2) {
			auto _m = *this;

			VMatrix out;
			out[0][0] = _m[0][0] * _m2[0][0] + _m[0][1] * _m2[1][0] + _m[0][2] * _m2[2][0] + _m[0][3] * _m2[3][0];
			out[0][1] = _m[0][0] * _m2[0][1] + _m[0][1] * _m2[1][1] + _m[0][2] * _m2[2][1] + _m[0][3] * _m2[3][1];
			out[0][2] = _m[0][0] * _m2[0][2] + _m[0][1] * _m2[1][2] + _m[0][2] * _m2[2][2] + _m[0][3] * _m2[3][2];
			out[0][3] = _m[0][0] * _m2[0][3] + _m[0][1] * _m2[1][3] + _m[0][2] * _m2[2][3] + _m[0][3] * _m2[3][3];
			out[1][0] = _m[1][0] * _m2[0][0] + _m[1][1] * _m2[1][0] + _m[1][2] * _m2[2][0] + _m[1][3] * _m2[3][0];
			out[1][1] = _m[1][0] * _m2[0][1] + _m[1][1] * _m2[1][1] + _m[1][2] * _m2[2][1] + _m[1][3] * _m2[3][1];
			out[1][2] = _m[1][0] * _m2[0][2] + _m[1][1] * _m2[1][2] + _m[1][2] * _m2[2][2] + _m[1][3] * _m2[3][2];
			out[1][3] = _m[1][0] * _m2[0][3] + _m[1][1] * _m2[1][3] + _m[1][2] * _m2[2][3] + _m[1][3] * _m2[3][3];
			out[2][0] = _m[2][0] * _m2[0][0] + _m[2][1] * _m2[1][0] + _m[2][2] * _m2[2][0] + _m[2][3] * _m2[3][0];
			out[2][1] = _m[2][0] * _m2[0][1] + _m[2][1] * _m2[1][1] + _m[2][2] * _m2[2][1] + _m[2][3] * _m2[3][1];
			out[2][2] = _m[2][0] * _m2[0][2] + _m[2][1] * _m2[1][2] + _m[2][2] * _m2[2][2] + _m[2][3] * _m2[3][2];
			out[2][3] = _m[2][0] * _m2[0][3] + _m[2][1] * _m2[1][3] + _m[2][2] * _m2[2][3] + _m[2][3] * _m2[3][3];
			out[3][0] = _m[3][0] * _m2[0][0] + _m[3][1] * _m2[1][0] + _m[3][2] * _m2[2][0] + _m[3][3] * _m2[3][0];
			out[3][1] = _m[3][0] * _m2[0][1] + _m[3][1] * _m2[1][1] + _m[3][2] * _m2[2][1] + _m[3][3] * _m2[3][1];
			out[3][2] = _m[3][0] * _m2[0][2] + _m[3][1] * _m2[1][2] + _m[3][2] * _m2[2][2] + _m[3][3] * _m2[3][2];
			out[3][3] = _m[3][0] * _m2[0][3] + _m[3][1] * _m2[1][3] + _m[3][2] * _m2[2][3] + _m[3][3] * _m2[3][3];

			return out;
		}


		Vector3 MultiplyPoint(Vector3 point) {
			Vector3 result;
			result.x = m[0][0] * point.x + m[0][1] * point.y + m[0][2] * point.z + m[0][3];
			result.y = m[1][0] * point.x + m[1][1] * point.y + m[1][2] * point.z + m[1][3];
			result.z = m[2][0] * point.x + m[2][1] * point.y + m[2][2] * point.z + m[2][3];
			float num = m[3][0] * point.x + m[3][1] * point.y + m[3][2] * point.z + m[3][3];
			num = 1.0f / num;
			result.x *= num;
			result.y *= num;
			result.z *= num;
			return result;
		}

		float* operator[](size_t i) { return m[i]; }
		const float* operator[](size_t i) const { return m[i]; }

		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};
	};
	struct Transform : Component
	{
		IL2CPP_CLASS("Transform");

		Vector3 get_position();

		//IL2CPP_PROPERTY(Vector3, position);
		IL2CPP_PROPERTY(Vector3, localPosition);
		IL2CPP_PROPERTY(Vector3, eulerAngles);
		IL2CPP_PROPERTY(Vector3, localEulerAngles);
		IL2CPP_PROPERTY(Vector3, right);
		IL2CPP_PROPERTY(Vector3, up);
		IL2CPP_PROPERTY(Vector3, forward);
		IL2CPP_PROPERTY(Vector3, localScale);
		IL2CPP_PROPERTY(Vector4, rotation);

		IL2CPP_PROPERTY(VMatrix*, localToWorldMatrix);


		auto InverseTransformPoint(Vector3 pt) -> Vector3;
		auto InverseTransformDirection(Vector3 pt) -> Vector3;

		Transform* get_parent();
		auto set_position(Vector3 pos) -> void;
		auto set_rotation(Vector4 pos) -> void;
		auto set_localscale(Vector3 amount) -> void;
		bool rotate(Vector3 pos, float engle)
		{
			if(!IsAddressValid(this))return false;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("rotate"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, this, pos, engle);
			}


			return false;
		}
	};

	struct Behaviour : Component
	{
		IL2CPP_CLASS("Behaviour");
	};

	struct MonoBehaviour : Behaviour
	{
		IL2CPP_CLASS("MonoBehaviour");
	};

	struct RenderSettings : Object
	{
		IL2CPP_CLASS("RenderSettings");

		static void set_skybox(UnityEngine::Material* mat)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethodFullArgs(HASH("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_skybox(Material): Void"));
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, mat);
			}
			else
			{

				return;
			}
		}

		static void set_ambientMode(RustStructs::AmbientMode value);
		static void set_ambientIntensity(float value);
		static void set_ambientLight(Color value);
	};

	struct Input : Il2CppObject
	{
		IL2CPP_CLASS("Input");

		static bool GetMouseButton(int a1);
		static Vector3 GetMousePosition();
		static bool GetKey(RustStructs::KeyCode code);
		static bool GetKeyDown(RustStructs::KeyCode code);

		IL2CPP_STATIC_PROPERTY(Vector2, mouseScrollDelta);
	};

	struct Event {
		IL2CPP_CLASS("Event");

		static Event* Current();
		static RustStructs::KeyCode get_keyCode(Event* current);
		Vector2 Delta();
		Vector2 mousePosition();
		RustStructs::EventType Type();

		void Use()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Use"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}
	};

	struct GUIContent;

	struct GUIStyleState : Il2CppObject {
		IL2CPP_CLASS("GUIStyleState");

	};

	struct GUIStyle : Il2CppObject {
		IL2CPP_CLASS("GUIStyle");

		IL2CPP_STATIC_FIELD(GUIStyle*, s_None);
		IL2CPP_FIELD(GUIStyleState*, m_Normal);

		void SetFontSize(int value);
		float GetFontSize();
		static void SetAlignment(GUIStyle* style, int text);
	};

	struct Animator : Il2CppObject {
		IL2CPP_CLASS("Animator");

		void SetFloat(int id, float value)
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = (MethodInfo*)CIl2Cpp::get_method_ptr_with_args((uint64_t)StaticClass(), "SetFloat", "id", 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, id, value);
			}


			return;
		}

		void SetBool(const char* name, bool value)
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetBool"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this,CIl2Cpp::il2cpp_string_new(name), value);
			}


			return;
		}

		void SetTriggerID(int d)
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SetTriggerID"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, d);
			}


			return;
		}

		void set_speed(float speed)
		{
			if(!IsAddressValid(this))
				return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_speed"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, speed);
			}


			return;
		}
	};

	struct GUISkin : Object {
		IL2CPP_CLASS("GUISkin");
		IL2CPP_FIELD(GUIStyle*, m_label);
		IL2CPP_FIELD(uintptr_t, m_Font);
		IL2CPP_FIELD(GUIStyle*, m_box);
		IL2CPP_FIELD(GUIStyle*, m_textArea);

		static GUIStyle* GetLabel();
	};

	class Rect {
	public:
		float x; // 0x10
		float y; // 0x14
		float wid; // 0x18
		float hei; // 0x1C
		Rect(float x, float y/*top left*/, float x_rightsize, float y_downsize) {
			this->x = x;
			this->y = y;
			wid = x_rightsize;
			hei = y_downsize;
		}
		Rect() {
			this->x = 0;
			this->y = 0;
			wid = 0;
			hei = 0;
		}
		bool Contains(Vector2 point)
		{
			return point.x >= x && point.x < (x + wid) && point.y >= y && point.y < (y + hei);
		}
	};


	struct Screen {
		IL2CPP_CLASS("Screen");


		IL2CPP_STATIC_PROPERTY(int, width);
		IL2CPP_STATIC_PROPERTY(int, height);
	};

	struct Sprite : Object {
		IL2CPP_CLASS("Sprite");
		IL2CPP_PROPERTY(Texture2D*, texture);
		IL2CPP_PROPERTY(Rect, rect);

	};

	struct Camera : Behaviour
	{
		struct View
		{
			FIELD_PAD(0x00DC);				// 0x0000
			VMatrix viewMatrix = { };	        // 0x00DC
		};

		View* view = nullptr;					// 0x0018
		bool WorldToScreen2(const Vector3& position, Vector3& output);

		bool WorldToScreen(const Vector3& position, Vector2& screen_pos);
		Vector3 WorldToScreen(Vector3 position);
		IL2CPP_CLASS("Camera");
		IL2CPP_STATIC_PROPERTY(Camera*, main);
		IL2CPP_STATIC_PROPERTY(Camera*, current);
		IL2CPP_PROPERTY(float, fieldOfView);
		//IL2CPP_PROPERTY(Matrix4x4, worldToCameraMatrix);
		//IL2CPP_PROPERTY(Matrix4x4, projectionMatrix);

		static auto viewMatrix() -> VMatrix;
	};

	enum FocusType
	{
		Native,
		Keyboard,
		Passive
	};
	struct ScrollViewState : Il2CppObject {
		Rect position;
		Rect visibleRect;
		Rect viewRect;
		Vector2 scrollPosition;
		bool apply;
	};

	struct GUIUtility : Il2CppObject {
		IL2CPP_CLASS("GUIUtility");

		static ScrollViewState* GetStateObject(FPSystem::Type* type, int controlID)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetStateObject"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<ScrollViewState*>(procedure, type, controlID);
			}


			return {};
		}

		static void CheckOnGUI()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CheckOnGUI"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure);
			}


			return;
		}

		static int GetControlID(int hash, FocusType type)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetControlID"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<int>(procedure, hash, type);
			}


			return 0;
		}
	};

	struct GUIContent;


	struct GUILayout {
		IL2CPP_CLASS("GUILayout");

		static void Label(const char* text)
		{
			Il2CppArray* options = FPSystem::il2cpp_array_new_specific((Il2CppClass*)CIl2Cpp::FindClass("UnityEngine", "GUILayoutOption"), 1u);

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Label"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, CIl2Cpp::il2cpp_string_new(text), options);
			}


			return;
		}

		static FPSystem::String* TextArea(const char* test)
		{

			Il2CppArray* options = FPSystem::il2cpp_array_new_specific((Il2CppClass*)CIl2Cpp::FindClass("UnityEngine", "GUILayoutOption"), 1u);

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("TextArea"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<FPSystem::String*>(procedure, CIl2Cpp::il2cpp_string_new(test), options);
			}


			return nullptr;
		}

		static void BeginHorizontal()
		{

			Il2CppArray* options = FPSystem::il2cpp_array_new_specific((Il2CppClass*)CIl2Cpp::FindClass("UnityEngine", "GUILayoutOption"), 1u);

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("BeginHorizontal"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, options);
			}


			return;
		}

		static void EndHorizontal()
		{

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("EndHorizontal"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure);
			}


			return;
		}


		static void BeginVertical()
		{

			Il2CppArray* options = FPSystem::il2cpp_array_new_specific((Il2CppClass*)CIl2Cpp::FindClass("UnityEngine", "GUILayoutOption"), 1u);

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("BeginVertical"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, options);
			}


			return;
		}
		static void EndVertical()
		{

			Il2CppArray* options = FPSystem::il2cpp_array_new_specific((Il2CppClass*)CIl2Cpp::FindClass("UnityEngine", "GUILayoutOption"), 1u);

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("EndVertical"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, options);
			}


			return;
		}

		static FPSystem::String* DoTextField(const char* text)
		{
			Il2CppArray* options = FPSystem::il2cpp_array_new_specific((Il2CppClass*)CIl2Cpp::FindClass("UnityEngine", "GUILayoutOption"), 1u);

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("TextField"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<FPSystem::String*>(procedure, CIl2Cpp::il2cpp_string_new(text), options);
			}


			return {};
		}

		static void BeginArea(rect_t screenRect)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("BeginArea"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, screenRect);
			}


			return;
		}

		static void EndArea()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("EndArea"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure);
			}


			return;
		}
	};

	struct GUI {
		IL2CPP_CLASS("GUI");

		IL2CPP_STATIC_FIELD(Material*, roundedRectMaterial);
		IL2CPP_STATIC_FIELD(int, s_ScrollviewHash);


		static GUISkin* GetSkin();
		static void SetColor(Color clr);
		static void DrawTexture(UnityEngine::rect_t a1, UnityEngine::Texture2D* a2);
		static void Label(UnityEngine::rect_t position, Unity_String text, uintptr_t style);
		static void LabelTest(UnityEngine::rect_t position, Il2CppString* text, uintptr_t style);

		static void DoTextField(rect_t position, int id, GUIContent* content, bool multiline, int maxLength, GUIStyle* style)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DoTextField"), 6);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, position, id, content, multiline, maxLength, style);
			}


			return;
		}

		static FPSystem::String* PasswordFieldGetStrToShow(const char* a1, const char* a2)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("PasswordFieldGetStrToShow"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<FPSystem::String*>(procedure, CIl2Cpp::il2cpp_string_new(a1), a2);
			}


			return {};
		}

		static void Box(rect_t pos, const char* text)
		{

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Box"), 2);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, pos, CIl2Cpp::il2cpp_string_new(text));
			}


			return;
		}


		static void BeginGroup(UnityEngine::rect_t position, GUIContent* content, GUIStyle* style, Vector2 ScrollOffset)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("BeginGroup"), 4);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, position, content, style, ScrollOffset);
			}


			return;
		}

		static void EndGroup()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("EndGroup"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure);
			}


			return;
		}
	};

	struct GUIContent : GUI {
		IL2CPP_CLASS("GUIContent");

		static uintptr_t Temp(Unity_String lol)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Temp"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<uintptr_t>(procedure, lol);
			}


			return {};
		}
	};

	struct DDraw : Il2CppObject {
		IL2CPP_CLASS("DDraw");

		static GUISkin* Arrow(Vector3 vPos, Vector3 vPosB, float headSize, Color color, float fDuration);
		static void Sphere(Vector3 vPos, float fRadius, Color color, float fDuration, bool distanceFade);
		static void Line(Vector3 vPos, Vector3 vPosB, Color color, float fDuration, bool fade, bool ztest);
		static void Capsule(Vector3 pos, Vector4 rotation, float fRadius, float fHeight, Color color, float fDuration = 0.5, bool distanceFade = true);
		static void Text(const char* text, Vector3 vPos, Color color, float fDuration);
		static void SphereGizmo(Vector3 vPos, float fRadius, Color color, float fDuration, bool distanceFade, bool ztest);
	};

	struct Collider : GameObject {
		IL2CPP_CLASS("Collider");

		bool get_enabled()
		{
			if(!IsAddressValid(this)) return false;
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_enabled"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, this);
			}


			return false;
		}

		void set_enabled(bool value)
		{
			if(!IsAddressValid(this))return;
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_enabled"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, value);
			}


			return;
		}
	};

	struct textcmd_t {
		bool outline;
		Vector2 pos;
		Color clr;
		Color outlineColor;
		Il2CppString* text;
		bool centered;
		bool draw_outlined;
		bool draw_shaded;
		int size;

		textcmd_t() = default;
		textcmd_t(bool a, const Vector2& b, const Color& c, const Color& d, Il2CppString* txt, bool e, bool f, int g) {
			outline = a;
			pos = b;
			clr = c;
			outlineColor = d;
			text = txt;
			draw_outlined = e;
			draw_shaded = f;
			size = g;
		}
	};

	struct menu_textcmd_t {
		bool outline;
		Vector2 pos;
		Color clr;
		Color outlineColor;
		Il2CppString* text;
		bool centered;

		menu_textcmd_t() = default;
		menu_textcmd_t(bool a, const Vector2& b, const Color& c, const Color& d, Il2CppString* txt) {
			outline = a;
			pos = b;
			clr = c;
			outlineColor = d;
			text = txt;
		}
	};

	struct textcmd_t_world {
		bool outline;
		Vector2 pos;
		Color clr;
		Color outlineColor;
		Il2CppString* text;
		bool centered;
		bool draw_outlined;
		bool draw_shaded;
		int size;

		textcmd_t_world() = default;
		textcmd_t_world(bool a, const Vector2& b, const Color& c, const Color& d, Il2CppString* txt, bool e, bool f, int g) {
			outline = a;
			pos = b;
			clr = c;
			outlineColor = d;
			text = txt;
			draw_outlined = e;
			draw_shaded = f;
			size = g;
		}
	};

	struct textcmd_t_screen {
		bool outline;
		Vector2 pos;
		Color clr;
		Color outlineColor;
		Il2CppString* text;
		bool centered;
		bool draw_outlined;
		bool draw_shaded;
		int size;

		textcmd_t_screen() = default;
		textcmd_t_screen(bool a, const Vector2& b, const Color& c, const Color& d, Il2CppString* txt, bool e, bool f, int g) {
			outline = a;
			pos = b;
			clr = c;
			outlineColor = d;
			text = txt;
			draw_outlined = e;
			draw_shaded = f;
			size = g;
		}
	};

	struct textcmd2_t {
		Vector2 pos;
		Vector2 size;
		Texture2D* texture;
		Color backgroundColor;

		textcmd2_t() = default;
		textcmd2_t(Vector2 a, Vector2 b, Texture2D* c, const Color& d) {
			pos = a;
			size = b;
			texture = c;
			backgroundColor = d;
		}
	};

	inline std::list<textcmd_t*> text_buffer;
	inline std::list<textcmd2_t*> icon_buffer;
	inline std::list<menu_textcmd_t*> menu_text_buffer;
	inline std::list<textcmd_t_world*> world_text_buffer;
	inline std::list<textcmd_t_screen*> screen_text_buffer;
	inline UnityEngine::Material* LineMat = nullptr;
	inline UnityEngine::GUIStyle* gui_style = nullptr;
	inline UnityEngine::GUIStyle* menu_gui_style = nullptr;
	inline UnityEngine::GUIStyle* world_gui_style = nullptr;
	inline UnityEngine::GUIStyle* screen_gui_style = nullptr;

	struct GL {
		IL2CPP_CLASS("GL");

		static void Begin(int mode) {
			const auto draw_texture = reinterpret_cast<void(*)(int)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("Begin"), 1)));
			return Call<void>(ToAddress(draw_texture), mode);
		}
		static void End() {
			const auto draw_texture = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("End"), 0)));
			return Call<void>(ToAddress(draw_texture));
		}
		static void Colorz(Color clr) {
			const auto draw_texture = reinterpret_cast<void(*)(Color)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("Color"), 1)));
			return Call<void>(ToAddress(draw_texture), clr);
		}
		static void Vertex3(float x, float y, float z)
		{
			const auto draw_texture = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("Vertex3"), 3)));
			return Call<void>(ToAddress(draw_texture), x, y, z);
		}
		static void PushMatrix() {
			const auto draw_texture = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("PushMatrix"), 0)));
			return Call<void>(ToAddress(draw_texture));
		}
		static void PopMatrix() {
			const auto draw_texture = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("PopMatrix"), 0)));
			return Call<void>(ToAddress(draw_texture));
		}

		static void LoadPixelMatrix() {
			const auto draw_texture = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("LoadPixelMatrix"), 0)));
			return Call<void>(ToAddress(draw_texture));
		}

		static void Vertex(Vector3 zzz) {
			const auto draw_texture = reinterpret_cast<void(*)(Vector3)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(StaticClass(), HASH("Vertex"), 1)));
			return Call<void>(ToAddress(draw_texture), zzz);
		}

		static auto gl_start(int mode) -> void
		{
			if (!LineMat)
			{
				LineMat = (UnityEngine::Material*)CIl2Cpp::il2cpp_object_new((void*)CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material")));
				UnityEngine::Material::CreateWithShader(LineMat, UnityEngine::Shader::Find((XS("Hidden/Internal-Colored"))));
			}

			PushMatrix();
			LineMat->SetPass(0);
			Begin(mode);
		}

		static auto gl_end() -> void
		{
			End();
			PopMatrix();
		}

		static void RectangleFilled(const Vector2& topLeft, const Vector2& bottomRight, const Color& col)
		{
			Begin(RustStructs::GlMode::Quads);

			Colorz(col);

			Vector2 tl = { topLeft.x, FlipVertical(topLeft.y) };
			Vector2 br = { bottomRight.x, FlipVertical(bottomRight.y) };

			Vertex3(tl.x, br.y, 0);
			Vertex3(tl.x, tl.y, 0);
			Vertex3(br.x, tl.y, 0);
			Vertex3(br.x, br.y, 0);

			End();
		}

		static void Rectangle(const Vector2& topLeft, const Vector2& bottomRight, const Color& col)
		{
			Vector2 points[5];

			points[0] = Vector2{ topLeft.x, bottomRight.y };
			points[1] = Vector2{ topLeft.x, topLeft.y };
			points[2] = Vector2{ bottomRight.x, topLeft.y };
			points[3] = Vector2{ bottomRight.x, bottomRight.y };
			points[4] = points[0];

			PolyLine(points, 5, col);
		}

		static void PolyLine(const Vector2* lines, int count, const Color& col)
		{
			Begin(RustStructs::GlMode::Line_Strip);

			Colorz(col);

			for (int i = 0; i < count; i++)
			{
				const Vector2& point = lines[i];
				Vertex3(point.x - 0.5f, FlipVertical(point.y - 0.5), 0);
			}

			End();
		}

		static void Triangle(const Vector2& Pos, const Vector2& Pos1, const Vector2& Pos2, const Color& col)
		{
			Begin(RustStructs::GlMode::Trangles);

			Vertex3(Pos.x, Pos.y, 0);
			Vertex3(Pos1.x, Pos1.y, 0);
			Vertex3(Pos2.x, Pos2.y, 0);

			End();
		}

		static void Line(const Vector2& a, const Vector2& b, const Color& col)
		{
			Vector2 points[] = { a, b };
			PolyLine(points, 2, col);
		}

		static int CircleAutoSegmentCalc(float rad)
		{
			int segments = ROUNDUP_TO_EVEN((int)Math::ceil((float)M_PI / Math::acosf(1.f - min(CIRCLE_AUTO_SEGMENT_MAXERROR, rad) / rad)));
			return CLAMP(segments, CIRCLE_AUTO_SEGMENT_MIN, CIRCLE_AUTO_SEGMENT_MAX);
		}

		static Vector2* CalcCirclePoints(const Vector2& center, float radius, int& segments, float startAngle = 0.f, float endAngle = 360.f)
		{
			float angleSize = endAngle - startAngle;

			if (segments == 0)
				segments = (int)Math::ceil((float)CircleAutoSegmentCalc(radius) * (angleSize / 360.f));

			float startRad = DEG2RAD(startAngle);
			float endRad = DEG2RAD(endAngle);
			float radSize = endRad - startRad;

			static Vector2* points = new Vector2[CIRCLE_AUTO_SEGMENT_MAX + 1];

			for (int i = 0; i <= segments; i++)
			{
				const float a = startRad + ((float)i / (float)segments) * radSize;
				points[i] = Vector2(center.x + (float)Math::cosf(a) * radius, center.y + (float)Math::sinf(a) * radius);
			}

			return points;
		}

		static void Circle(const Vector2& center, float radius, const Color& col, int segments)
		{
			Vector2* points = CalcCirclePoints(center, radius, segments);

			PolyLine(points, segments + 1, col);
		}

		static void CircleFilled(const Vector2& center, float radius, const Color& col, int segments)
		{
			CircleFilledGradient(center, radius, col, col, segments);
		}

		static void CircleFilledGradient(const Vector2& center, float radius, const Color& colCenter, const Color& colOuter, int segments)
		{
			CircleSectionFilledGradient(center, radius, colCenter, colOuter, 0.f, 360.f, segments);
		}

		static void CircleSectionFilledGradient(const Vector2& center, float radius, const Color& colCenter, const Color& colOuter, float start, float end, int segments)
		{
			Vector2* points = CalcCirclePoints(center, radius, segments, start, end);

			Begin(RustStructs::GlMode::Trangles);

			const float centerYFlipped = FlipVertical(center.y);

			for (int i = 0; i < segments; i++)
			{
				Colorz(colOuter);
				Vertex3(points[i].x, FlipVertical(points[i].y), 0);
				Colorz(colOuter);
				Vertex3(points[i + 1].x, FlipVertical(points[i + 1].y), 0);
				Colorz(colCenter);
				Vertex3(center.x, centerYFlipped, 0);
			}

			End();
		}

		static void DrawIcon(const Vector2& pos, const Vector2& size, UnityEngine::Texture2D* texture, Color backgroundColor)
		{
			textcmd2_t* cmd = new textcmd2_t;
			cmd->pos = pos;
			cmd->size = size;
			cmd->texture = texture;
			cmd->backgroundColor = backgroundColor;

			icon_buffer.emplace_back(cmd);
		}

		static void TextOutline(const Vector2& pos, const Color& color, Color outlineColor, const char* text, bool centered, int size = 10, bool outlined = true, bool shaded = false)
		{
			textcmd_t* cmd = new textcmd_t;
			cmd->outline = outlineColor.m_alpha > 0;
			cmd->clr = color;
			cmd->outlineColor = outlineColor;
			cmd->text = CIl2Cpp::il2cpp_string_new(text);
			cmd->pos = pos;
			cmd->centered = centered;
			cmd->size = size;
			cmd->draw_outlined = outlined;
			cmd->draw_shaded = shaded;

			text_buffer.emplace_back(cmd);
		}

		static void TextCenter(const Vector2& centerPos, const char* str, Color color, Color outlineColor, int size, bool outlined = true, bool shaded = false)
		{
			return TextOutline(centerPos, color, outlineColor, str, true, size, outlined, shaded);
		}

		static void WorldTextCenter(const Vector2& centerPos, const char* str, Color color, Color outlineColor, int size, bool outlined = true, bool shaded = false, bool centered = true)
		{
			textcmd_t_world* cmd = new textcmd_t_world;
			cmd->outline = outlineColor.m_alpha > 0;
			cmd->clr = color;
			cmd->outlineColor = outlineColor;
			cmd->text = CIl2Cpp::il2cpp_string_new(str);
			cmd->pos = centerPos;
			cmd->centered = true;
			cmd->size = size;
			cmd->draw_outlined = outlined;
			cmd->draw_shaded = shaded;

			world_text_buffer.emplace_back(cmd);
		}

		static void ScreenTextCenter(const Vector2& centerPos, const char* str, Color color, Color outlineColor, int size, bool outlined = true, bool shaded = false, bool centered = true)
		{
			textcmd_t_screen* cmd = new textcmd_t_screen;
			cmd->outline = outlineColor.m_alpha > 0;
			cmd->clr = color;
			cmd->outlineColor = outlineColor;
			cmd->text = CIl2Cpp::il2cpp_string_new(str);
			cmd->pos = centerPos;
			cmd->centered = true;
			cmd->size = size;
			cmd->draw_outlined = outlined;
			cmd->draw_shaded = shaded;

			screen_text_buffer.emplace_back(cmd);
		}

		static void MenuText(const Vector2& pos, const char* text, const Color& color, Color outlineColor, bool centered)
		{
			menu_textcmd_t* cmd = new menu_textcmd_t;
			cmd->outline = outlineColor.m_alpha > 0;
			cmd->clr = color;
			cmd->outlineColor = outlineColor;
			cmd->text = CIl2Cpp::il2cpp_string_new(text);
			cmd->pos = pos;
			cmd->centered = centered;

			menu_text_buffer.emplace_back(cmd);
		}

		static std::list<textcmd_t*>& get_text_buffer() {
			return text_buffer;
		}

		static std::list<textcmd_t_world*>& get_world_text_buffer() {
			return world_text_buffer;
		}

		static std::list<menu_textcmd_t*>& get_menu_text_buffer() {
			return menu_text_buffer;
		}

		static std::list<textcmd_t_screen*>& get_screen_text_buffer() {
			return screen_text_buffer;
		}

		static std::list<textcmd2_t*>& get_icon_buffer() {
			return icon_buffer;
		}

		static void UnityLabel(const Vector2& pos, Il2CppString* text, UnityEngine::GUIStyle* style) {

			UnityEngine::rect_t rect{ pos.x, pos.y, 400, 20 };

			const auto label = reinterpret_cast<void(*)(UnityEngine::rect_t, Il2CppString*, UnityEngine::GUIStyle*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("UnityEngine"), XS("GUI")), HASH("Label"), 3)));
			if (!label)
				return;

			return Call<void>(ToAddress(label), rect, text, style);
		}

		static void RenderText()
		{
			auto& text_buffer = get_text_buffer();
			auto it = text_buffer.begin();
			while (it != text_buffer.end())
			{
				const auto& entry = *it;
				if (entry->centered)
				{
					UnityEngine::GUIStyle::SetAlignment(gui_style, 0x4);
					entry->pos.x -= 200;
					entry->pos.y -= 12;
				}
				else
					UnityEngine::GUIStyle::SetAlignment(gui_style, 0x0);

				gui_style->SetFontSize(m_settings::ESPFontsize); //FPS?

				if (entry->draw_outlined) {
					UnityEngine::GUI::SetColor(entry->outlineColor);

					UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y + 1), entry->text, gui_style);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y - 1), entry->text, gui_style);

					UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y - 1), entry->text, gui_style);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y + 1), entry->text, gui_style);


					UnityEngine::GUI::SetColor(entry->clr);

					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, gui_style);
				}
				else if (entry->draw_shaded) {
					UnityEngine::GUI::SetColor(entry->outlineColor);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y + 1), entry->text, gui_style);

					UnityEngine::GUI::SetColor(entry->clr);

					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, gui_style);
				}
				else {
					UnityEngine::GUI::SetColor(entry->outlineColor);
					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, gui_style);

					UnityEngine::GUI::SetColor(entry->clr);
					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, gui_style);
				}

				free(entry);
				it = text_buffer.erase(it);
			}
		}

		static void RenderWorldText()
		{
			auto& text_buffer = get_world_text_buffer();
			auto it = text_buffer.begin();
			while (it != text_buffer.end())
			{
				const auto& entry = *it;
				if (entry->centered)
				{
					UnityEngine::GUIStyle::SetAlignment(world_gui_style, 0x4);
					entry->pos.x -= 200;
					entry->pos.y -= 12;
				}
				else
					UnityEngine::GUIStyle::SetAlignment(world_gui_style, 0x0);

				world_gui_style->SetFontSize(m_settings::WorldFontSize); //FPS?

				if (entry->draw_outlined) {
					UnityEngine::GUI::SetColor(entry->outlineColor);

					UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y + 1), entry->text, world_gui_style);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y - 1), entry->text, world_gui_style);

					UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y - 1), entry->text, world_gui_style);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y + 1), entry->text, world_gui_style);


					UnityEngine::GUI::SetColor(entry->clr);

					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, world_gui_style);
				}
				else if (entry->draw_shaded) {
					UnityEngine::GUI::SetColor(entry->outlineColor);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y + 1), entry->text, world_gui_style);

					UnityEngine::GUI::SetColor(entry->clr);

					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, world_gui_style);
				}
				else {
					UnityEngine::GUI::SetColor(entry->outlineColor);
					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, world_gui_style);

					UnityEngine::GUI::SetColor(entry->clr);
					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, world_gui_style);
				}

				free(entry);
				it = text_buffer.erase(it);
			}
		}

		static void RenderScreenText()
		{
			auto& text_buffer = get_screen_text_buffer();
			auto it = text_buffer.begin();
			while (it != text_buffer.end())
			{
				const auto& entry = *it;
				if (entry->centered)
				{
					UnityEngine::GUIStyle::SetAlignment(screen_gui_style, 0x4);
					entry->pos.x -= 200;
					entry->pos.y -= 12;
				}
				else
					UnityEngine::GUIStyle::SetAlignment(screen_gui_style, 0x0);

				screen_gui_style->SetFontSize(10); //FPS?

				if (entry->draw_outlined) {
					UnityEngine::GUI::SetColor(entry->outlineColor);

					UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y + 1), entry->text, screen_gui_style);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y - 1), entry->text, screen_gui_style);

					UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y - 1), entry->text, screen_gui_style);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y + 1), entry->text, screen_gui_style);


					UnityEngine::GUI::SetColor(entry->clr);

					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, screen_gui_style);
				}
				else if (entry->draw_shaded) {
					UnityEngine::GUI::SetColor(entry->outlineColor);
					UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y + 1), entry->text, screen_gui_style);

					UnityEngine::GUI::SetColor(entry->clr);

					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, screen_gui_style);
				}
				else {
					UnityEngine::GUI::SetColor(entry->outlineColor);
					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, screen_gui_style);

					UnityEngine::GUI::SetColor(entry->clr);
					UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, screen_gui_style);
				}

				free(entry);
				it = text_buffer.erase(it);
			}
		}

		static void RenderMenuText()
		{
			auto& text_buffer = get_menu_text_buffer();
			auto it = text_buffer.begin();
			while (it != text_buffer.end())
			{
				const auto& entry = *it;
				if (entry->centered)
				{
					UnityEngine::GUIStyle::SetAlignment(menu_gui_style, 0x4);
					entry->pos.x -= 200;
					entry->pos.y -= 12;
				}
				else
					UnityEngine::GUIStyle::SetAlignment(menu_gui_style, 0x0);

				UnityEngine::menu_gui_style->SetFontSize(12); //FPS?

				UnityEngine::GUI::SetColor(entry->outlineColor);

				UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y + 1), entry->text, menu_gui_style);
				UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y - 1), entry->text, menu_gui_style);

				UnityLabel(Vector2(entry->pos.x - 1, entry->pos.y - 1), entry->text, menu_gui_style);
				UnityLabel(Vector2(entry->pos.x + 1, entry->pos.y + 1), entry->text, menu_gui_style);


				UnityEngine::GUI::SetColor(entry->clr);

				UnityLabel(Vector2(entry->pos.x, entry->pos.y), entry->text, menu_gui_style);

				free(entry);
				it = text_buffer.erase(it);
			}
		}

		static void RenderIcons()
		{
			auto& text_buffer = get_icon_buffer();
			auto it = text_buffer.begin();
			while (it != text_buffer.end())
			{
				const auto& entry = *it;

				UnityEngine::GUI::SetColor(entry->backgroundColor);
				UnityEngine::GUI::DrawTexture(rect_t{ entry->pos.x, entry->pos.y, entry->size.x, entry->size.y }, entry->texture);

				free(entry);
				it = text_buffer.erase(it);
			}
		}
	};


	struct CapsuleCollider : Object {
		IL2CPP_CLASS("CapsuleCollider");

		auto set_radius(float value) -> void;
		auto get_height() -> float;
	};

	struct Rigidbody : Il2CppObject {
		IL2CPP_CLASS("Rigidbody");

		void set_velocity(Vector3 vel);
	};


	struct Terrain_C : Il2CppObject {
		IL2CPP_CLASS("Terrain");

		float SampleHeight(Vector3 pos)
		{
			if(!IsAddressValid(this))
				return 0.f;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SampleHeight"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<float>(procedure, this, pos);
			}


			return 0.f;
		}
	};

	enum CursorLockMode // TypeDefIndex: 10524
	{
		None = 0,
		Locked = 1,
		Confined = 2,
	};
	struct Cursor : Il2CppObject {
		IL2CPP_CLASS("Cursor");


		static void set_lockState(CursorLockMode value)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("set_lockState"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, value);
			}

			return;
		}
	};


	bool WorldToScreen(const Vector3& position, Vector2& output);
	bool WorldToScreen2(const Vector3& position, Vector3& output);
}


using UnityEngine::Vector2;
using UnityEngine::Vector3;
using UnityEngine::Vector4;
using UnityEngine::Quaternion;

inline Vector2 screen_center = { 0.f,0.f };
inline Vector3 spoofed_eye_pos = Vector3();


namespace UnityEngineUI
{
	IL2CPP_NAME_SPACE("UnityEngine.UI");

	struct Image : Il2CppObject {
		IL2CPP_CLASS("Image");

		IL2CPP_FIELD(UnityEngine::Sprite*, m_Sprite);
	};

	struct RawImage : Il2CppObject {
		IL2CPP_CLASS("RawImage");

		IL2CPP_FIELD(UnityEngine::Texture*, m_Texture);
		IL2CPP_PROPERTY(UnityEngine::Texture*, mainTexture);
	};

	struct InputField : Il2CppObject {
		IL2CPP_CLASS("InputField");

		void ActivateInputField()
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ActivateInputField"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}
		}

		void _ctor()
		{
			if(!IsAddressValid(this)) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this);
			}
			else
			{

				return;
			}

		}
	};
}


namespace UnityEngineNetworking {
	IL2CPP_NAME_SPACE("UnityEngine.Networking");

	struct DownloadHandlerBuffer : Il2CppObject {
		IL2CPP_CLASS("DownloadHandlerBuffer");

	};

	struct DownloadHandler : Il2CppObject {
		IL2CPP_CLASS("DownloadHandler");


		FPSystem::c_system_array<FPSystem::Byte*>* GetData()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetData"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<FPSystem::c_system_array<FPSystem::Byte*>*>(procedure, this);
			}


			return {};
		}

		DownloadHandler* NewInstance()
		{
			if(!IsAddressValid(this)) return {};

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{


				uintptr_t Texture2DClass = 0;
				if (!Texture2DClass)
				{
					Texture2DClass = (uintptr_t)CIl2Cpp::FindClass(XS("UnityEngine.Networking"), XS("DownloadHandler"));
				}
				DownloadHandler* texture2D = reinterpret_cast<DownloadHandler*>(CIl2Cpp::il2cpp_object_new(ToPointer(Texture2DClass)));
				Call<DownloadHandler*>(procedure, this);

				return texture2D;
			}
			else
			{

				return {};
			}

		}
	};

	struct UnityWebRequest : Il2CppObject {
		IL2CPP_CLASS("UnityWebRequest");

		IL2CPP_FIELD(DownloadHandler*, m_DownloadHandler);


		bool get_isDone()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("get_isDone"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, this);
			}


			return false;
		}

		void SendWebRequest()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SendWebRequest"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this);
			}


			return;
		}

		static UnityWebRequest* Get(const char* uri)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Get"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<UnityWebRequest*>(procedure, CIl2Cpp::il2cpp_string_new(uri));
			}


			return {};
		}
	};
}

inline UnityEngine::AssetBundle* MenuIconBundles = nullptr;
inline UnityEngine::AssetBundle* SerotoninIconBundle = nullptr;
