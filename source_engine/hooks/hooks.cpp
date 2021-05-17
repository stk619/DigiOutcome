#include "hooks.h"

//for now hooking can only be done with signatures, the detour class needs a form of vfunc hooking, allowing us to hook specific functions easier
//this, however, is done using valve's gameoverlayrender.dll which has the main perk of being minimalistic and being something directly from valve

bool nHooks::allocate()
{
	//client.dll
	if (!sDetours.hook_function(xorstr_("CamThink"), nUtilities::find_signature(xorstr_("client.dll"), xorstr_("55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9")), &cam_think))
		return false;

	if (!sDetours.hook_function(xorstr_("CamToThirdperson"), nUtilities::find_signature(xorstr_("client.dll"), xorstr_("55 8B EC 83 EC 0C 8D 55 F4")), &cam_to_thirdperson))
		return false;

	if (!sDetours.hook_function(xorstr_("CreateMove"), nUtilities::find_signature(xorstr_("client.dll"), xorstr_("55 8B EC 8B 0D ? ? ? ? 85 C9 75 06")), &create_move))
		return false;

	if (!sDetours.hook_function(xorstr_("ViewmodelFov"), nUtilities::find_signature(xorstr_("client.dll"), xorstr_("55 8B EC 8B 0D ? ? ? ? 83 EC 08 57")), &viewmodel_fov))
		return false;

	//vguimatsurface.dll
	if (!sDetours.hook_function(xorstr_("LockCursor"), nUtilities::find_signature(xorstr_("vguimatsurface.dll"), xorstr_("80 3D ? ? ? ? ? 8B 91 ? ? ? ? 8B 0D ? ? ? ? C6 05 ? ? ? ? ? 8B 01 74 0B FF 35 ? ? ? ? 52 FF 50 34 C3 6A 00 52 FF 50 34 C3 55")), &lock_cursor))
		return false;

	//engine.dll
	if (!sDetours.hook_function(xorstr_("Paint"), nUtilities::find_signature(xorstr_("engine.dll"), xorstr_("55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8")), &paint))
		return false;

	sConsole.log(eLogType::MAIN, xorstr_("hooks finished allocating"));
	return true;
}

//called when we detach the cheat, frees the hooks and restores them to their original state
void nHooks::free()
{
	sDetours.free_hooks();
}