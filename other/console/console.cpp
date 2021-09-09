#include "console.h"

bool console_t::attach(std::string_view szTitle)
{
	//allocate memory for the console
	if (!AllocConsole())
		return false;

	//https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/freopen-s-wfreopen-s?view=msvc-160
	//enabled the input/output streams, as well as error logging, usually writes to files, but in this case
	//we force CONIN$ and CONOUT$ for the console.
	freopen_s(reinterpret_cast<FILE**>(stdin), xorstr_("CONIN$"), xorstr_("r"), stdin);
	freopen_s(reinterpret_cast<FILE**>(stdout), xorstr_("CONOUT$"), xorstr_("w"), stdout);
	freopen_s(reinterpret_cast<FILE**>(stderr), xorstr_("CONOUT$"), xorstr_("w"), stderr);

	SetConsoleTitleA(szTitle.data());

	//get the console handle, will allow us to change text colour later on
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	return true;
}

void console_t::free()
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
//for formatting examples - https://en.wikipedia.org/wiki/Printf_format_string
void console_t::log(eLogType iLogType, std::string_view szFormatting, ...)
{
#ifdef _DEBUG

	//log prefix that is used to indicate the type of log
	std::array<std::pair<std::string_view, int>, 6> arrLogType = { std::make_pair(xorstr_("[MAIN] "), 8), std::make_pair(xorstr_("[LOG] "), 1), 
	/*colours are as follows:*/											std::make_pair(xorstr_("[MISC] "), 3), std::make_pair(xorstr_("[WARNING] "), 14), 
	/*8 = gray, 1 = blue, 3 = cyan, 14 = yellow, 4 = red, 6 = orange*/	std::make_pair(xorstr_("[ERROR] "), 4), std::make_pair(xorstr_("[DEBUG] "), 6) };

	//if the logs are too big, return (greater than 256 characters)
	if (std::strlen(szFormatting.data()) >= sizeof(szBuffer))
		return;

	va_list szArgs;
	va_start(szArgs, szFormatting);

	//this handles the formatting and applies it to our buffer correctly.
	std::memset(szBuffer, '\0', sizeof(szBuffer));
	vsprintf_s(szBuffer, szFormatting.data(), szArgs);

	//set text colour and print it out using the input/output streams.
	SetConsoleTextAttribute(hConsole, arrLogType[static_cast<int>(iLogType)].second);
	std::cout << arrLogType[static_cast<int>(iLogType)].first;
	
	//reset the colour to white and print text
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << szBuffer << std::endl;

	va_end(szArgs);

#endif // _DEBUG
}