#pragma once
//used in: vfunc grabbing
#include "../../../other/utilities/utilities.h"

struct IClientEntityList
{
private:
	enum eIndices
	{
		GETCLIENTENTITY = 3
	};
public:
	void* get_client_entity(int iIndex)
	{
		return nUtilities::vfunc<void* (__thiscall*)(IClientEntityList*, int)>(this, GETCLIENTENTITY)(this, iIndex);
	}
};