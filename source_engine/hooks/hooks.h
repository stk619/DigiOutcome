#pragma once
#include "../../common_includes.h"
//used in: override view hook
#include "../definitions/viewsetup.h"
//used in: create move hook
#include "../definitions/usercmd.h"
//used in: entity management
#include "../entities/entities.h"
//used in: thirdperson hook
#include "../definitions/clientmode_input.h"
//used in: drawmodel hook
#include "../definitions/modelrenderinfo.h"
//used in: general interface usage in hooks
#include "../interfaces/interfaces.h"
//used in: hooking method
#include "../../other/utilities/detours.h"
//used in: rendering of our visuals and menu
#include "../../other/renderer/renderer.h"
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
	extern bool __fastcall create_move(void* ecx, void* edx, float flInputSampleTime, usercmd_t* ptrCmd);
	extern void __fastcall override_view(void* ecx, void* edx, viewsetup_t* ptrViewsetup);
	extern float __fastcall get_viewmodel_fov(); //no need to pass registers
	extern bool __cdecl glow_effect_spectator(basecsplayer_t* ptrEntity, basecsplayer_t* ptrLocalPlayer, eGlowRenderStyle& sGlowRenderStyle, vector3d_t<float>& vecGlowColour, float& flAlphaStart, float& flAlpha, float& flTimeStart, float& flTimeTarget, bool& bAnimate);

	//vguimatsurface.dll
	extern void __fastcall lock_cursor(ISurface* ecx, void* edx);
	
	//engine.dll
	extern void __fastcall paint(void* ecx, void* edx, int iPaintMode);

	//studiorender.dll
	extern void __fastcall draw_model(void* ecx, void* edx, void* ptrResults, modelrenderinfo_t& sModelInfo, matrix3x4_t* ptrBoneToWorld, float* flFlexWeights, float* flFlexDelayedRates, vector3d_t<float>& vecOrigin, int iFlags);

	//vfunc hooks
	//ISurface
	extern void __fastcall on_screen_size_changed(ISurface* ecx, void* edx, int iWidth, int iHeight);
}