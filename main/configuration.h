#pragma once

namespace nConfiguration
{
	struct menu_t
	{
		bool bOpened = false;
	};
	inline menu_t sMenu;

	struct miscellaneous_t
	{
		bool bThirdperson = false;
		int iThirdpersonKey = VK_XBUTTON1;
	};
	inline miscellaneous_t sMiscellaneous;
};