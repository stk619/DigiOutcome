#pragma once
//used in: eButtonCode obtaining
#include "../../definitions/general_defines.h"
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

struct IInputSystem
{
private:
	enum eIndices
	{
		ENABLEINPUT = 11,
	};
public:
	void enable_input(bool bEnable)
	{
		return nUtilities::vfunc<void(__thiscall*)(IInputSystem*, bool)>(this, ENABLEINPUT)(this, bEnable);
	}
};