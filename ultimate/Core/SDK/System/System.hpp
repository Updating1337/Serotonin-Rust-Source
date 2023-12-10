#pragma once
#include "../../Il2Cpp/CIl2Cpp.hpp"


namespace FPSystem {
	IL2CPP_NAME_SPACE("System");



	struct Type {
		IL2CPP_CLASS("Type");

		static Type* GetType(const char* qualified_name) {
			const auto get_type = reinterpret_cast<Type * (*)(Il2CppString*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(CIl2Cpp::FindClass(XS("System"), XS("Type")), HASH("GetType"), 1)));

			if (IS_NULL_POINTER(get_type))
				return nullptr;

			return Call<Type*>((uintptr_t)get_type, CIl2Cpp::il2cpp_string_new(qualified_name));
		}

		static Type* SkinnedMeshRenderer() {
			Type* type = GetType(XS("UnityEngine.SkinnedMeshRenderer, UnityEngine.CoreModule"));

			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}
		static Type* PostProcessDebug() {
			Type* type = GetType(XS("UnityEngine.Rendering.PostProcessing.PostProcessDebug, Assembly-CSharp"));

			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}
		static Type* Renderer() {
			Type* type = GetType(XS("UnityEngine.Renderer, UnityEngine.CoreModule"));

			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* Shader() {
			Type* type = GetType(XS("UnityEngine.Shader, UnityEngine.CoreModule"));

			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}


		static Type* Object() {
			Type* type = GetType(XS("UnityEngine.Object, UnityEngine.CoreModule"));

			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}


		static Type* Material() {
			Type* type = GetType(XS("UnityEngine.Material, UnityEngine.CoreModule"));

			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* Behaviour() {
			Type* type = GetType(XS("UnityEngine.Behaviour, UnityEngine.CoreModule"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* GameObject() {
			Type* type = GetType(XS("UnityEngine.GameObject, UnityEngine.CoreModule"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* Sprite() {
			Type* type = GetType(XS("UnityEngine.Sprite, UnityEngine.CoreModule"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* Font() {
			Type* type = GetType(XS("UnityEngine.Font, UnityEngine.CoreModule"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* Projectile() {
			Type* type = GetType(XS("Projectile, Assembly-CSharp"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* BaseProjectile() {
			Type* type = GetType(XS("BaseProjectile, Assembly-CSharp"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* BaseCombatEntity() {
			Type* type = GetType(XS("BaseCombatEntity, Assembly-CSharp"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* ItemModProjectile() {
			Type* type = GetType(XS("ItemModProjectile, Assembly-CSharp"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* ExplosionsFPS() {
			Type* type = GetType(XS("ExplosionsFPS, Assembly-CSharp"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

		static Type* ScrollViewState() {
			Type* type = GetType(XS("UnityEngine.ScrollViewState, UnityEngine.IMGUIModule"));
			if (IS_NULL_POINTER(type))
				return nullptr;

			return type;
		}

	};

	struct Object : Il2CppObject
	{
		IL2CPP_CLASS("Object");
	};

	struct IntPtr : Il2CppObject
	{
		IL2CPP_CLASS("IntPtr");

		//inline void* ToPointer()
		//{
		//	static uintptr_t procedure = 0;
		//	if ( !( procedure ) )
		//	{
		//		const auto method = rust::FindMethod( StaticClass(), HASH( "ToPointer" ), 0 );
		//		if ( ( method ) )
		//		{
		//			procedure = ToAddress( method->methodPointer );
		//		}
		//	}
		//
		//	if ( ( procedure ) )
		//	{
		//		return Call<void*>( procedure, this );
		//	}
		//
		//	return nullptr;
		//}

		void* m_value = nullptr;
	};

	struct String : Il2CppObject
	{
		String(uint32_t size)
		{
			m_stringLength = size;
			m_firstChar[size] = { };
		}


		const wchar_t* c_str() const
		{
			return m_firstChar;
		}

		wchar_t* begin()
		{
			return m_firstChar;
		}

		wchar_t* end()
		{
			return (begin() + m_stringLength);
		}

		const wchar_t* begin() const
		{
			return m_firstChar;
		}

		auto string_safe() -> std::string
		{
			std::wstring ws = m_firstChar;
			return std::string(ws.begin(), ws.end());
		}

		const wchar_t* end() const
		{
			return (begin() + m_stringLength);
		}




		IL2CPP_CLASS("String");
		std::int32_t m_stringLength = 0;	// 0x0010
		wchar_t m_firstChar[1] = { };		// 0x0014
		wchar_t str[128 + 1];

		bool Contains(const char* str)
		{
			if (!this) return false;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Contains"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<bool>(procedure, this, CIl2Cpp::il2cpp_string_new(str));
			}
			else
			{

				return false;
			}
		}
	};

	template <class T>
	class c_system_array {
	public:
		Il2CppObject obj;
		void* bounds;
		uint64_t size;
		T items[0];
	};


	struct Byte : Il2CppObject
	{
		IL2CPP_CLASS("Byte");
		IL2CPP_FIELD(Byte*, m_value);

	};
	struct Convert {
		IL2CPP_CLASS("Convert");

		static c_system_array<Byte*>* FromBase64String(const char* str)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("FromBase64String"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<c_system_array<Byte*>*>(procedure, CIl2Cpp::il2cpp_string_new(str));
			}
			else
			{

				return nullptr;
			}
		}
	};

	template< typename Type >
	struct Array : Il2CppArray
	{
		Type m_Items[1] = { };


		uintptr_t GetData() {
			return reinterpret_cast<uintptr_t>(&m_pValues);
		}

		Type& operator[](unsigned int index)
		{
			return *reinterpret_cast<Type*>(GetData() + sizeof(Type) * index);
		}
		Type& At(unsigned int index)
		{
			return operator[](index);
		}

		Type* m_pValues = nullptr;
	};



	struct Array_3 : Il2CppObject
	{
		IL2CPP_CLASS("Array");

	};

	template< typename Type >
	struct BufferList : Il2CppObject
	{
		std::int32_t count = 0;						// 0x0010
		FIELD_PAD(0x0004);							// 0x0014
		Array< Type >* buffer = nullptr;	// 0x0018
	};

	template< typename KeyType, typename ValueType >
	struct ListDictionary : Il2CppObject
	{
		FIELD_PAD(0x0010);						// 0x0010
		BufferList< KeyType >* keys = nullptr;		// 0x0020
		BufferList< ValueType >* vals = nullptr;	// 0x0040
	};

	template< typename Type >
	struct List : Il2CppObject
	{
		Array< Type >* _items = nullptr;		// 0x0010
		std::int32_t _size = 0;					// 0x0018
		std::int32_t _version = 0;				// 0x001C
		Il2CppObject* _syncRoot = nullptr;		// 0x0020

		void Clear()
		{
			if (this->_size > 0)
			{
				memcpy(this->_items, 0, this->_size);
				this->_size = 0;
			}
			this->_version++;
		}
	};


	template<typename T = unsigned char>
	FPSystem::Array<T>* il2cpp_array_new_specific(const Il2CppClass* klazz, unsigned long long length) {
		auto image = GetImage(HASH("GameAssembly.dll"));
		auto ret = Call< FPSystem::Array<T>*>((uintptr_t)GetImageExport(image, HASH("il2cpp_array_new_specific")), klazz, length);
		return ret;
	}

	template<typename T = unsigned char>
	FPSystem::Array<T>* il2cpp_array_new(const Il2CppClass* klazz, unsigned long long length) {
		auto image = GetImage(HASH("GameAssembly.dll"));
		auto ret = Call< FPSystem::Array<T>*>((uintptr_t)GetImageExport(image, HASH("il2cpp_array_new")), klazz, length);
		return ret;
	}

	struct TextReader : Il2CppObject
	{
		IL2CPP_CLASS("TextReader");

		FPSystem::String* ReadLine()
		{
			if (!this) return {};

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ReadLine"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<FPSystem::String*>(procedure, this);
			}
			else
			{

				return {};
			}
		}

		void _cctor()
		{
			if (!this) return;

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

	struct TextWriter : Il2CppObject {
		IL2CPP_CLASS("TextWriter");


		void _cctor()
		{
			if (!this) return;

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

	struct Console : Il2CppObject {
		IL2CPP_CLASS("Console");

		static void WriteLine(const char* str)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethodFullArgs(HASH("mscorlib::System::Console::WriteLine(String): Void"));
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, CIl2Cpp::il2cpp_string_new(str));
			}


			return;
		}

		static uintptr_t* OpenStandardInput(int size)
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("OpenStandardInput"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<uintptr_t*>(procedure, size);
			}
			else
			{

				return {};
			}
		}

		static void _cctor()
		{
			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".cctor"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure);
			}
			else
			{

				return;
			}
		}

		static TextWriter* std_out()
		{
			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(StaticClass(), HASH("stdout"));
			if ((field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}
			const auto static_fields = StaticClass()->static_fields;

			return *reinterpret_cast<TextWriter**>(ToAddress(static_fields) + offset);
		}

		static TextWriter* std_err()
		{
			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(StaticClass(), HASH("stderr"));
			if ((field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}
			const auto static_fields = StaticClass()->static_fields;
			return *reinterpret_cast<TextWriter**>(ToAddress(static_fields) + offset);
		}

		static TextReader* std_in()
		{
			static std::size_t offset = 0;
			const auto field = CIl2Cpp::FindField(StaticClass(), HASH("stdin"));
			if ((field))
			{
				offset = CIl2Cpp::il2cpp_field_get_offset(field);
			}
			const auto static_fields = StaticClass()->static_fields;

			return *reinterpret_cast<TextReader**>(ToAddress(static_fields) + offset);
		}
	};


	struct Uri : Il2CppObject {
		IL2CPP_CLASS("Uri");

		IL2CPP_FIELD(FPSystem::String*, m_String);
		IL2CPP_PROPERTY(FPSystem::String*, AbsoluteUri);
		IL2CPP_PROPERTY(FPSystem::String*, Query);


		FPSystem::String* ToString()
		{
			if (!this) return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ToString"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, this);
			}
			else
			{

				return {};
			}
		}
	};
}

namespace Windows {
	IL2CPP_NAME_SPACE("Windows");

	struct ConsoleInput : Il2CppObject {
		IL2CPP_CLASS("ConsoleInput");


		void add_OnInputText(const char* input)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("add_OnInputText"), 1);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<void>(procedure, this, CIl2Cpp::il2cpp_string_new(input));
			}
			else
			{

				return;
			}
		}

		void RedrawInputLine()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("RedrawInputLine"), 0);
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

		void Update()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Update"), 0);
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
		void _cctor()
		{
			if (!this) return;

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

	struct ConsoleWindow : Il2CppObject {
		IL2CPP_CLASS("ConsoleWindow");

		void Initialize()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Initialize"), 0);
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

		void _cctor()
		{
			if (!this) return;

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
		static bool AllocConsole()
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("AllocConsole"), 0);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<bool*>(procedure);
			}
			else
			{
				return {};
			}
		}

		static bool FreeConsole()
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("FreeConsole"), 0);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<bool*>(procedure);
			}
			else
			{
				return {};
			}
		}
	};

}


namespace SystemIO {
	IL2CPP_NAME_SPACE("System.IO");


	struct MemoryStream : Il2CppObject {
		IL2CPP_CLASS("MemoryStream");

		FPSystem::c_system_array<FPSystem::Byte*>* ToArray()
		{
			if (!this) return {};

			static uintptr_t procedure = 0;
			if (!(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ToArray"), 0);
				if ((method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if ((procedure))
			{
				return Call<FPSystem::c_system_array<FPSystem::Byte*>*>(procedure, this);
			}
			else
			{

				return {};
			}
		}

		void _cctor()
		{
			if (!this) return;

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

	struct Stream : Il2CppObject {
		IL2CPP_CLASS("Stream");

		void CopyTo(Stream* destination)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("CopyTo"), 1);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<void>(procedure, this, destination);
			}
			else
			{
				return;
			}
		}

		int Read(FPSystem::c_system_array<FPSystem::Byte*>* arr, int offset, int count)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Read"), 3);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<int>(procedure, this, arr, offset, count);
			}
			else
			{
				return {};
			}
		}
	};

	enum FileMode // TypeDefIndex: 5858
	{
		// Fields
		CreateNew = 1,
		Create = 2,
		Open = 3,
		OpenOrCreate = 4,
		Truncate = 5,
		Append = 6,
	};

	struct FileStream : Il2CppObject {
		IL2CPP_CLASS("FileStream");

	};

	struct StreamReader : Il2CppObject {
		IL2CPP_CLASS("StreamReader");

		FPSystem::String* ReadToEnd()
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ReadToEnd"), 0);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<FPSystem::String*>(procedure, this);
			}
			else
			{
				return {};
			}
		}

		FPSystem::String* ReadLine()
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ReadLine"), 0);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<FPSystem::String*>(procedure, this);
			}
			else
			{
				return {};
			}
		}
	};

	struct File : Il2CppObject {
		IL2CPP_CLASS("File");

		static FPSystem::List<FPSystem::String*>* ReadLines(const char* path)
		{

			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ReadLines"), 1);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<FPSystem::List<FPSystem::String*>*>(procedure, CIl2Cpp::il2cpp_string_new(path));
			}
			else
			{
				return {};
			}
		}

		static void WriteAllText(const char* path, const char* contents)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("WriteAllText"), 2);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<void>(procedure, CIl2Cpp::il2cpp_string_new(path), CIl2Cpp::il2cpp_string_new(contents));
			}
			else
			{
				return;
			}
		}

		static FPSystem::String* ReadAllText(const char* path)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("ReadAllText"), 1);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<FPSystem::String*>(procedure, CIl2Cpp::il2cpp_string_new(path));
			}
			else
			{
				return {};
			}
		}

		static StreamReader* OpenText(const char* str)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("OpenText"), 1);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<StreamReader*>(procedure, CIl2Cpp::il2cpp_string_new(str));
			}
			else
			{
				return {};
			}
		}

		static FileStream* Open(const char* str, FileMode mode)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Open"), 2);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<FileStream*>(procedure, CIl2Cpp::il2cpp_string_new(str), mode);
			}
			else
			{
				return {};
			}
		}

		static bool Exists(const char* path)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Exists"), 1);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<bool>(procedure, CIl2Cpp::il2cpp_string_new(path));
			}
			else
			{
				return false;
			}
		}

		static void Delete(const char* path)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("Delete"), 1);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<void>(procedure, CIl2Cpp::il2cpp_string_new(path));
			}
			else
			{
				return;
			}
		}
	};


}


namespace NewtonsoftJson {
	IL2CPP_NAME_SPACE("Newtonsoft.Json");

	struct JsonConvert : Il2CppObject {
		IL2CPP_CLASS("JsonConvert");

		static FPSystem::String* SerializeObject(const char* str)
		{
			static uintptr_t procedure = 0;
			if (!procedure)
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("SerializeObject"), 1);
				if (method)
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (procedure)
			{
				return Call<FPSystem::String*>(procedure, CIl2Cpp::il2cpp_string_new(str));
			}
			else
			{
				return {};
			}
		}
	};

}

namespace SystemNet {
	IL2CPP_NAME_SPACE("System.Net");

	struct WebClient : Il2CppObject {

		IL2CPP_CLASS("WebClient");

		FPSystem::Uri* GetUri(const char* str)
		{
			if (!this) return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("GetUri"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::Uri*>(procedure, this, CIl2Cpp::il2cpp_string_new(str));
			}
			else
			{

				return {};
			}
		}


		FPSystem::c_system_array< FPSystem::Byte* >* DownloadDataInternal(FPSystem::Uri* str, uintptr_t* request)
		{
			if (!this) return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DownloadDataInternal"), 2);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::c_system_array< FPSystem::Byte* >*>(procedure, this, (str), request);
			}
			else
			{

				return {};
			}
		}

		void DownloadStringAsync(FPSystem::Uri* str)
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DownloadStringAsync"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<void>(procedure, this, (str));
			}
			else
			{

				return;
			}
		}

		FPSystem::String* DownloadString(const char* str)
		{
			if (!this) return {};

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH("DownloadString"), 1);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
			{
				return Call<FPSystem::String*>(procedure, this, CIl2Cpp::il2cpp_string_new(str));
			}
			else
			{

				return {};
			}
		}

		void _cctor()
		{
			if (!this) return;

			static uintptr_t procedure = 0;
			if (!IsAddressValid(procedure))
			{
				const auto method = CIl2Cpp::FindMethod(StaticClass(), HASH(".ctor"), 0);
				if (IsAddressValid(method))
				{
					procedure = ToAddress(method->methodPointer);
				}
			}

			if (IsAddressValid(procedure))
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
