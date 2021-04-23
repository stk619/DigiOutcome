#include "interfaces.h"
//used in: logging interface status
#include "../../other/console/console.h"
//used in: interface mangement
#include "../../other/utilities/utilities.h"

bool nInterfaces::allocate()
{
	ptrEngine = nUtilities::get_interface<IVEngineClient>("engine.dll", "VEngineClient014");
	if (ptrEngine == nullptr)
		return false;
	sConsole.log(eLogType::LOG, "IVEngineClient found at address: 0x%x", ptrEngine);

	//finished loading the interfaces? no need to be here, return true
	sConsole.log(eLogType::LOG, "interfaces finished loading");
	return true;
}