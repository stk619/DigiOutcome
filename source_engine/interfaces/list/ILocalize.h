#pragma once

struct ILocalize
{
private:
	enum eIndices
	{
		FINDTOKEN = 11
	};

public:
	wchar_t* find_token(const char* szToken)
	{
		return nUtilities::vfunc<wchar_t* (__thiscall*)(ILocalize*, const char*)>(this, FINDTOKEN)(this, szToken);
	}
};