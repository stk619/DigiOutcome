#include "renderer.h"
//used in: console logging
#include "../console/console.h"
//used in: surface rendering utiltiies
#include "../../source_engine/interfaces/interfaces.h"

//simple renderer wrapper container generic shapes and lines, realistically we should be using directx 
//however i'm trying to keep this as minimalistic as possible and directx takes a little to set up but would
//allow for easy transfer to other games if i were to make software for another game. however this is just easier to
//do as valve have done it already, and i'm trying to keep this project as minimalistic as possible

bool nRender::allocate()
{
	//this is kind of unfortunate that we're using valve's surface wrapper as the fonts don't look as good
	//as if i was using directx, that and changing fonts whenever is a little harder.
	uiTahoma = nInterfaces::ptrSurface->create_font();
	if (!uiTahoma) //virtual function could fail here, resulting in a crash on font glyph set
		return false;
	if (!nInterfaces::ptrSurface->set_font_glyph_set(uiTahoma, xorstr_("Tahoma"), 11, FW_HEAVY, 0, 0, eFontFlags::FONTFLAG_DROPSHADOW))
		return false;
	sConsole.log(eLogType::LOG, xorstr_("font: tahoma, created"));


	sConsole.log(eLogType::MAIN, xorstr_("renderer finished allocating"));
	return true;
}

void nRender::text(int iX, int iY, std::string_view szText, colour_t sColour, hFont uiFont, bool bCentered)
{
	//simple char -> wchar_t conversion as nInterfaces::ptrSurface->draw_text() wants it
	std::wstring szConvertedText = std::wstring(szText.begin(), szText.end());
	
	//text size calculation
	vector2d_t vecTextSize = nRender::text_size(uiFont, szText.data());

	nInterfaces::ptrSurface->text_font(uiFont);
	nInterfaces::ptrSurface->font_colour(static_cast<int>(sColour.flRed), static_cast<int>(sColour.flGreen), static_cast<int>(sColour.flBlue), static_cast<int>(sColour.flAlpha));
	nInterfaces::ptrSurface->text_position(bCentered ? (iX - (static_cast<int>(vecTextSize.flX) / 2)) : iX, iY);
	nInterfaces::ptrSurface->draw_text(szConvertedText.data(), szText.size());
}

void nRender::rectangle(int iX, int iY, int iWidth, int iHeight, colour_t sColour)
{
	//colour_t may need floats in the future, so for the time being we'll just static_cast them to ints, prevents warning C4244
	nInterfaces::ptrSurface->set_colour(static_cast<int>(sColour.flRed), static_cast<int>(sColour.flGreen), static_cast<int>(sColour.flBlue), static_cast<int>(sColour.flAlpha));
	nInterfaces::ptrSurface->filled_rect(iX, iY, iX + iWidth, iY + iHeight);
}

void nRender::outlined_rectangle(int iX, int iY, int iWidth, int iHeight, colour_t sColour)
{
	nInterfaces::ptrSurface->set_colour(static_cast<int>(sColour.flRed), static_cast<int>(sColour.flGreen), static_cast<int>(sColour.flBlue), static_cast<int>(sColour.flAlpha));
	nInterfaces::ptrSurface->outlined_rect(iX, iY, iX + iWidth, iY + iHeight);
}

void nRender::line(int iX, int iY, int iEndX, int iEndY, colour_t sColour)
{
	nInterfaces::ptrSurface->set_colour(static_cast<int>(sColour.flRed), static_cast<int>(sColour.flGreen), static_cast<int>(sColour.flBlue), static_cast<int>(sColour.flAlpha));
	nInterfaces::ptrSurface->line(iX, iY, iEndX, iEndY);
}

void nRender::gradient(int iX, int iY, int iWidth, int iHeight, colour_t sColour1, colour_t sColour2, bool bHorizontal)
{
	nInterfaces::ptrSurface->set_colour(static_cast<int>(sColour1.flRed), static_cast<int>(sColour1.flGreen), static_cast<int>(sColour1.flBlue), static_cast<int>(sColour1.flAlpha));
	nInterfaces::ptrSurface->filled_rect_fade(iX, iY, iX + iWidth, iY + iHeight, 255, 255, bHorizontal);

	nInterfaces::ptrSurface->set_colour(static_cast<int>(sColour2.flRed), static_cast<int>(sColour2.flGreen), static_cast<int>(sColour2.flBlue), static_cast<int>(sColour2.flAlpha));
	nInterfaces::ptrSurface->filled_rect_fade(iX, iY, iX + iWidth, iY + iHeight, 0, 255, bHorizontal);
}

vector2d_t nRender::text_size(hFont uiFont, std::string_view szText)
{
	//simple wchar_t* convertion as nInterfaces::ptrSurface->get_text_size() requires it
	std::wstring szConvertedText = std::wstring(szText.begin(), szText.end());
	
	//placeholders for our text size
	int iWidth;
	int iHeight;

	nInterfaces::ptrSurface->get_text_size(uiFont, szConvertedText.data(), iWidth, iHeight);

	//returns our x, y vector coords
	return { static_cast<float>(iWidth), static_cast<float>(iHeight) };
}