#include "../hooks.h"
//used in: menu state
#include "../../../main/menu/menu.h"

//override view handles the majority of viewmodel related functions, in our case
//this will only be used to modify fov values.

void __fastcall nHooks::override_view(void* ecx, void* edx, viewsetup_t* ptrViewsetup)
{
	static void(__fastcall * oOverrideView)(void* ecx, void* edx, viewsetup_t * ptrViewsetup) = sDetours.get_original<decltype(&nHooks::override_view)>(xorstr_("OverrideView"));

	//get local player
	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return oOverrideView(ecx, edx, ptrViewsetup);
	if (!ptrLocalPlayer->isalive())
		return oOverrideView(ecx, edx, ptrViewsetup);

	//make sure we're not trying to change things when zoomed in
	if (!ptrLocalPlayer->get_scoped())
	{
		//modify fov, logically we should be able to modify the viewmodel fov here too.
		//but viewmodelfov is some sort of derivative from the fov, calculated after
		//override view is called, however, hooking get_viewmodel_fov and returning our
		//desired value will work. 90.0f is also the games base fov value
		ptrViewsetup->flFov = 90.0f + nMenu::ptrFovSlider->GetValue();
	}

	//this needs to be called as it prevents thirdperson from breaking
	oOverrideView(ecx, edx, ptrViewsetup);
}