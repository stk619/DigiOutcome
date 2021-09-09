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

	//vguimatsurface.dll
	ptrSurface = nUtilities::get_interface<ISurface>(xorstr_("vguimatsurface.dll"), xorstr_("VGUI_Surface031"));
	if (ptrSurface == nullptr)
		return false;

	//engine.dll
	ptrEngine = nUtilities::get_interface<IVEngineClient>(xorstr_("engine.dll"), xorstr_("VEngineClient014"));
	if (ptrEngine == nullptr)
		return false;
	
	ptrGameEventManager = nUtilities::get_interface<IVGameEventManager2>(xorstr_("engine.dll"), xorstr_("GAMEEVENTSMANAGER002"));
	if (ptrGameEventManager == nullptr)
		return false;

	ptrDebugOverlay = nUtilities::get_interface<IDebugOverlay>(xorstr_("engine.dll"), xorstr_("VDebugOverlay004"));
	if (ptrDebugOverlay == nullptr)
		return false;

	ptrModelInfo = nUtilities::get_interface<IVModelInfo>(xorstr_("engine.dll"), xorstr_("VModelInfoClient004"));
	if (ptrModelInfo == nullptr)
		return false;

	ptrEngineSounds = nUtilities::get_interface<IEngineSounds>(xorstr_("engine.dll"), xorstr_("IEngineSoundClient003"));
	if (ptrEngineSounds == nullptr)
		return false;

	//inputsystem.dll
	ptrInputSystem = nUtilities::get_interface<IInputSystem>(xorstr_("inputsystem.dll"), xorstr_("InputSystemVersion001"));
	if (ptrInputSystem == nullptr)
		return false;

	//localize.dll
	ptrLocalize = nUtilities::get_interface<ILocalize>(xorstr_("localize.dll"), xorstr_("Localize_001"));
	if (ptrLocalize == nullptr)
		return false;

	//materialsystem.dll
	ptrMaterialSystem = nUtilities::get_interface<IMaterialSystem>(xorstr_("materialsystem.dll"), xorstr_("VMaterialSystem080"));
	if (ptrMaterialSystem == nullptr)
		return false;

	//studiorender.dll
	ptrStudioRender = nUtilities::get_interface<IStudioRender>(xorstr_("studiorender.dll"), xorstr_("VStudioRender026"));
	if (ptrStudioRender == nullptr)
		return false;

	//custom interfaces, these will be manually logged
	ptrGlobalVars = **reinterpret_cast<IGlobalVarsBase***>((*reinterpret_cast<uintptr_t**>(nInterfaces::ptrClient)[0] + 0x1F));
	if (ptrGlobalVars == nullptr)
		return false;
	sConsole.log(eLogType::LOG, xorstr_("found interface: IGlobalVarsBase in module: client.dll at address: 0x%x"), ptrGlobalVars);

	ptrRenderBeams = *reinterpret_cast<IViewRenderBeams**>(nUtilities::find_signature(xorstr_("client.dll"), xorstr_("B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9")) + 0x1);
	if (ptrRenderBeams == nullptr)
		return false;
	sConsole.log(eLogType::LOG, xorstr_("found interface: IViewRenderBeams in module: client.dll at address: 0x%x"), ptrRenderBeams);

	//finished loading the interfaces? no need to be here, return true
	sConsole.log(eLogType::MAIN, xorstr_("interfaces finished allocating"));
	return true;
}