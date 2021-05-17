#pragma once
#include "../../other/netvars/netvars.h"

//base entitiy, inherited by combatcharacter
struct baseentity_t
{
public:
	int get_movetype()
	{
		//hardcoded offset: 0x0 - int - can't seem to find an actual offset
		//static std::size_t uiMovetypeOffset = nNetvarManager::umOffsets[sHash.hash("DT_BaseEntity->movetype")];
		//return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiMovetypeOffset);
		//https://github.com/frk1/hazedumper/blob/master/csgo.cs#L15
		//fucking valve including the movetype netvar, but having it not work as it should :D
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + 0x25C);
	}

	//better than using the vfunc, but if i need to for whatever reason
	//baseentity, idx 155, no parameters
	//bool isalive()
	//{
		//should be using lifestates
		//return get_lifestate() == static_cast<std::byte>(LIFE_ALIVE);
	//}
	//lifestate stopped working for me?
	bool isalive()
	{
		return nUtilities::vfunc<bool(__thiscall*)(void*)>(this, 155)(this);
	}
};