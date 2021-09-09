#pragma once
#include "../../common_includes.h"

#define FGUI_IMPLEMENTATION
#include "../../main/FGUI/FGUI.h"

namespace nRender
{
	bool allocate();

	inline FGUI::FONT ulMuseoSans;

	void create_font(FGUI::FONT& ulFont, std::string szFontFamily, int iSize, int iFlags, bool bBold);
	void text(int iX, int iY, FGUI::FONT ulFont, FGUI::COLOR sColour, std::string szText);
	void rectangle(int iX, int iY, int iWidth, int iHeight, FGUI::COLOR sColour);
	void outlined_rectangle(int iX, int iY, int iWidth, int iHeight, FGUI::COLOR sColour);
	void line(int iX, int iY, int iEndX, int iEndY, FGUI::COLOR sColour);
	void gradient(int iX, int iY, int iWidth, int iHeight, FGUI::COLOR sColour1, FGUI::COLOR sColour2, bool bHorizontal = false);
	FGUI::DIMENSION text_size(FGUI::FONT ulFont, std::string szText);
	FGUI::DIMENSION screen_size();
}