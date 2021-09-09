#include "../hooks.h"
//used in: key toggling system
#include "../../../other/input/input.h"
//used in: menu state
#include "../../../main/menu/menu.h"

//literally the easiest method of thirdperson there is, we simply skip a few checks in the game itself
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/29e4c1fda9698d5cebcdaf1a0de4b829fa149bf8/game/client/in_camera.cpp#L297
//notably user.m_fCameraInThirdPerson on line 310 and line 328 which puts us in the 3rd person view, calling CAM_ToThirdPerson();
//credits: https://www.unknowncheats.me/forum/counterstrike-global-offensive/428036-easy-alternative-internal-third-person-basically-3-lines.html

void __fastcall nHooks::cam_think(clientmode_input_t* ecx, void* edx)
{
	static void(__fastcall * oCamThink)(clientmode_input_t * ecx, void* edx) = sDetours.get_original<decltype(&nHooks::cam_think)>(xorstr_("CamThink"));

	//force first person if we're dead, bugs out spectator otherwise
	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return oCamThink(ecx, edx);
	if (!ptrLocalPlayer->isalive())
		return oCamThink(ecx, edx);

	//bypass inital check
	ecx->bCamInThirdperson = false;
	//this puts our camera into thirdperson, calling Cam_ToThirdperson()
	ecx->iCamCommand = nMenu::ptrThirdPersonKeybinder->GetKey();

	return oCamThink(ecx, edx);
}