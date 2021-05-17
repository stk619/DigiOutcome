#pragma once
#include "../../common_includes.h"
//used in: thirdperson hook
#include "../definitions/clientmode_input.h"
//used in: hooking method
#include "../../other/utilities/detours.h"
//used in: general interface usage in hooks
#include "../interfaces/interfaces.h"
//used in: rendering of our visuals and menu
#include "../../other/renderer/renderer.h"
//used in: create move hook
#include "../definitions/usercmd.h"
//used in: signature scanning
#include "../../other/utilities/utilities.h"

namespace nHooks
{
	bool allocate();
	void free();

	//prototypes
	//client.dll
	extern void __fastcall cam_think(clientmode_input_t* ecx, void* edx);
	extern void __fastcall cam_to_thirdperson(clientmode_input_t* ecx, void* edx);
	extern bool __fastcall create_move(void* ecx, void* edx, float flInputSampleTime, usercmd_t* sCmd);
	extern float __fastcall viewmodel_fov(void* ecx, void* edx);

	//vguimatsurface.dll
	extern void __fastcall lock_cursor(ISurface* ecx, void* edx);

	//engine.dll
	extern void __fastcall paint(void* ecx, void* edx, int iPaintMode);
}