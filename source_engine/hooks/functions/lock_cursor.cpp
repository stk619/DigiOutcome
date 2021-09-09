#include "../hooks.h"
//used in: menu state
#include "../../../main/menu/menu.h"

//cursor input handler
void __fastcall nHooks::lock_cursor(ISurface* ecx, void* edx)
{
	static void(__fastcall * oLockCursor)(ISurface * ecx, void* edx) = sDetours.get_original<decltype(&nHooks::lock_cursor)>(xorstr_("LockCursor"));

	if (!nMenu::ptrMainWindow->GetState())
		return oLockCursor(ecx, edx);

	//keep the cursor unlocked, unless menu is opened
	ecx->unlock_cursor();
}