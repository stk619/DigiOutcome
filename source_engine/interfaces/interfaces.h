#pragma once
//interface file list
#include "list/IBaseClientDll.h"
#include "list/IClientEntityList.h"
#include "list/IGlobalVarsBase.h"
#include "list/IInterfaceSystem.h"
#include "list/ISurface.h"
#include "list/IVEngineClient.h"

namespace nInterfaces
{
	//no freeing required as we're not modifiying anything that'll need a form of detachment
	bool allocate();

	//interfaces listed here. [sorted alphabetically]
	inline IBaseClientDll* ptrClient;
	inline IClientEntityList* ptrEntityList;
	inline IGlobalVarsBase* ptrGlobalVars;
	inline IInputSystem* ptrInputSystem;
	inline ISurface* ptrSurface;
	inline IVEngineClient* ptrEngine;
}