#include "../hooks.h"

void __fastcall nHooks::lock_cursor(ISurface* ecx, void* edx)
{
	static void(__fastcall * oLockCursor)(ISurface * ecx, void* edx) = sDetours.get_original<decltype(&nHooks::lock_cursor)>("LockCursor");

	if (!nConfiguration::sMenu.bOpened)
	{
		nInterfaces::ptrInputSystem->enable_input(true);
		return oLockCursor(ecx, edx);
	}

	//lock game input
	nInterfaces::ptrInputSystem->enable_input(false);
	//keep mouse input available though
	ecx->unlock_cursor();
}