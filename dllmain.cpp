//used in: logging events as well as attachment and detachment
#include "other/console/console.h"
//used in: hook management
#include "source_engine/hooks/hooks.h"
//used in: input allocation
#include "other/input/input.h"
//used in: interface attachments
#include "source_engine/interfaces/interfaces.h"
//used in: renderer allocation
#include "other/renderer/renderer.h"
//used in: netvar allocation
#include "other/netvars/netvars.h"

HMODULE hGlobalModule = NULL;
HWND hGlobalWindow = NULL;

DWORD WINAPI attach(void* ptrParameter)
{
	try
	{
		if (hGlobalModule == NULL)
			return false;

		//wait for serverbrowser.dll to be loaded, this is always the last module loaded into csgo, can be seen when 
		//attaching a debugger to the csgo process
		while (GetModuleHandleA(xorstr_("serverbrowser.dll")) == NULL || !(hGlobalWindow = FindWindowA(xorstr_("Valve001"), nullptr)))
			std::this_thread::sleep_for(std::chrono::milliseconds(250));

		const std::chrono::high_resolution_clock::time_point attachmentStart = std::chrono::high_resolution_clock::now();

#ifdef _DEBUG

		sConsole.attach(xorstr_("csgo.assistant"));
		sConsole.log(eLogType::MAIN, xorstr_("csgo.assistant console attached"));

#endif // !_DEBUG

		if (!nInterfaces::allocate())
			sConsole.log(eLogType::ERR, xorstr_("interfaces failed to allocate"));

		if (!nHooks::allocate())
			sConsole.log(eLogType::ERR, xorstr_("hooks failed to allocate"));

		if (!sInput.allocate())
			sConsole.log(eLogType::ERR, xorstr_("input failed to allocate"));

		if (!nRender::allocate())
			sConsole.log(eLogType::ERR, xorstr_("renderer failed to allocate"));

		if (!nNetvarManager::allocate())
			sConsole.log(eLogType::ERR, xorstr_("netvars failed to allocate"));

		//calculates rough time of attachment
		const std::chrono::high_resolution_clock::time_point attachmentEnd = std::chrono::high_resolution_clock::now();
		const double dTimeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(attachmentEnd - attachmentStart).count();

		sConsole.log(eLogType::MISC, xorstr_("attachment time taken: %0.3fs"), dTimeDifference);
	}
	catch (std::exception& cException) //simple error handler
	{
		//make a message box appear, then exit the thread
		//NOTE: the message box is untested, the LPCWSTR contructor seems to print out text in chinese
		//		no idea what will happen with cException.what()
		MessageBoxW(NULL, LPCWSTR(cException.what()), xorstr_(L"ERROR"), MB_ICONERROR | MB_OK);
		FreeLibraryAndExitThread(hGlobalModule, EXIT_FAILURE);
	}

	//force the program to sit in a while loop until the uninject key is pressed
	while (!sInput.key_held(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(hGlobalModule, EXIT_SUCCESS);

	//need to return something -_-
	return true;
}

void detach()
{
	//detach and unload everything
	sConsole.detach();

	//free hooks, nInput frees the wndproc allocation
	nHooks::free();
	sInput.free();

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