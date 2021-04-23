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

//used in: general arrays
#include <array>
//used in: sleeping
#include <chrono>
//used in: console stream allocation
#include <iostream>
//used in: general string management, more effeicient than std::string
#include <string_view>
//used in: thread creation, allows us to inject our dll
#include <thread>

//general global includes
extern HMODULE hGlobalModule;

//TODO:
//utilities - netvar management, signature initiation, address handler
// 
//interface management system https://www.unknowncheats.me/forum/counterstrike-global-offensive/444181-vac-monitors-createinterface-calls.html 
//for now it's fine, all that's required is a rework for the walking through the list but this seems a little pointless, but i'll think about it
//in the future.
// 
//hook system, use Valves one https://github.com/binkynz/cstrike-hack/blob/master/other/module/module.cpp#L127