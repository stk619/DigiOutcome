#pragma once
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

struct IVEngineClient
{
private:
	enum eIndices
	{
		EXECUTECOMMANDUNRESTRICTED = 108
	};
public:
	void execute_command_unrestricted(const char* szCommand) //this function most of the time throws an error when debugging, not sure why though https://i.imgur.com/lpIPiDI.png
	{
		nUtilities::vfunc<void(__thiscall*)(IVEngineClient*, const char*)>(this, EXECUTECOMMANDUNRESTRICTED)(this, szCommand);
	}
};