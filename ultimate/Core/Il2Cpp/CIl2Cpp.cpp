#include "CIl2Cpp.hpp"
#include "../Includes/includes.hpp"

#pragma optimize( "", off )
#define IL2CPP_API( return_type, name, parameters )		return_type ( *name ) parameters = nullptr
#define IL2CPP_IMPORT( image, name )									name = reinterpret_cast< decltype( name ) >( GetImageExport( image, HASH( #name ) ) )

namespace CIl2Cpp
{

IL2CPP_API( Il2CppDomain*, il2cpp_domain_get, () );
IL2CPP_API( void*, il2cpp_thread_attach, ( void* ) );
IL2CPP_API( void*, il2cpp_thread_detach, ( void* ) );
IL2CPP_API( const Il2CppAssembly**, il2cpp_domain_get_assemblies, ( const Il2CppDomain* domain, std::size_t* size ) );
IL2CPP_API(uint64_t, il2cpp_image_get_class_count, (const Il2CppImage* domain));
IL2CPP_API(Il2CppClass*, il2cpp_image_get_class, (const Il2CppImage* domain, uint64_t));
IL2CPP_API(Il2CppType*, il2cpp_method_get_param, (const MethodInfo*, uint32_t));
IL2CPP_API(const char*, il2cpp_type_get_name, (const Il2CppType*));
IL2CPP_API(Il2CppType*, il2cpp_method_get_return_type, (const MethodInfo*));

IL2CPP_API( void, il2cpp_set_memory_callbacks, ( Il2CppMemoryCallbacks* callbacks ) );
IL2CPP_API( const Il2CppImage*, il2cpp_get_corlib, () );
IL2CPP_API( void, il2cpp_add_internal_call, ( const char* name, Il2CppMethodPointer method ) );
IL2CPP_API( Il2CppMethodPointer, il2cpp_resolve_icall, ( const char* name ) );

IL2CPP_API( void*, il2cpp_alloc, ( std::size_t size ) );
IL2CPP_API( void, il2cpp_free, ( void* ptr ) );

IL2CPP_API( const Il2CppImage*, il2cpp_assembly_get_image, ( const Il2CppAssembly* assembly ) );

IL2CPP_API( Il2CppClass*, il2cpp_class_from_name, ( const Il2CppImage* image, const char* namespaze, const char* name ) );
IL2CPP_API( const EventInfo*, il2cpp_class_get_events, ( const Il2CppClass* klass, void** iter ) );
IL2CPP_API( FieldInfo*, il2cpp_class_get_fields, ( const Il2CppClass* klass, void** iter ) );
IL2CPP_API( FieldInfo*, il2cpp_class_get_field_from_name, ( const Il2CppClass* klass, const char* name ) );
IL2CPP_API( const PropertyInfo*, il2cpp_class_get_properties, ( const Il2CppClass* klass, void** iter ) );
IL2CPP_API( const PropertyInfo*, il2cpp_class_get_property_from_name, ( const Il2CppClass* klass, const char* name ) );
IL2CPP_API( const MethodInfo*, il2cpp_class_get_methods, ( Il2CppClass* klass, void** iter ) );
IL2CPP_API( const MethodInfo*, il2cpp_class_get_method_from_name, ( Il2CppClass* klass, const char* name, int argsCount ) );
IL2CPP_API( const char*, il2cpp_class_get_name, ( Il2CppClass* klass ) );
IL2CPP_API( const char*, il2cpp_class_get_namespace, ( Il2CppClass* klass ) );
IL2CPP_API( Il2CppClass*, il2cpp_class_get_parent, ( Il2CppClass* klass ) );
IL2CPP_API(int, il2cpp_method_get_param_count, (uintptr_t));

IL2CPP_API( const char*, il2cpp_field_get_name, ( const FieldInfo* field ) );
IL2CPP_API( std::size_t, il2cpp_field_get_offset, ( const FieldInfo* field ) );

IL2CPP_API( const MethodInfo*, il2cpp_property_get_get_method, ( const PropertyInfo* prop ) );
IL2CPP_API( const MethodInfo*, il2cpp_property_get_set_method, ( const PropertyInfo* prop ) );
IL2CPP_API( const char*, il2cpp_property_get_name, ( const PropertyInfo* prop ) );

IL2CPP_API(const Il2CppType*, il2cpp_type_get_object, (const Il2CppType* klass));

IL2CPP_API(const Il2CppType*, il2cpp_class_get_type, (Il2CppClass* klass));

IL2CPP_API( Il2CppString*, il2cpp_string_new, ( const char* str ) );

IL2CPP_API( Il2CppObject*, il2cpp_runtime_invoke, ( const MethodInfo* method, void* obj, void** params, Il2CppObject** exc ) );
IL2CPP_API( void*, il2cpp_object_unbox, ( Il2CppObject* obj ) );

IL2CPP_API( const Il2CppAssembly*, il2cpp_image_get_assembly, ( const Il2CppImage* image ) );
IL2CPP_API( const char*, il2cpp_image_get_name, ( const Il2CppImage* image ) );
IL2CPP_API( const char*, il2cpp_image_get_filename, ( const Il2CppImage* image ) );
IL2CPP_API( const MethodInfo*, il2cpp_image_get_entry_point, ( const Il2CppImage* image ) );

IL2CPP_API( void, il2cpp_monitor_enter, ( Il2CppObject* obj ) );
IL2CPP_API( void, il2cpp_monitor_exit, ( Il2CppObject* obj ) );
IL2CPP_API(uintptr_t, il2cpp_object_new, (void*));
IL2CPP_API(const char*, il2cpp_method_get_param_name, (uint64_t, uint64_t));
IL2CPP_API(const char*, il2cpp_method_get_name, (uint64_t));
bool CreateIL2CPP()
{
	IL2CPP_IMPORT(m_game_assembly, il2cpp_method_get_param_name);
	IL2CPP_IMPORT(m_game_assembly, il2cpp_method_get_name);

	IL2CPP_IMPORT( m_game_assembly, il2cpp_domain_get );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_thread_attach );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_thread_detach );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_domain_get_assemblies );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_set_memory_callbacks );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_get_corlib );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_add_internal_call );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_resolve_icall );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_alloc );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_free );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_assembly_get_image );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_from_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_events );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_fields );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_field_from_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_properties );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_property_from_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_methods );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_method_from_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_namespace );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_class_get_parent );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_field_get_offset );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_field_get_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_property_get_get_method );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_property_get_set_method );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_property_get_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_string_new );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_runtime_invoke );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_object_unbox );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_image_get_assembly );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_image_get_name );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_image_get_filename );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_image_get_entry_point );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_monitor_enter );
	IL2CPP_IMPORT( m_game_assembly, il2cpp_monitor_exit );
	IL2CPP_IMPORT(m_game_assembly, il2cpp_method_get_param_count);
	IL2CPP_IMPORT(m_game_assembly, il2cpp_class_get_type);
	IL2CPP_IMPORT(m_game_assembly, il2cpp_type_get_object);

	IL2CPP_IMPORT(m_game_assembly, il2cpp_object_new);
	IL2CPP_IMPORT(m_game_assembly, il2cpp_image_get_class_count);
	IL2CPP_IMPORT(m_game_assembly, il2cpp_image_get_class);
	IL2CPP_IMPORT(m_game_assembly, il2cpp_method_get_param);

	IL2CPP_IMPORT(m_game_assembly, il2cpp_type_get_name);

	return true;
}

void DestroyIL2CPP()
{

}



} // namespace rust
#pragma optimize( "", on )