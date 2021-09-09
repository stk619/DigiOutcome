#pragma once
//used in: vfunc grabbing
#include "../../../other/utilities/utilities.h"

struct IClientEntityList
{
private:
	enum eIndices
	{
		GETCLIENTENTITY = 3,
		GETCLIENTENTITYFROMHANDLE = 4,
		GETMAXENTITIES = 8

	};
public:
	void* get_client_entity(int iIndex)
	{
		return nUtilities::vfunc<void* (__thiscall*)(IClientEntityList*, int)>(this, GETCLIENTENTITY)(this, iIndex);
	}
	void* get_client_entity_from_handle(std::size_t hHandle)
	{
		return nUtilities::vfunc<void* (__thiscall*)(IClientEntityList*, std::size_t)>(this, GETCLIENTENTITYFROMHANDLE)(this, hHandle);
	}
	int get_max_entities()
	{
		return nUtilities::vfunc<int (__thiscall*)(IClientEntityList*)>(this, GETMAXENTITIES)(this);
	}
};