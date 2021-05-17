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
#include "other/math/vector2d.h"
#include "other/math/vector3d.h"
//used in: global configuration of menu
#include "main/configuration.h"

//general global includes
//used in: proper dll detachment
extern HMODULE hGlobalModule;
//used in: hooking wndproc
extern HWND hGlobalWindow;

//global defines
//just wanted a shorter version of __FILE__ - https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
//debug feature, only ever used in debug logs
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

//TODO: - fixes/changes
//fonts break on resolution change, hook https://www.unknowncheats.me/forum/counterstrike-global-offensive/338901-alternative-checking.html
//handle detours and utilities files properly
//when the menu is opened, allow movement keys to still be pressed, should be easy as we hook wndproc

//TODO: - additions
//a menu, in the form of oop
//vfunc hooking to the detours
//json config system

//FUTURE - planning
//could change the renderer to directx which will allow for easy porting across games if i choose to do so
//a cheat loader, more secure than simple dll injections, which will enable the creation of a website too
//changing interfaces, potentially walk through the list

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
//-> https://github.com/perilouswithadollarsign/cstrike15_src leaked csgo source (from may 2017)s