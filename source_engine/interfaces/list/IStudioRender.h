#pragma once
//used in: virtual function grabbing

struct IStudioRender
{
private:
	enum eIndices
	{
		SETCOLOURMODULATION = 27,
		FORCEDMATERIALOVERRIDE = 33 
	};

public:
	void set_colour_modulation(const float* ptrColour)
	{
		nUtilities::vfunc<void(__thiscall*)(IStudioRender*, const float*)>(this, SETCOLOURMODULATION)(this, ptrColour);
	}
	void forced_material_override(IMaterial* ptrMaterial, int iOverrideType = 0, int iMaterialIndex = -1)
	{
		nUtilities::vfunc<void(__thiscall*)(IStudioRender*, IMaterial*, int, int)>(this, FORCEDMATERIALOVERRIDE)(this, ptrMaterial, iOverrideType, iMaterialIndex);
	}
};