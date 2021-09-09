#include "../hooks.h"
//used in: menu variables
#include "../../../main/menu/menu.h"

//similar to the cam_think hook, all this does is make sure we've got enough distance in thirdperson
//so it doesn't look like we're right up against our players head.
void __fastcall nHooks::cam_to_thirdperson(clientmode_input_t* ecx, void* edx)
{
	//get and call original as we're modifying the values of ecx
	static void(__fastcall * oCamToThirdperson)(clientmode_input_t * ecx, void* edx) = sDetours.get_original<decltype(&nHooks::cam_to_thirdperson)>(xorstr_("CamToThirdperson"));
	oCamToThirdperson(ecx, edx);

	//force first person if we're dead, bugs out spectator otherwise
	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return oCamToThirdperson(ecx, edx);
	if (!ptrLocalPlayer->isalive())
		return oCamToThirdperson(ecx, edx);

	//this puts our camera 250 hammer units away from our player
	//this with a fov changer can result in some weird looking thirdperson camera angles
	ecx->vecCameraOffset.tZ = nMenu::ptrThirdpersonDistSlider->GetValue();
}