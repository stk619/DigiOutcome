#pragma once
//used in: logging
#include "../console/console.h"
//used in: signature scanning
#include "../utilities/utilities.h"

//simple detour method that's pretty much just a modified version of this
//https://github.com/infirms/SteamOverlay_Hooker
struct detours_t
{
private:
	struct hookinfo_t
	{
		void* ptrFunction;
		void* ptrOriginal;
	};

	std::unordered_map<std::size_t, hookinfo_t> arrHookInfo;
public:
	//been stuck here for hours trying to figure this out, the cheat always crashed on detachment
	inline bool hook_function(std::string_view szFunctionName, void* ptrFunction, void* ptrCustomFunction)
	{
		if (ptrFunction == nullptr || ptrCustomFunction == nullptr)
			return false;

		//it just works :D
		hookinfo_t& sHookInfo = arrHookInfo[sHash.hash(szFunctionName.data())];
		sHookInfo = { ptrFunction, nullptr };

		uint8_t* ucHookFunction = nUtilities::find_signature(xorstr_("gameoverlayrenderer.dll"), xorstr_("55 8B EC 51 8B 45 10 C7"));

		typedef bool(__cdecl* hook_function_fn)(void*, void*, void*, int);
		hook_function_fn run_hook_function = (hook_function_fn)ucHookFunction;

		//test our hook, this will actually hook the function as well as create an instance for our original function
		//and our detoured function
		if (!run_hook_function(sHookInfo.ptrFunction, ptrCustomFunction, &sHookInfo.ptrOriginal, 0))
			return false;

		sConsole.log(eLogType::LOG, xorstr_("hooked %s at address: 0x%x, original address: 0x%x"), szFunctionName.data(), ptrFunction, &sHookInfo.ptrOriginal);

		return true;
	}

	inline void free_hooks()
	{
		//could shorten the signature to "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" if rel32 fix is used
		//found here - https://github.com/infirms/SteamOverlay_Hooker/blob/master/SteamOverlay_hooker/hooker.h#L66
		//rel32 fix - https://github.com/infirms/SteamOverlay_Hooker/blob/master/SteamOverlay_hooker/hooker.h#L47
		//*could* look into it, but it doesn't matter in the long run
		uint8_t* ucFreeHookFunction = nUtilities::find_signature(xorstr_("gameoverlayrenderer.dll"), xorstr_("55 8B ?? 64 ?? ?? ?? ?? ?? 6A ?? 68 ?? ?? ?? ?? 50 64 ?? ?? ?? ?? ?? ?? 81 ?? ?? ?? ?? ?? 56 8B ?? ?? 85"));

		//uisng an address manager for the signature scanner should be able to eliminate this/cut it down to a more readable
		//piece of code, this is good enough for now though.
		typedef void(__cdecl* free_hook_function_fn)(void*, bool);
		free_hook_function_fn run_free_hook_function = (free_hook_function_fn)ucFreeHookFunction;

		//loop through the list of hooked functions, and unhook acordingly
		for (std::pair<const std::size_t, hookinfo_t>& detour : arrHookInfo)
			run_free_hook_function(detour.second.ptrFunction, false);
	}

	//similiarly to the vfunc function i genuinely don't know how this actually works, it just does :D
	template< typename T > 
	inline T get_original(std::string_view szName)
	{
		return (T)arrHookInfo[sHash.hash(szName.data())].ptrOriginal;
	}
};
inline detours_t sDetours;