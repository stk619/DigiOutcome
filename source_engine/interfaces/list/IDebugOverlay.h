#pragma once

struct IDebugOverlay
{
private:
	enum eIndices
	{
		DEBUGOVERLAY = 13
	};
	
public:
	int debug_overlay(const vector3d_t<float>& vecIn, vector3d_t<float>& vecOut)
	{
		return nUtilities::vfunc<int(__thiscall*)(IDebugOverlay*, const vector3d_t<float>&, vector3d_t<float>&)>(this, DEBUGOVERLAY)(this, vecIn, vecOut);
	}

	//world to screen wrapper, prevents us having to check if debug_overlay == 1 each time
	bool world_to_screen(const vector3d_t<float>& vecIn, vector3d_t<float>& vecOut)
	{
		return static_cast<bool>(debug_overlay(vecIn, vecOut) != 1);
	}
};