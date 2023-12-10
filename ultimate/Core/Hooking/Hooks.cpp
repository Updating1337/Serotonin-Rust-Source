#include "Hooks.hpp"

void Hooks::BeginHooks()
{
	Hooks::Update_hk.PointerSwapHook(XS("MainMenuSystem"), HASH("Update"), &Hooks::Update_, XS(""), 0);
	Hooks::OnGUIhk.PointerSwapHook(XS("PostProcessDebug"), HASH("OnGUI"), &Hooks::OnGUI, XS("UnityEngine.Rendering.PostProcessing"), 0);
	Hooks::DoAttackhk.VirtualFunctionHook(XS("BaseProjectile"), HASH("DoAttack"), &Hooks::DoAttack, XS(""), 0);
	//Hooks::DoAttackBowhk.VirtualFunctionHook(XS("BowWeapon"), HASH("DoAttack"), &Hooks::DoAttackBow, XS(""), 0);
	//Hooks::OnNetworkMessagehk.VirtualFunctionHook(XS("Client"), HASH("OnNetworkMessage"), &Hooks::OnNetworkMessage, XS(""), 1);
	Hooks::FlintStrikeWeaponDoAttackhk.VirtualFunctionHook(XS("FlintStrikeWeapon"), HASH("DoAttack"), &Hooks::FlintStrikeWeaponDoAttack, XS(""), 0);
	Hooks::DoAttackMeleehk.VirtualFunctionHook(XS("BaseMelee"), HASH("DoAttack"), &Hooks::DoAttackMelee, XS(""), 0);
	//Hooks::IsAiminghk.VirtualFunctionHook(XS("BowWeapon"), HASH("IsAiming"), &Hooks::IsAiming, XS(""), 0);

}