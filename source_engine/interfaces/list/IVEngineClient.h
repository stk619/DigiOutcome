#pragma once
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

struct playerinfo_t;

struct IVEngineClient
{
private:
	enum eIndices
	{
		GETPLAYERINFO = 8,
		GETPLAYERBYUSERID = 9,
		GETLOCALPLAYER = 12,
		ISINGAME = 26,
		ISCONNECTED = 27,
		EXECUTECOMMANDUNRESTRICTED = 108
	};
public:
	bool get_player_info(int iIndex, playerinfo_t* sPlayerInfo)
	{
		return nUtilities::vfunc<bool(__thiscall*)(IVEngineClient*, int, playerinfo_t*)>(this, GETPLAYERINFO)(this, iIndex, sPlayerInfo);
	}
	int get_player_by_userid(int iUserId)
	{
		return nUtilities::vfunc<int(__thiscall*)(IVEngineClient*, int)>(this, GETPLAYERBYUSERID)(this, iUserId);
	}
	int get_local_player()
	{
		return nUtilities::vfunc<int(__thiscall*)(IVEngineClient*)>(this, GETLOCALPLAYER)(this);
	}
	bool is_in_game()
	{
		return nUtilities::vfunc<bool(__thiscall*)(IVEngineClient*)>(this, ISINGAME)(this);
	}
	bool is_connected()
	{
		return nUtilities::vfunc<bool(__thiscall*)(IVEngineClient*)>(this, ISCONNECTED)(this);
	}
	//this function most of the time throws a breakpoint when debugging, not sure why though https://i.imgur.com/lpIPiDI.png
	//doesn't cause any problems, must be something on valve's end as i see this all the time
	void execute_command_unrestricted(const char* szCommand) //currently unused
	{
		return nUtilities::vfunc<void(__thiscall*)(IVEngineClient*, const char*)>(this, EXECUTECOMMANDUNRESTRICTED)(this, szCommand);
	}
};