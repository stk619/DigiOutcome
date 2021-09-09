#pragma once
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

struct IMaterial
{
private:
	enum eIndices
	{
		SETMATERIALVARFLAGS = 29,
	};

public:
	void set_material_var_flags(int iFlags, bool bEnable = true)
	{
		return nUtilities::vfunc<void(__thiscall*)(IMaterial*, int, bool)>(this, SETMATERIALVARFLAGS)(this, iFlags, bEnable);
	}
};

struct IMaterialSystem
{
private:
	enum eIndices
	{
		FINDMATERIAL = 84
	};

public:
	IMaterial* find_material(const char* szMaterialName, const char* szTextureGroupName, bool bComplain = true, const char* szComplainPrefix = nullptr)
	{
		return nUtilities::vfunc<IMaterial* (__thiscall*)(IMaterialSystem*, const char*, const char*, bool, const char*)>(this, FINDMATERIAL)(this, szMaterialName, szTextureGroupName, bComplain, szComplainPrefix);
	}
};