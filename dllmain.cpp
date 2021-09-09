//used in: menu initialization
#include "main/menu/menu.h"
//used in: logging events as well as attachment and detachment
#include "other/console/console.h"
//used in: input allocation
#include "other/input/input.h"
//used in: renderer allocation
#include "other/renderer/renderer.h"
//used in: netvar allocation
#include "other/netvars/netvars.h"
//used in: event allocation
#include "other/events/event_manager.h"
//used in: interface attachments
#include "source_engine/interfaces/interfaces.h"
//used in: hook management
#include "source_engine/hooks/hooks.h"

HMODULE hGlobalModule = NULL;

DWORD WINAPI attach(void* ptrParameter)
{
	try
	{
		if (hGlobalModule == NULL)
			return false;

		//wait for serverbrowser.dll to be loaded, this is always the last module loaded into csgo, can be seen when 
		//attaching a debugger to the csgo process
		while (GetModuleHandleA(xorstr_("serverbrowser.dll")) == NULL)
			std::this_thread::sleep_for(std::chrono::milliseconds(250));

		const std::chrono::high_resolution_clock::time_point cAttachmentStart = std::chrono::high_resolution_clock::now();

#ifdef _DEBUG
		sConsole.attach(xorstr_("csgo.assistant"));
		sConsole.log(eLogType::MAIN, xorstr_("csgo.assistant console attached"));
#endif // !_DEBUG

		if (!nInterfaces::allocate())
			sConsole.log(eLogType::ERR, xorstr_("interfaces failed to allocate"));

		if (!nInput::allocate())
			sConsole.log(eLogType::ERR, xorstr_("input failed to allocate"));

		if (!nRender::allocate())
			sConsole.log(eLogType::ERR, xorstr_("renderer failed to allocate"));

		if (!nMenu::allocate())
			sConsole.log(eLogType::ERR, xorstr_("menu failed to allocate"));

		if (!nNetvarManager::allocate())
			sConsole.log(eLogType::ERR, xorstr_("netvars failed to allocate"));

#ifdef _DEBUG
		const std::chrono::high_resolution_clock::time_point cHooksStartTime = std::chrono::high_resolution_clock::now();
#endif // !_DEBUG

		if (!nHooks::allocate())
			sConsole.log(eLogType::ERR, xorstr_("hooks failed to allocate"));

#ifdef _DEBUG
		const double dHooksTimeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - cHooksStartTime).count();
		sConsole.log(eLogType::DEBUG, xorstr_("hooks allocated in: %0.3fs"), dHooksTimeDifference);
#endif // !_DEBUG

		if (!sGameEventImplementation.allocate())
			sConsole.log(eLogType::ERR, xorstr_("events failed to allocate"));

		//calculates rough time of attachment, this isn't precise entirely, it's only used to give a rough estimation as to how long
		//the cheat takes to allocate itself hence the logs at specific points. with these calculations and logs this will also create
		//a longer allocation time as logging and time calculation functions seem to take up a considerable amount especially with the
		//amount used here
#ifdef _DEBUG
		const std::chrono::high_resolution_clock::time_point cAttachmentEnd = std::chrono::high_resolution_clock::now();
		const double dTimeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(cAttachmentEnd - cAttachmentStart).count();
		sConsole.log(eLogType::DEBUG, xorstr_("cheat allocated in: %0.3fs"), dTimeDifference);
#endif
	}
	catch (std::exception& cException) //simple error handler
	{
		MessageBoxW(NULL, LPCWSTR(cException.what()), xorstr_(L"ERROR"), MB_ICONERROR | MB_OK);
		FreeLibraryAndExitThread(hGlobalModule, EXIT_FAILURE);
	}

#ifdef _DEBUG

	//force the program to sit in a while loop until the uninject key is pressed
	while (!nInput::key_pressed(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(hGlobalModule, EXIT_SUCCESS);

#endif // _DEBUG

	//need to return something -_-
	return true;
}

void detach()
{
	nHooks::free();
	sGameEventImplementation.free();

	//free the console last as this if we have any unload messages in the aforementioned called functions
	//(i.e nRender::free()) this will cause a crash on unload as logging events whilst the console doesn't
	//exist doesn't work :D
	sConsole.free();

	//beep as an indication the cheat has been detached
	Beep(500, 500);
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwCallReason, LPVOID lpParameter)
{
	//disables the DLL_THREAD_ATTACH and DLL_THREAD_DETACH notifications, as we're not using either
	DisableThreadLibraryCalls(hModule);

	//global instance of the module, used for detachment
	hGlobalModule = hModule;

	if (dwCallReason == DLL_PROCESS_ATTACH)
	{
		//create our cheat thread
		HANDLE hThread = CreateThread(NULL, 0, attach, lpParameter, 0, NULL);

		if (!hThread)
			return false;

		CloseHandle(hThread);

		return true;
	}
	else if (dwCallReason == DLL_PROCESS_DETACH)
	{
		detach();

		return true;
	}

	//if we reach this, the dll failed to inject
	return false;
}