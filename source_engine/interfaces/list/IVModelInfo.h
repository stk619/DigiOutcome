#pragma once
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

struct IVModelInfo
{
private:
	enum eIndices
	{
		GETMODELINDEX = 2,
		GETMODELNAME = 3,
		GETSTUDIOMODEL = 32
	};

public:
	int get_model_index(const char* szModelName)
	{
		return nUtilities::vfunc<int(__thiscall*)(IVModelInfo*, const char*)>(this, GETMODELINDEX)(this, szModelName);
	}
	const char* get_model_name(void* ptrModel)
	{
		return nUtilities::vfunc<const char* (__thiscall*)(IVModelInfo*, void*)>(this, GETMODELNAME)(this, ptrModel);
	}
	void* get_studio_model(void* ptrModel)
	{
		return nUtilities::vfunc<void* (__thiscall*)(IVModelInfo*, void*)>(this, GETSTUDIOMODEL)(this, ptrModel);
	}
};