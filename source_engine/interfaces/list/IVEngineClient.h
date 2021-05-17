#pragma once
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

struct IVEngineClient
{
private:
	enum eIndices
	{
		GETLOCALPLAYER = 12,
		EXECUTECOMMANDUNRESTRICTED = 108
	};
public:
	int get_local_player()
	{
		return nUtilities::vfunc<int(__thiscall*)(IVEngineClient*)>(this, GETLOCALPLAYER)(this);
	}
	//this function most of the time throws a breakpoint when debugging, not sure why though https://i.imgur.com/lpIPiDI.png
	//doesn't cause any problems, must be something on valve's end as i see this all the time
	void execute_command_unrestricted(const char* szCommand)
	{
		return nUtilities::vfunc<void(__thiscall*)(IVEngineClient*, const char*)>(this, EXECUTECOMMANDUNRESTRICTED)(this, szCommand);
	}
};