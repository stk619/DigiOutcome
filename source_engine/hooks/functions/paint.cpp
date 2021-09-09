#include "../hooks.h"
//used in: rendering menu
#include "../../../main/menu/menu.h"
//used in: feature call locations
#include "../../../main/features/features.h"
//used in: menu input
#include "../../../other/input/input.h"

//a perk of this hook method seems to be that when we're in game in the buy menu the text and boxes don't get
//messed up when buying things or going through the buy menu. whereas in the paint traverse hook you'd use to 
//render in things weird artifacts would be caused when going through the buy menu.

void __fastcall nHooks::paint(void* ecx, void* edx, int iPaintMode)
{
	static void(__fastcall * oPaint)(void* ecx, void* edx, int iPaintMode) = sDetours.get_original<decltype(&nHooks::paint)>(xorstr_("Paint"));

	//check for the correct panel, i think gamepanels only draws in game, not too sure though
	if (iPaintMode & static_cast<int>(ePaintMode::PAINT_UIPANELS))
	{
		//need to draw our functions within the boundaries of the game
		nInterfaces::ptrSurface->begin_drawing();
		{
			nVisuals::tick();

			//render event related info
			nMiscellaneous::hitmarker_paint();
			nMiscellaneous::event_logger_paint();

			//render the container each frame
			nMenu::ptrMainWindow->Render();

			//stupid method of enabling input and disabling input
			if (!nInterfaces::ptrEngine->is_in_game() || !nInterfaces::ptrEngine->is_connected())
				nInterfaces::ptrInputSystem->enable_input(nMenu::ptrMainWindow->GetState() ? false : true);
			else
				nInterfaces::ptrInputSystem->enable_input(true);
		}
		nInterfaces::ptrSurface->end_drawing();
	}

	return oPaint(ecx, edx, iPaintMode);
}