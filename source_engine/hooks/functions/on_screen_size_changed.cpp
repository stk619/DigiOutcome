#include "../hooks.h"
//used in: menu reinitialization
#include "../../../main/menu/menu.h"

//https://www.unknowncheats.me/forum/counterstrike-global-offensive/338901-alternative-checking.html
//solutions to the problem found here. this function is only called when the user changes their screen resolution
//we simply free the renderer, nulling out the fonts for any lingering variables we then reset the games font state
//then reallocate the renderer

void __fastcall nHooks::on_screen_size_changed(ISurface* ecx, void* edx, int iWidth, int iHeight)
{
	static void(__fastcall * oOnScreenSizeChanged)(ISurface * ecx, void* edx, int iWidth, int iHeight) = sDetours.get_original<decltype(&nHooks::on_screen_size_changed)>(xorstr_("OnScreenSizeChanged"));
	oOnScreenSizeChanged(ecx, edx, iWidth, iHeight);

	//reset surface font caches, this wouldn't work if we changed to a directx renderer, not that
	//it would matter considering we wouldn't hook this function to begin with when using directx.
	ecx->reset_font_caches();

	//reinitialize menu
	if (!nMenu::allocate())
		sConsole.log(eLogType::ERR, "menu failed to reinitialize on screen size change");
}