#pragma once
#include "../../common_includes.h"

//different log types have different prefixes
enum class eLogType
{
	MAIN = 0,
	LOG = 1,
	MISC = 2,
	WARNING = 3,
	ERR = 4,
	DEBUG = 5
};

struct console_t
{
	bool attach(std::string_view szTitle);
	void detach();
	void log(eLogType iLogType, std::string_view szFormatting, ...);

private:
	//console handle, used for text colour changes
	HANDLE hConsole;
	//the buffer we use to handle the formatting of logs
	char szBuffer[256];
}; 
inline console_t sConsole; //needs to be inlined as it becomes multidefined in dllmain