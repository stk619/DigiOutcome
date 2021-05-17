#include "interfaces.h"
//used in: logging interface status
#include "../../other/console/console.h"
//used in: interface mangement
#include "../../other/utilities/utilities.h"

bool nInterfaces::allocate()
{
	//standard interfaces
	//client.dll
	ptrClient = nUtilities::get_interface<IBaseClientDll>(xorstr_("client.dll"), xorstr_("VClient018"));
	if (ptrClient == nullptr)
		return false;

	ptrEntityList = nUtilities::get_interface<IClientEntityList>(xorstr_("client.dll"), xorstr_("VClientEntityList003"));
	if (ptrEntityList == nullptr)
		return false;

	//inputsystem.dll
	ptrInputSystem = nUtilities::get_interface<IInputSystem>(xorstr_("inputsystem.dll"), xorstr_("InputSystemVersion001"));
	if (ptrInputSystem == nullptr)
		return false;

	//vguimatsurface.dll
	ptrSurface = nUtilities::get_interface<ISurface>(xorstr_("vguimatsurface.dll"), xorstr_("VGUI_Surface031"));
	if (ptrSurface == nullptr)
		return false;

	//engine.dll
	ptrEngine = nUtilities::get_interface<IVEngineClient>(xorstr_("engine.dll"), xorstr_("VEngineClient014"));
	if (ptrEngine == nullptr)
		return false;

	//custom interfaces, these will be manually logged
	//ptrGlobalVars = **nUtilities::vfunc<IGlobalVarsBase***>(ptrClient, 11) + 0x1F;
	ptrGlobalVars = **reinterpret_cast<IGlobalVarsBase***>((*reinterpret_cast<uintptr_t**>(nInterfaces::ptrClient)[0] + 0x1F));
	if (ptrGlobalVars == nullptr)
		return false;
	sConsole.log(eLogType::LOG, xorstr_("found interface: IGlobalVarsBase in module: client.dll at address: 0x%x"), ptrGlobalVars);

	//finished loading the interfaces? no need to be here, return true
	sConsole.log(eLogType::MAIN, xorstr_("interfaces finished allocating"));
	return true;
}