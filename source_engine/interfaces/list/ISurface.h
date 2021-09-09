#pragma once
//used in: hfont obtaining
#include "../../definitions/general_defines.h"
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

struct ISurface
{
private:
	enum eIndices
	{
		DRAWSETCOLOUR = 15,
		DRAWFILLEDRECT = 16,
		DRAWOUTLINEDRECT = 18,
		DRAWLINE = 19,
		SETTEXTFONT = 23,
		SETTEXTCOLOUR = 25,
		SETTEXTPOSITION = 26,
		DRAWTEXT = 28,
		GETSCREENSIZE = 44,
		UNLOCKCURSOR = 66,
		CREATEFONT = 71,
		SETFONTGLYPHSET = 72,
		GETTEXTSIZE = 79,
		PLAYSOUND = 82,
		GETCURSORPOSITION = 100,
		DRAWFILLEDRECTFADE = 123,
		RESETFONTCACHES = 141,
	};
public:
	void set_colour(int iRed, int iGreen, int iBlue, int iAlpha)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int, int, int, int)>(this, DRAWSETCOLOUR)(this, iRed, iGreen, iBlue, iAlpha);
	}
	void filled_rect(int iX, int iY, int iWidth, int iHeight)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int, int, int, int)>(this, DRAWFILLEDRECT)(this, iX, iY, iWidth, iHeight);
	}
	void outlined_rect(int iX, int iY, int iWidth, int iHeight)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int, int, int, int)>(this, DRAWOUTLINEDRECT)(this, iX, iY, iWidth, iHeight);
	}
	void line(int iX, int iY, int iWidth, int iHeight)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int, int, int, int)>(this, DRAWLINE)(this, iX, iY, iWidth, iHeight);
	}
	void text_font(unsigned int uiFont)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, unsigned int)>(this, SETTEXTFONT)(this, uiFont);
	}
	void font_colour(int iRed, int iGreen, int iBlue, int iAlpha)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int, int, int, int)>(this, SETTEXTCOLOUR)(this, iRed, iGreen, iBlue, iAlpha);
	}
	void text_position(int iX, int iY)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int, int)>(this, SETTEXTPOSITION)(this, iX, iY);
	}
	void draw_text(const wchar_t* szText, int iTextLength, int iDrawType = 0)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, const wchar_t*, int, int)>(this, DRAWTEXT)(this, szText, iTextLength, iDrawType);
	}
	void screen_size(int& iWidth, int& iHeight)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int&, int&)>(this, GETSCREENSIZE)(this, iWidth, iHeight);
	}
	void unlock_cursor()
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*)>(this, UNLOCKCURSOR)(this);
	}
	unsigned int create_font()
	{
		return nUtilities::vfunc<unsigned int(__thiscall*)(ISurface*)>(this, CREATEFONT)(this);
	}
	bool set_font_glyph_set(unsigned long uiFont, const char* szFontFamily, int iHeight, int iWeight, int iBlur, int iScanlines, int iFlags, int iRangeMin = 0, int iRangeMax = 0)
	{
		return nUtilities::vfunc<bool(__thiscall*)(ISurface*, unsigned long, const char*, int, int, int, int, int, int, int)>(this, SETFONTGLYPHSET)(this, uiFont, szFontFamily, iHeight, iWeight, iBlur, iScanlines, iFlags, iRangeMin, iRangeMax);
	}
	void get_text_size(unsigned int uiFont, const wchar_t* szText, int& iWidth, int& iHeight)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, unsigned int, const wchar_t*, int&, int&)>(this, GETTEXTSIZE)(this, uiFont, szText, iWidth, iHeight);
	}
	void play_sound(const char* szFileName)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, const char*)>(this, PLAYSOUND)(this, szFileName);
	}
	void filled_rect_fade(int iX, int iY, int iWidth, int iHeight, uint32_t iColour1, uint32_t iColour2, bool bHorizontal = false)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int, int, int, int, uint32_t, uint32_t, bool)>(this, DRAWFILLEDRECTFADE)(this, iX, iY, iWidth, iHeight, iColour1, iColour2, bHorizontal);
	}
	void get_cursor_pos(int& iX, int& iY)
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*, int&, int&)>(this, GETCURSORPOSITION)(this, iX, iY);
	}
	void reset_font_caches()
	{
		return nUtilities::vfunc<void(__thiscall*)(ISurface*)>(this, RESETFONTCACHES)(this);
	}

	//external functions - these need the ISurface thisptr hence why they're here could probably just pass the 
	//ISurface.h file to our renderer where these should be then just use the ISurface pointer itself but like
	//no :D
	void begin_drawing()
	{
		typedef void(__thiscall* begin_drawing_fn)(void*);
		static begin_drawing_fn oBeginDrawing = reinterpret_cast<begin_drawing_fn>(nUtilities::find_signature(xorstr_("vguimatsurface.dll"), xorstr_("55 8B EC 83 E4 C0 83 EC 38")));

		return oBeginDrawing(this);
	}
	void end_drawing()
	{
		typedef void(__thiscall* end_drawing_fn)(void*);
		static end_drawing_fn oEndDrawing = reinterpret_cast<end_drawing_fn>(nUtilities::find_signature(xorstr_("vguimatsurface.dll"), xorstr_("8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?")));

		return oEndDrawing(this);
	}
};