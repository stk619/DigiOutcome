#include "../hooks.h"
//used in: local player
#include "../../entities/base_csplayer.h"

//createmove is only ever called whilst in game
bool __fastcall nHooks::create_move(void* ecx, void* edx, float flInputSampleTime, usercmd_t* sCmd)
{
	//auto is for stupid people :D-
	static bool(__fastcall *oCreateMove)(void* ecx, void* edx, float flInputSampleTime, usercmd_t* sCmd) = sDetours.get_original<decltype(&nHooks::create_move)>(xorstr_("CreateMove"));

	baseplayer_t* ptrLocalPlayer = reinterpret_cast<baseplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return oCreateMove(ecx, edx, flInputSampleTime, sCmd);

	//NOTE: should be in a featrues file
	if (true) //bhop checkbox
	{
		int iMoveType = ptrLocalPlayer->get_movetype();
		if ((iMoveType == MOVETYPE_LADDER) || (iMoveType == MOVETYPE_NOCLIP))
			return oCreateMove(ecx, edx, flInputSampleTime, sCmd);

		if ((sCmd->iButtons & IN_JUMP) && !(ptrLocalPlayer->get_flags() & FL_ONGROUND))
			sCmd->iButtons &= ~IN_JUMP;
	}

	//simple exploit that allows us to bypass the duck delay
	sCmd->iButtons |= IN_BULLRUSH;

	return oCreateMove(ecx, edx, flInputSampleTime, sCmd);
}