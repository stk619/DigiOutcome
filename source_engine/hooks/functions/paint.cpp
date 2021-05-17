#include "../hooks.h"
//used in: menu input
#include "../../../other/input/input.h"
//used in: rendering menu
#include "../../main/menu/menu.h"

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
			//30px down because i use nvidias stupid fps counter in the top left, test code anyways
			if (sInput.toggle_key(VK_INSERT, nConfiguration::sMenu.bOpened))
				nRender::text(10, 30, xorstr_("csgo.assistant"), colour_t(255, 255, 255, 255), nRender::uiTahoma);

			if (sInput.mouse_in_boundaries(20, 20, 100, 100))
			{
				nRender::outlined_rectangle(20, 20, 100, 100, colour_t(255, 255, 255, 255));
				nRender::text(10, 50, xorstr_("mouse is in boundaries"), colour_t(255, 255, 255, 255), nRender::uiTahoma);
			}
			//run our esp code
			//nVisuals::allocate();
			//run our menu code
			//nMenu::allocate();
		}
		nInterfaces::ptrSurface->end_drawing();
	}

	return oPaint(ecx, edx, iPaintMode);
}