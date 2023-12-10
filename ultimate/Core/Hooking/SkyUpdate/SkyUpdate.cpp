#include "../Hooks.hpp"


void Hooks::SkyUpdate(AssemblyCSharp::TOD_Camera* _This)
{
	//if(!InGame)
	//	return Hooks::SkyUpdatehk.get_original< decltype(&SkyUpdate)>()(_This);



	//auto load_from_memory_internal = reinterpret_cast<void (*)(UnityEngine::Material * mat)>(CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.RenderSettings::set_skybox")));
	//LOG("[DEBUG] test - %p", load_from_memory_internal);
	//load_from_memory_internal(nullptr);

	//auto UpdateEnvironment = reinterpret_cast<void (*)()>(CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.DynamicGI::UpdateEnvironment")));
	//LOG("[DEBUG] UpdateEnvironment - %p", UpdateEnvironment);

	//UpdateEnvironment();

	return;
}