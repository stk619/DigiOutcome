#include "../hooks.h"
//used in: menu state
#include "../../../main/menu/menu.h"
//used in: call locations to features
#include "../../../main/features/features.h"

//createmove is only ever called whilst in game
bool __fastcall nHooks::create_move(void* ecx, void* edx, float flInputSampleTime, usercmd_t* ptrCmd)
{
	static bool(__fastcall *oCreateMove)(void* ecx, void* edx, float flInputSampleTime, usercmd_t* ptrCmd) = sDetours.get_original<decltype(&nHooks::create_move)>(xorstr_("CreateMove"));

	baseplayer_t* ptrLocalPlayer = reinterpret_cast<baseplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return oCreateMove(ecx, edx, flInputSampleTime, ptrCmd);

	//disable attacking buttons if the menu is opened
	if (nMenu::ptrMainWindow->GetState())
		ptrCmd->iButtons &= ~(IN_ATTACK | IN_ATTACK2);

	nMiscellaneous::bhop(ptrCmd);

	//simple exploit that allows us to bypass the duck delay
	if (nMenu::ptrInfiniteDuckCheckbox->GetState())
		ptrCmd->iButtons |= IN_BULLRUSH;

	return oCreateMove(ecx, edx, flInputSampleTime, ptrCmd);
}