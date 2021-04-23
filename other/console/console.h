#pragma once
#include "../../common_includes.h"

enum class eLogType
{
	LOG = 0,
	MISC = 1,
	WARNING = 2,
	ERR = 3,
};

struct console_t
{
	bool attach(std::string_view szTitle);
	void detach();
	void log(eLogType iLogType, std::string_view szFormatting, ...);

private:
	HANDLE hConsole;
	char szBuffer[256];

}; 
inline console_t sConsole; //needs to be inlined as it becomes multidefined