#pragma once

//interface file list
#include "list/IVEngineClient.h"
namespace nInterfaces
{
	//no detachment required as we're not modifiying anything that'll need a form of detachment
	bool allocate();

	//interfaces listed here. [sorted alphabetically]
	inline IVEngineClient* ptrEngine;
}