#include "console.h"

bool console_t::attach(std::string_view szTitle)
{
	//allocate memory for the console
	if (!AllocConsole())
		return false;

	//https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/freopen-s-wfreopen-s?view=msvc-160
	//enabled the input/output streams, as well as error logging, usually writes to files, but in this case
	//we force CONIN$ and CONOUT$ for the console.
	freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin); //console input, read only
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout); //console output, writable
	freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr); //console error, writable

	SetConsoleTitleA(szTitle.data());

	//get the console handle, will allow us to change text colour later on
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	return true;
}

void console_t::detach()
{
	//close opened input/output streams
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);

	//free memory
	FreeConsole();
}

//i dislike pasting but this was the only "viable" solution i found online to being able to format the logs
//as well as being able to change text colour.
//https://github.com/binkynz/cstrike-hack/blob/master/other/console/console.cpp#L30
void console_t::log(eLogType iLogType, std::string_view szFormatting, ...)
{
#ifdef _DEBUG

	//log extention that is used to indicate the type of log
	std::array<std::pair<std::string_view, int>, 4> arrLogType = { std::make_pair("[LOG] ", 1), std::make_pair("[MISC] ", 3), std::make_pair("[WARNING] ", 14), std::make_pair("[ERROR] ", 4) };

	//if the logs are too big, return (greater than 256 characters)
	if (std::strlen(szFormatting.data()) >= sizeof(szBuffer))
		return;

	va_list szArgs;
	va_start(szArgs, szFormatting);

	//this handles the formatting and applies it correctly.
	std::memset(szBuffer, '\0', sizeof(szBuffer));
	vsprintf_s(szBuffer, szFormatting.data(), szArgs);

	//set text colour and print it out using the input/output streams.
	SetConsoleTextAttribute(hConsole, arrLogType[static_cast<int>(iLogType)].second);
	std::cout << arrLogType[static_cast<int>(iLogType)].first;

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << szBuffer << std::endl;

	va_end(szArgs);

#endif // _DEBUG
}