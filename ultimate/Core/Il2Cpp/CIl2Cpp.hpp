#pragma once

#include "../Includes/includes.hpp"

#pragma optimize( "", off )

namespace CIl2Cpp
{

DO_API( Il2CppDomain*, il2cpp_domain_get, () );
DO_API( const Il2CppAssembly**, il2cpp_domain_get_assemblies, ( const Il2CppDomain* domain, std::size_t* size ) );

DO_API( void, il2cpp_set_memory_callbacks, ( Il2CppMemoryCallbacks* callbacks ) );
DO_API( const Il2CppImage*, il2cpp_get_corlib, () );
DO_API( void, il2cpp_add_internal_call, ( const char* name, Il2CppMethodPointer method ) );
DO_API( Il2CppMethodPointer, il2cpp_resolve_icall, ( const char* name ) );
DO_API(uint64_t, il2cpp_image_get_class_count, (const Il2CppImage* domain));
DO_API(Il2CppClass*, il2cpp_image_get_class, (const Il2CppImage* domain, uint64_t));
DO_API(Il2CppType*, il2cpp_method_get_param, (const MethodInfo*, uint32_t));
DO_API(const char*, il2cpp_type_get_name, (const Il2CppType*));
DO_API(Il2CppType*, il2cpp_method_get_return_type, (const MethodInfo*));

DO_API( void*, il2cpp_alloc, ( std::size_t size ) );
DO_API( void, il2cpp_free, ( void* ptr ) );

DO_API( const Il2CppImage*, il2cpp_assembly_get_image, ( const Il2CppAssembly* assembly ) );

DO_API( bool, il2cpp_class_has_parent, ( Il2CppClass* klass, Il2CppClass* klassc ) );
DO_API( Il2CppClass*, il2cpp_class_from_name, ( const Il2CppImage* image, const char* namespaze, const char* name ) );
DO_API( const EventInfo*, il2cpp_class_get_events, ( const Il2CppClass* klass, void** iter ) );
DO_API( FieldInfo*, il2cpp_class_get_fields, ( const Il2CppClass* klass, void** iter ) );
DO_API( FieldInfo*, il2cpp_class_get_field_from_name, ( const Il2CppClass* klass, const char* name ) );
DO_API( const PropertyInfo*, il2cpp_class_get_properties, ( const Il2CppClass* klass, void** iter ) );
DO_API( const PropertyInfo*, il2cpp_class_get_property_from_name, ( const Il2CppClass* klass, const char* name ) );
DO_API( const MethodInfo*, il2cpp_class_get_methods, ( Il2CppClass* klass, void** iter ) );
DO_API( const MethodInfo*, il2cpp_class_get_method_from_name, ( Il2CppClass* klass, const char* name, int argsCount ) );
DO_API( const char*, il2cpp_class_get_name, ( Il2CppClass* klass ) );
DO_API( const char*, il2cpp_class_get_namespace, ( Il2CppClass* klass ) );
DO_API( Il2CppClass*, il2cpp_class_get_parent, ( Il2CppClass* klass ) );
DO_API(int, il2cpp_method_get_param_count, (uintptr_t));

DO_API( const char*, il2cpp_field_get_name, ( const FieldInfo* field ) );
DO_API( std::size_t, il2cpp_field_get_offset, ( const FieldInfo* field ) );

DO_API( const MethodInfo*, il2cpp_property_get_get_method, ( const PropertyInfo* prop ) );
DO_API( const MethodInfo*, il2cpp_property_get_set_method, ( const PropertyInfo* prop ) );
DO_API( const char*, il2cpp_property_get_name, ( const PropertyInfo* prop ) );

DO_API( Il2CppString*, il2cpp_string_new, ( const char* str ) );

DO_API( Il2CppObject*, il2cpp_runtime_invoke, ( const MethodInfo* method, void* obj, void** params, Il2CppObject** exc ) );
DO_API( void*, il2cpp_object_unbox, ( Il2CppObject* obj ) );

DO_API( const Il2CppAssembly*, il2cpp_image_get_assembly, ( const Il2CppImage* image ) );
DO_API( const char*, il2cpp_image_get_name, ( const Il2CppImage* image ) );
DO_API( const char*, il2cpp_image_get_filename, ( const Il2CppImage* image ) );
DO_API( const MethodInfo*, il2cpp_image_get_entry_point, ( const Il2CppImage* image ) );

DO_API( void, il2cpp_monitor_enter, ( Il2CppObject* obj ) );
DO_API( void, il2cpp_monitor_exit, ( Il2CppObject* obj ) );
DO_API(uintptr_t, il2cpp_object_new, (void*));

bool CreateIL2CPP();
void DestroyIL2CPP();

} // namespace rust

namespace CIl2Cpp {

	DO_API(Il2CppDomain*, il2cpp_domain_get, ());
	DO_API(void*, il2cpp_thread_attach, (void*));
	DO_API(void*, il2cpp_thread_detach, (void*));
	DO_API(const Il2CppAssembly**, il2cpp_domain_get_assemblies, (const Il2CppDomain* domain, std::size_t* size));
	DO_API(uint64_t, il2cpp_image_get_class_count, (const Il2CppImage* domain));
	DO_API(Il2CppClass*, il2cpp_image_get_class, (const Il2CppImage* domain, uint64_t));

	DO_API(void, il2cpp_set_memory_callbacks, (Il2CppMemoryCallbacks* callbacks));
	DO_API(const Il2CppImage*, il2cpp_get_corlib, ());
	DO_API(void, il2cpp_add_internal_call, (const char* name, Il2CppMethodPointer method));
	DO_API(Il2CppMethodPointer, il2cpp_resolve_icall, (const char* name));

	DO_API(void*, il2cpp_alloc, (std::size_t size));
	DO_API(void, il2cpp_free, (void* ptr));

	DO_API(const Il2CppImage*, il2cpp_assembly_get_image, (const Il2CppAssembly* assembly));

	DO_API(bool, il2cpp_class_has_parent, (Il2CppClass* klass, Il2CppClass* klassc));
	DO_API(Il2CppClass*, il2cpp_class_from_name, (const Il2CppImage* image, const char* namespaze, const char* name));
	DO_API(const EventInfo*, il2cpp_class_get_events, (const Il2CppClass* klass, void** iter));
	DO_API(FieldInfo*, il2cpp_class_get_fields, (const Il2CppClass* klass, void** iter));
	DO_API(FieldInfo*, il2cpp_class_get_field_from_name, (const Il2CppClass* klass, const char* name));
	DO_API(const PropertyInfo*, il2cpp_class_get_properties, (const Il2CppClass* klass, void** iter));
	DO_API(const PropertyInfo*, il2cpp_class_get_property_from_name, (const Il2CppClass* klass, const char* name));
	DO_API(const MethodInfo*, il2cpp_class_get_methods, (Il2CppClass* klass, void** iter));
	DO_API(const MethodInfo*, il2cpp_class_get_method_from_name, (Il2CppClass* klass, const char* name, int argsCount));
	DO_API(const Il2CppType*, il2cpp_type_get_object, (const Il2CppType* klass));

	DO_API(const Il2CppType*, il2cpp_class_get_type, (Il2CppClass* klass));

	DO_API(const char*, il2cpp_class_get_name, (Il2CppClass* klass));
	DO_API(const char*, il2cpp_class_get_namespace, (Il2CppClass* klass));
	DO_API(Il2CppClass*, il2cpp_class_get_parent, (Il2CppClass* klass));
	DO_API(int, il2cpp_method_get_param_count, (uintptr_t));
	DO_API(Il2CppType*, il2cpp_method_get_param, (const MethodInfo*, uint32_t));
	DO_API(const char*, il2cpp_type_get_name, (const Il2CppType*));
	DO_API(Il2CppType*, il2cpp_method_get_return_type, (const MethodInfo*));

	DO_API(const char*, il2cpp_field_get_name, (const FieldInfo* field));
	DO_API(std::size_t, il2cpp_field_get_offset, (const FieldInfo* field));

	DO_API(const MethodInfo*, il2cpp_property_get_get_method, (const PropertyInfo* prop));
	DO_API(const MethodInfo*, il2cpp_property_get_set_method, (const PropertyInfo* prop));
	DO_API(const char*, il2cpp_property_get_name, (const PropertyInfo* prop));

	DO_API(Il2CppString*, il2cpp_string_new, (const char* str));
	DO_API(uintptr_t, il2cpp_object_new, (void*));

	// runtime
	DO_API(Il2CppObject*, il2cpp_runtime_invoke, (const MethodInfo* method, void* obj, void** params, Il2CppObject** exc));
	DO_API(void*, il2cpp_object_unbox, (Il2CppObject* obj));

	DO_API(const Il2CppAssembly*, il2cpp_image_get_assembly, (const Il2CppImage* image));
	DO_API(const char*, il2cpp_image_get_name, (const Il2CppImage* image));
	DO_API(const char*, il2cpp_image_get_filename, (const Il2CppImage* image));
	DO_API(const MethodInfo*, il2cpp_image_get_entry_point, (const Il2CppImage* image));

	DO_API(void, il2cpp_monitor_enter, (Il2CppObject* obj));
	DO_API(void, il2cpp_monitor_exit, (Il2CppObject* obj));

	DO_API(const char*, il2cpp_method_get_param_name, (uint64_t, uint64_t));
	DO_API(const char*, il2cpp_method_get_name, (uint64_t));

	inline const Il2CppClass* FindClass(const Il2CppImage* image, const char* name_space, const char* name)
	{
		return il2cpp_class_from_name(image, name_space, name);
	}

	inline const Il2CppClass* FindClass(const char* name_space, const char* name)
	{
		const auto domain = il2cpp_domain_get();

		if (IsAddressValid(domain))
		{
			std::size_t count = 0;
			const auto assemblies = il2cpp_domain_get_assemblies(domain, &count);

			if (IsAddressValid(assemblies))
			{
				for (std::size_t index = 0; index < count; index++)
				{
					const auto assembly = assemblies[index];

					if (IsAddressValid(assembly))
					{
						const auto image = il2cpp_assembly_get_image(assembly);

						if (IsAddressValid(image))
						{
							const auto instance = FindClass(image, name_space, name);

							if (IsAddressValid(instance))
							{
								return instance;
							}
						}
					}
				}
			}
			else
			{
				LOG(XS("%s: il2cpp_domain_get_assemblies( ... ) error!"), XS(__FUNCTION__));
			}
		}
		else
		{
			LOG(XS("%s: il2cpp_domain_get() error!"), XS(__FUNCTION__));
		}

		return nullptr;
	}

	inline const FieldInfo* FindField(const Il2CppClass* object, std::uint64_t name_hash)
	{
		auto super = object;

		while (IsAddressValid(super))
		{
			auto iterator = static_cast<void*>(nullptr);
			auto field = il2cpp_class_get_fields(super, &iterator);

			while (IsAddressValid(field))
			{
				const auto name = il2cpp_field_get_name(field);

				if (IsAddressValid(name))
				{
					if (Hash(name, true) == name_hash)
					{
						return field;
					}
				}

				field = il2cpp_class_get_fields(super, &iterator);
			}
			super = super->parent;
		}

		return nullptr;
	}

	inline const PropertyInfo* FindProperty(const Il2CppClass* object, std::uint64_t name_hash)
	{
		auto super = object;

		while (IsAddressValid(super))
		{
			auto iterator = static_cast<void*>(nullptr);
			auto prop = il2cpp_class_get_properties(super, &iterator);

			while (IsAddressValid(prop))
			{
				const auto name = il2cpp_property_get_name(prop);

				if (IsAddressValid(name))
				{
					if (Hash(name, true) == name_hash)
					{
						return prop;
					}
				}

				prop = il2cpp_class_get_properties(super, &iterator);
			}

			super = super->parent;
		}

		return nullptr;
	}


	inline const Il2CppType* FindType(const Il2CppClass* object) {
		auto get_type = CIl2Cpp::il2cpp_class_get_type((Il2CppClass*)object);
		return CIl2Cpp::il2cpp_type_get_object(get_type);
	}



	inline const MethodInfo* FindMethodWithName(const Il2CppClass* object, std::uint64_t name_hash, std::uint8_t params_count /* = 0 */, const char* param_name)
	{
		auto super = object;

		while (IsAddressValid(super))
		{
			auto iterator = static_cast<void*>(nullptr);
			auto method = il2cpp_class_get_methods(const_cast<Il2CppClass*>(super), &iterator);

			while (IsAddressValid(method))
			{
				if (Hash(method->name, true) == name_hash)
				{
					if (method->parameters_count == params_count)
					{
						if (method->parameters->name == param_name)
						{
							return method;
						}
						
					}
				}

				method = il2cpp_class_get_methods(const_cast<Il2CppClass*>(super), &iterator);
			}

			super = super->parent;
		}

		return nullptr;
	}

	inline const MethodInfo* FindMethod(const Il2CppClass* object, std::uint64_t name_hash, std::uint8_t params_count /* = 0 */)
	{
		auto super = object;

		while (IsAddressValid(super))
		{
			auto iterator = static_cast<void*>(nullptr);
			auto method = il2cpp_class_get_methods(const_cast<Il2CppClass*>(super), &iterator);

			while (IsAddressValid(method))
			{
				if (Hash(method->name, true) == name_hash)
				{
					if (method->parameters_count == params_count)
					{
						return method;
					}
				}

				method = il2cpp_class_get_methods(const_cast<Il2CppClass*>(super), &iterator);
			}

			super = super->parent;
		}

		return nullptr;
	}

	inline uintptr_t hook(void* our_func, const char* kl, uint64_t name, int arg, const char* name_space)
	{
		auto il2cpp_method = (uintptr_t)FindMethod(FindClass(name_space, kl), name, arg);

		*reinterpret_cast<void**>(il2cpp_method) = our_func;

		void* written = *reinterpret_cast<void**>(il2cpp_method);
		if (written == our_func)
		{
			//TRACE("Hooked [%s] Successfully", kl);
		}

		return il2cpp_method;
	}


	inline uint64_t get_class(const char* namespace_name, const char* class_name) {
		const auto domain = il2cpp_domain_get();

		std::uintptr_t assembly_count{ 0 };
		const Il2CppAssembly** assemblies;
		assemblies = il2cpp_domain_get_assemblies(domain, &assembly_count);

		for (size_t idx{ 0 }; idx < assembly_count; idx++) {
			const auto img = il2cpp_assembly_get_image(assemblies[idx]);
			const auto kl = il2cpp_class_from_name(img, namespace_name, class_name);
			if (!kl)
				continue;

			return (uint64_t)kl;
		}

		return {};
	}

	inline uint64_t get_method_ptr(uint64_t klass, const char* method_name, int arg_count) {
		if (!klass)
			return { };

		const auto method_ptr = il2cpp_class_get_method_from_name((Il2CppClass*)klass, method_name, arg_count);
		return (uint64_t)method_ptr;
	}


	inline uint64_t get_method_ptr_with_args(uint64_t klass, const char* method_name, const char* arg_name, int arg_count) {
		if (!klass)
			return { };

		void* it{ 0 };
		while (auto method = il2cpp_class_get_methods((Il2CppClass*)klass, &it)) {
			if (auto _method_name = il2cpp_method_get_name((uint64_t)method);
				strcmp(method_name, _method_name) != 0)
				continue;

			if (auto param_count = il2cpp_method_get_param_count((uint64_t)method);
				param_count != arg_count)
				continue;

			for (int i{ }; i < arg_count; i++) {
				if (auto param_name = il2cpp_method_get_param_name((uint64_t)method, i);
					strcmp(arg_name, param_name) == 0)
					return (uint64_t)method;
			}
		}

		return { };
	}


	inline const MethodInfo* FindMethodFullArgs(std::uint64_t name_hash)
	{
		auto domain = il2cpp_domain_get();
		std::size_t count = 0;
		auto assemblies = il2cpp_domain_get_assemblies(domain, &count);

		for (int i = 0; i < count; i++) {
			auto image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));

			if (!(image))
				continue;

			for (int c = 0; c < il2cpp_image_get_class_count(image); c++) {
				std::string temp(image->name);
				temp.erase(temp.find(XS(".dll")), 4);

				auto klass = il2cpp_image_get_class(image, c);
				if (!(klass))
					continue;

				const char* name = klass->name;

				if (!(name))
					continue;

				const char* ns = klass->namespaze;

				if (std::string(ns).empty())
					temp = temp + XS("::") + name;
				else
					temp = temp + XS("::") + ns + XS("::") + name;

				const MethodInfo* Method = nullptr;
				auto iterator = static_cast<void*>(nullptr);
				while (Method = il2cpp_class_get_methods(const_cast<Il2CppClass*>(klass), &iterator))
				{
					std::string temp2(temp + XS("::") + Method->name);

					auto param_count = il2cpp_method_get_param_count((uintptr_t)(Method));
					if (param_count > 0)
					{
						temp2 = temp2 + XS("(");
						for (int p = 0; p < param_count; p++) {
							const auto param = il2cpp_method_get_param(Method, p);
							const auto param_name = il2cpp_type_get_name(param);
							std::string t(param_name);
							t = t.substr(t.find(XS(".")) + 1);
							temp2 = temp2 + t + XS(",");
						}

						const auto return_type = Method->return_type;
						const auto return_type_name = il2cpp_type_get_name(return_type);

						std::string t(return_type_name);
						temp2 = temp2.substr(0, temp2.size() - 1);
						temp2 = temp2 + XS("): ") + t.substr(t.find(XS(".")) + 1);
					}
					else {
						const auto return_type = Method->return_type;
						const auto return_type_name = il2cpp_type_get_name(return_type);
						std::string t(return_type_name);
						temp2 = temp2 + XS("(): ") + t.substr(t.find(XS(".")) + 1);
					}
					if (Hash(temp2.c_str(), true) == name_hash) {
						return Method;
					}
				}

			}
		}

		return nullptr;
	}

	inline uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* our_func, int param_count, const char* name_space)
	{
		auto method = (uintptr_t)FindMethod(FindClass(name_space, classname), Hash(function_to_hook, true), param_count);
		if (!method)
		{
			//TRACE(" Error getting method %s::%s::%s", name_space, classname, function_to_hook);
			return NULL;
		}
		uintptr_t search = *reinterpret_cast<uintptr_t*>(method);
		uintptr_t table = (uintptr_t)FindClass(name_space, classname);

		if (search == (uintptr_t)our_func)
		{
			//TRACE("Already Hooked %s::%s::%s", name_space, classname, function_to_hook);
			return (uintptr_t)our_func;
		}

		for (uintptr_t i = table; i <= table + 0x10000; i += 0x1) {
			uintptr_t addr = *reinterpret_cast<uintptr_t*>(i);
			if (addr == search)
			{
				//TRACE("Hooking %s::%s::%s", name_space, classname, function_to_hook);
				*reinterpret_cast<uintptr_t*>(i) = (uintptr_t)our_func;
				return addr;
			}
		}
		//TRACE("Failed to Hook %s::%s::%s", name_space, classname, function_to_hook);
	}


	inline uintptr_t VFuntionHook(const char* classname, const char* function_to_hook, void* our_func, const char* name_space = XS(""), int argcounttt = -1) {
		uintptr_t search = *reinterpret_cast<uintptr_t*>((uintptr_t)FindMethod(FindClass(name_space, classname), Hash(function_to_hook, true), argcounttt));
		uintptr_t table = (uintptr_t)FindClass(name_space, classname);


		if (search == (uintptr_t)our_func)
			return (uintptr_t)our_func;

		for (uintptr_t i = table; i <= table + 0x1500; i += 0x1) {
			uintptr_t addr = *reinterpret_cast<uintptr_t*>(i);
			if (addr == search) {
				*reinterpret_cast<uintptr_t*>(i) = (uintptr_t)our_func;
				return addr;
			}
		}
	}
}

#pragma region il2cpp_reg
#define IL2CPP_NAME_SPACE( name )																															\
static const char* get_namespace(){\
	const char* gg = name; \
	return gg;\
}\

#define IL2CPP_CLASS( name )																																	\
	static const Il2CppClass* StaticClass()																											\
	{																																														\
		static const Il2CppClass* instance = nullptr;																							\
		if( !( instance ) )																									\
		{																																													\
			instance = CIl2Cpp::FindClass( get_namespace(), (name) );																			\
		}																																													\
		return instance;																																					\
	}


#define IL2CPP_FIELD(return_type, name) return_type& name() { \
	__try \
	{ \
		static std::size_t offset = 0; \
		if( !offset )																																							\
		{																																													\
			const auto field = CIl2Cpp::FindField( klass, HASH( #name ) );															\
			if( ( field ) )																										\
			{																																												\
				offset = CIl2Cpp::il2cpp_field_get_offset( field );																			\
			}																																												\
		}																																													\
		return *reinterpret_cast< return_type* >( (uintptr_t)( this ) + offset );						\
	} \
	__except (true) \
	{ \
		/*LOG(XS("Exception Occurred. %s"));*/ \
	} \
		auto n = nullptr; \
		return reinterpret_cast<return_type&>(n); \
	}

#define IL2CPP_STATIC_FIELD( return_type, name )																							\
	static return_type& name()																																	\
	{																																														\
		static auto offsetz = 0;														\
		if( offsetz == 0 )																	\
		{																																													\
			const auto field = CIl2Cpp::FindField( StaticClass(), HASH( #name ) );											\
			if(  field )																										\
			{																																												\
				offsetz = CIl2Cpp::il2cpp_field_get_offset( field );																			\
			}																																												\
		}																																													\
		const auto static_fields = StaticClass()->static_fields;																	\
		return *reinterpret_cast< return_type* >(ToAddress( static_fields ) + offsetz );	\
	}



#define IL2CPP_PROPERTY( return_type, name )																																		\
	return_type JOIN( get_, name )()																																							\
	{																																																							\
		static std::uintptr_t procedure = 0;																																				\
		if( !( procedure ) )																																	\
		{																																																						\
			const auto prop = CIl2Cpp::FindProperty( klass, HASH( #name ) );																							\
			if( ( prop ) )																																			\
			{																																																					\
				const auto method = CIl2Cpp::il2cpp_property_get_get_method( prop );																				\
				if( ( method ) )																																	\
				{																																																				\
					procedure = (uintptr_t)( method->methodPointer );																								\
				}																																																				\
			}																																																					\
		}																																																						\
		if constexpr( sizeof( return_type ) > sizeof( std::uintptr_t ) )																						\
		{																																																						\
			return_type data = { };																																										\
			const auto method = reinterpret_cast< return_type*( __fastcall* )( return_type*, void* ) >( procedure );	\
			method( &data, this );																																										\
			return std::move( data );																																									\
		}																																																						\
		else																																																				\
		{																																																						\
			const auto method = reinterpret_cast< return_type( __fastcall* )( void* ) >( procedure );									\
			return method(this );																																										\
		}																																																						\
	}

#define IL2CPP_STATIC_PROPERTY( return_type, name )																															\
	static return_type JOIN( get_, name )()																																				\
	{																																																							\
		static std::uintptr_t procedure = 0;																																				\
		if( !( procedure ) )																																	\
		{																																																						\
			const auto prop = CIl2Cpp::FindProperty( StaticClass(), HASH( #name ) );																			\
			if( ( prop ) )																																			\
			{																																																					\
				const auto method = CIl2Cpp::il2cpp_property_get_get_method( prop );																				\
				if( ( method ) )																																	\
				{																																																				\
					procedure = (uintptr_t)( method->methodPointer );																								\
				}																																																				\
			}																																																					\
		}																																																						\
		if constexpr( sizeof( return_type ) > sizeof( std::uintptr_t ) )																						\
		{																																																						\
			return_type data = { };																																										\
			const auto method = reinterpret_cast< return_type*( __fastcall* )( return_type* ) >( procedure );					\
			method(&data );																																													\
			return std::move( data );																																									\
		}																																																						\
		else																																																				\
		{																																																						\
			const auto method = reinterpret_cast< return_type( __fastcall* )() >( procedure );												\
			return method();																																													\
		}																																																						\
	}

#define IL2CPP_METHOD_FIND(name, size)												\
		static const MethodInfo* method_info = nullptr;								\
		if(!(method_info))									\
		{																			\
			method_info = CIl2Cpp::FindMethod( StaticClass(), HASH(##name), size );    \
			if ( !( method_info ) )							\
			{																		\
				LOG( XS("%s: Invalid method_info for calling runtime method!") ); \
				return { };														    \
			}																		\
		}	
#pragma endregion


IL2CPP_NAME_SPACE("");

#pragma optimize( "", on )