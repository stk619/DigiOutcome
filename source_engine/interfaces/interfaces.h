#pragma once
//interface file list
#include "list/IBaseClientDll.h"
#include "list/IClientEntityList.h"
#include "list/IDebugOverlay.h"
#include "list/IEngineSounds.h"
#include "list/IVGameEventManager.h"
#include "list/IGlobalVarsBase.h"
#include "list/IInputSystem.h"
#include "list/ILocalize.h"
#include "list/IMaterialSystem.h"
#include "list/IVModelInfo.h"
#include "list/ISurface.h"
#include "list/IStudioRender.h"
#include "list/IVEngineClient.h"
#include "list/IViewRenderBeams.h"

namespace nInterfaces
{
	//no freeing required as we're not modifiying anything that'll need a form of detachment
	bool allocate();

	//interfaces listed here. [sorted alphabetically]
	inline IBaseClientDll* ptrClient;
	inline IClientEntityList* ptrEntityList;
	inline IDebugOverlay* ptrDebugOverlay;
	inline IEngineSounds* ptrEngineSounds;
	inline IVGameEventManager2* ptrGameEventManager;
	inline IGlobalVarsBase* ptrGlobalVars;
	inline IInputSystem* ptrInputSystem;
	inline ILocalize* ptrLocalize;
	inline IMaterialSystem* ptrMaterialSystem;
	inline IVModelInfo* ptrModelInfo;
	inline IStudioRender* ptrStudioRender;
	inline ISurface* ptrSurface;
	inline IVEngineClient* ptrEngine;
	inline IViewRenderBeams* ptrRenderBeams;
}