//used in: logging events as well as attachment and detachment
#include "other/console/console.h"
//used in: interface attachments
#include "source_engine/interfaces/interfaces.h"

HMODULE hGlobalModule = NULL;

DWORD WINAPI attach(void* ptrParameter)
{
	try
	{
		if (hGlobalModule == NULL)
			return false;

		//wait for serverbrowser.dll to be loaded, this is always the last module loaded into csgo, can be seen when 
		//attaching a debugger to the csgo process, this is here as another "null check"
		while (GetModuleHandleA("serverbrowser.dll") == NULL)
			std::this_thread::sleep_for(std::chrono::milliseconds(250));

		const std::chrono::high_resolution_clock::time_point attachmentStart = std::chrono::high_resolution_clock::now();

#ifdef _DEBUG

		sConsole.attach("csgo.assistant");
		sConsole.log(eLogType::LOG, "csgo.assistant console attached");

#endif // !_DEBUG

		if (!nInterfaces::allocate())
			sConsole.log(eLogType::ERR, "interfaces failed to load");

		nInterfaces::ptrEngine->execute_command_unrestricted("clear");
		nInterfaces::ptrEngine->execute_command_unrestricted("echo sex");
		nInterfaces::ptrEngine->execute_command_unrestricted("echo is");
		nInterfaces::ptrEngine->execute_command_unrestricted("echo weird");

		//calculates rough time of attachment
		const std::chrono::high_resolution_clock::time_point attachmentEnd = std::chrono::high_resolution_clock::now();
		const double dTimeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(attachmentEnd - attachmentStart).count();

		sConsole.log(eLogType::MISC, "attachment time taken: %0.3fs", dTimeDifference);
	}
	catch (std::exception& cException)
	{
		//make a message box appear, then exit the thread
		MessageBoxW(NULL, LPCWSTR(cException.what()), L"ERROR", MB_ICONERROR | MB_OK);
		FreeLibraryAndExitThread(hGlobalModule, EXIT_FAILURE);
	}

	//force the program to sit in a while loop until the uninject key is pressed, in this case end
	//otheriwse we sit here.
	while (!GetAsyncKeyState(VK_END)) //NOTE: this should be changed to Valve's input system, not Microsoft's
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

	FreeLibraryAndExitThread(hGlobalModule, EXIT_SUCCESS);

	//need to return something -_-
	return true;
}

void detach()
{
	//detach and unload everything
	sConsole.detach();

	//beep and indicate console has been unloaded
	Beep(500, 500);
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwCallReason, LPVOID lpParameter)
{
	//disables the DLL_THREAD_ATTACH and DLL_THREAD_DETACH notifications, as we're not using either
	DisableThreadLibraryCalls(hModule);

	//global instance of the module
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