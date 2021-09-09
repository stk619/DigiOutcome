#include "renderer.h"
//used in: console logging
#include "../console/console.h"
//used in: surface rendering utiltiies
#include "../../source_engine/interfaces/interfaces.h"

//simple renderer wrapper container generic shapes and lines, realistically we should be using directx 
//however i'm trying to keep this as minimalistic as possible and directx takes a little to set up but would
//allow for easy transfer to other games if i were to make software for another game. however this is just easier to
//do as valve have done it already

bool nRender::allocate()
{
	FGUI::RENDER.CreateFont = nRender::create_font;
	FGUI::RENDER.Text = nRender::text;
	FGUI::RENDER.Rectangle = nRender::rectangle;
	FGUI::RENDER.Outline = nRender::outlined_rectangle;
	FGUI::RENDER.Line = nRender::line;
	FGUI::RENDER.Gradient = nRender::gradient;
	FGUI::RENDER.GetTextSize = nRender::text_size;
	FGUI::RENDER.GetScreenSize = nRender::screen_size;

	nRender::create_font(nRender::ulMuseoSans, xorstr_("Museo Sans"), 12, eFontFlags::FONTFLAG_DROPSHADOW, 0);

	sConsole.log(eLogType::MAIN, xorstr_("renderer finished allocating"));
	return true;
}

void nRender::create_font(FGUI::FONT& ulFont, std::string szFontFamily, int iSize, int iFlags, bool bBold)
{
	ulFont = nInterfaces::ptrSurface->create_font();
	nInterfaces::ptrSurface->set_font_glyph_set(ulFont, szFontFamily.c_str(), iSize, bBold ? 800 : 0, 0, 0, iFlags);
}

void nRender::text(int iX, int iY, FGUI::FONT ulFont, FGUI::COLOR sColour, std::string szText)
{
	//simple char -> wchar_t conversion as nInterfaces::ptrSurface->draw_text() wants it
	std::wstring szConvertedText = std::wstring(szText.begin(), szText.end());
	nInterfaces::ptrSurface->text_font(ulFont);
	nInterfaces::ptrSurface->font_colour(sColour.m_ucRed, sColour.m_ucGreen, sColour.m_ucBlue, sColour.m_ucAlpha);
	nInterfaces::ptrSurface->text_position(iX, iY);
	nInterfaces::ptrSurface->draw_text(szConvertedText.data(), szText.size());
}

void nRender::rectangle(int iX, int iY, int iWidth, int iHeight, FGUI::COLOR sColour)
{
	nInterfaces::ptrSurface->set_colour(sColour.m_ucRed, sColour.m_ucGreen, sColour.m_ucBlue, sColour.m_ucAlpha);
	nInterfaces::ptrSurface->filled_rect(iX, iY, iX + iWidth, iY + iHeight);
}

void nRender::outlined_rectangle(int iX, int iY, int iWidth, int iHeight, FGUI::COLOR sColour)
{
	nInterfaces::ptrSurface->set_colour(sColour.m_ucRed, sColour.m_ucGreen, sColour.m_ucBlue, sColour.m_ucAlpha);
	nInterfaces::ptrSurface->outlined_rect(iX, iY, iX + iWidth, iY + iHeight);
}

void nRender::line(int iX, int iY, int iEndX, int iEndY, FGUI::COLOR sColour)
{
	nInterfaces::ptrSurface->set_colour(sColour.m_ucRed, sColour.m_ucGreen, sColour.m_ucBlue, sColour.m_ucAlpha);
	nInterfaces::ptrSurface->line(iX, iY, iEndX, iEndY);
}

void nRender::gradient(int iX, int iY, int iWidth, int iHeight, FGUI::COLOR sColour1, FGUI::COLOR sColour2, bool bHorizontal)
{
	nInterfaces::ptrSurface->set_colour(sColour1.m_ucRed, sColour1.m_ucGreen, sColour1.m_ucBlue, sColour1.m_ucAlpha);
	nInterfaces::ptrSurface->filled_rect_fade(iX, iY, iX + iWidth, iY + iHeight, 255, 255, bHorizontal);

	nInterfaces::ptrSurface->set_colour(sColour2.m_ucRed, sColour2.m_ucGreen, sColour2.m_ucBlue, sColour2.m_ucAlpha);
	nInterfaces::ptrSurface->filled_rect_fade(iX, iY, iX + iWidth, iY + iHeight, 0, 255, bHorizontal);
}

FGUI::DIMENSION nRender::text_size(FGUI::FONT ulFont, std::string szText)
{
	//simple wchar_t* convertion as nInterfaces::ptrSurface->get_text_size() requires it
	std::wstring szConvertedText = std::wstring(szText.begin(), szText.end());
	
	//placeholders for our text size
	int iWidth;
	int iHeight;

	nInterfaces::ptrSurface->get_text_size(ulFont, szConvertedText.data(), iWidth, iHeight);

	//returns our x, y vector coords
	return { iWidth, iHeight };
}

FGUI::DIMENSION nRender::screen_size()
{
	int iWidth;
	int iHeight;
	nInterfaces::ptrSurface->screen_size(iWidth, iHeight);
	return { iWidth, iHeight };
}