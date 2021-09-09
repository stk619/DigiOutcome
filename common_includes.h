#pragma once

//windows headers
//windows.h loves to add a bunch of garbage that we don't exactly need, to prevent this
//win32 lean and mean cuts down on a large portion and no min max prevents the min/max
//macros from being decleared, as they'll sometimes interfere with std::min/max.
//https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN

//https://stackoverflow.com/questions/22450423/how-to-use-crt-secure-no-warnings
//stupid stuff like sprintf generally causes warnings, this prevents them
#define _CRT_SECURE_NO_WARNINGS

//used in: general arrays
#include <array>
//used in: sleeping, timing
#include <chrono>
//used in: event logger
#include <deque>
//used in: console stream allocation
#include <iostream>
//used in: signature scanning
#include <Psapi.h>
//used in: general string management, more effeicient than std::string
#include <string_view>
//used in: thread creation, allows us to inject our dll
#include <thread>
//used in: hooks
#include <unordered_map>
//used in: general vectors
#include <vector>
//used in: input for mouse pos
#include <windowsx.h>

//other includes
//used in: general encryption - xor method uses current pc time i believe as the encryption key
#include "other/encryption/hashing.h"
#include "other/encryption/xor.h"
//used in: general math functions
#include "other/math/math.h"
#include "other/math/vector2d.h"
#include "other/math/vector3d.h"
#include "other/math/matrix3x4.h"
//used in: general source engine definitions
#include "source_engine/definitions/general_defines.h"

//general global includes
//used in: proper dll detachment
extern HMODULE hGlobalModule;

//global defines
//just wanted a shorter version of __FILE__ - https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
//debug feature, only ever used in debug logs
#ifdef _DEBUG
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif //_DEBUG

#define TICKS_TO_TIME(iTick) (iTick * nInterfaces::ptrGlobalVars->flIntervalPerTick)

//TODO: - fixes/changes
//clean up weapondata.h
//menu font system needs changing as it doesn't account for font cache clearing on screen size change - currently just reloads menu which reloads cfg, change this when doing esp

//TODO: - additions

//FUTURE - planning
//a cheat loader, more secure than simple dll injections, which will enable the creation of a website too

//Things to learn
//calling conventions https://en.m.wikipedia.org/wiki/X86_calling_conventions https://en.wikipedia.org/wiki/Hooking
//basic assembly https://www.tutorialspoint.com/assembly_programming/assembly_introduction.htm https://www.felixcloutier.com/x86/or#protected-mode-exceptions
//basic memory mangement

//looking up NOTE: will show any existing problems too

//Useful tools
//signatures
//-> https://github.com/KittenPopo/csgo-signatures/blob/main/functions.cpp

//offsets
//-> https://csinfo.dev
//-> https://pastebin.com/raw/Rb2TYAcg this is the onetap netvar list
//-> https://github.com/frk1/hazedumper/blob/master/csgo.cs

//other
//-> https://github.com/perilouswithadollarsign/cstrike15_src leaked csgo source (from may 2017)