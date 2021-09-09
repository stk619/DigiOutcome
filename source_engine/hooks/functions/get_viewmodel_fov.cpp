#include "../hooks.h"
//used in: menu variables
#include "../../../main/menu/menu.h"

float __fastcall nHooks::get_viewmodel_fov()
{
	static float(__fastcall * oGetViewmodelFov)() = sDetours.get_original<decltype(&nHooks::get_viewmodel_fov)>(xorstr_("GetViewmodelFov"));

	//get local player
	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return oGetViewmodelFov();
	if (!ptrLocalPlayer->isalive())
		return oGetViewmodelFov();

	//make sure we're not trying to change things when zoomed in
	if (ptrLocalPlayer->get_scoped())
		return oGetViewmodelFov();

	return 68.0f + nMenu::ptrFovViewmodelSlider->GetValue();
}