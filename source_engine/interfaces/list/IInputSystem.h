#pragma once

struct IInputSystem
{
private:
	enum eIndices
	{
		ENABLEINPUT = 11,
		ISBUTTONDOWN = 15
	};

public:
	void enable_input(bool bEnable)
	{
		return nUtilities::vfunc<void(__thiscall*)(IInputSystem*, bool)>(this, ENABLEINPUT)(this, bEnable);
	}
};