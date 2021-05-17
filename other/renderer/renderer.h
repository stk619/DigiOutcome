#pragma once
#include "../../common_includes.h"
//used in: hfont for our fonts
#include "../../source_engine/definitions/general_defines.h"

//colour struct, basically just a struct with floats representing rgba normally these would just be a std::byte 
//as they go up to 255 at max but valve represent their rgba system percentage wise, i.e 1 = 255, 0.1 = 25.5 so we
//need to manually convert it ourselves in some instances, normally people put this elsewhere but it's only ever
//going to be used in the renderer anyways.
struct colour_t
{
public:
	colour_t() = default;
	//simple constructor
	colour_t(float flRed, float flGreen, float flBlue, float flAlpha)
	{
		this->flRed = flRed;
		this->flGreen = flGreen;
		this->flBlue = flBlue;
		this->flAlpha = flAlpha;
	}

	float flRed;
	float flGreen;
	float flBlue;
	float flAlpha;
};

namespace nRender
{
	//as we're just calling virtual functions for our fonts and stuff, we're not gonna need to free this.
	bool allocate();

	//font list
	inline hFont uiTahoma;

	void text(int iX, int iY, std::string_view szText, colour_t sColour, hFont uiFont, bool bCentered = false);
	void rectangle(int iX, int iY, int iWidth, int iHeight, colour_t sColour);
	void outlined_rectangle(int iX, int iY, int iWidth, int iHeight, colour_t sColour);
	void line(int iX, int iY, int iEndX, int iEndY, colour_t sColour);
	void gradient(int iX, int iY, int iWidth, int iHeight, colour_t sColour1, colour_t sColour2, bool bHorizontal = false);
	vector2d_t text_size(hFont uiFont, std::string_view szText);
}