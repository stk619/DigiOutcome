#pragma once
#include "../../common_includes.h"
//used in: interface logging
#include "../console/console.h"

#pragma warning(disable : 6387)

namespace nUtilities
{
	//get interfaces, this is a simple method that isn't really too complicated, just gets return address of the 
	//interface used, this converts it to a pointer that we can use. realistically we should be walking through the
	//interface list as valve can do what has seemingly been done here https://www.unknowncheats.me/forum/counterstrike-global-offensive/444181-vac-monitors-createinterface-calls.html
	//but this seems to have taken effect 2+ years ago without any problems, this is just a more "simple method"
	template<typename T>
	inline T* get_interface(const std::string_view& szModule, const std::string_view& szInterfaceName)
	{
		//this is our CreateInterface export, would use std::string_view instead of const char but ptrReturnValue
		//changes this to a const char anyway. this is essentially the main portion of our interface list too.
		//this is supposedly bad as this is most likely a vac detected module that i'm outright walking into, but the
		//module itself probably just lowers trust factor, more mentioned above.
		using ptrInterfaceFunction = void* (*)(const char*, std::size_t*);
		//decleared as _NotNull_ as this prevents warning C6387 from being generated, which *should* never be a problem anyway
		const ptrInterfaceFunction _Notnull_ ptrReturnValue = reinterpret_cast<ptrInterfaceFunction>(GetProcAddress(GetModuleHandleA(szModule.data()), xorstr_("CreateInterface")));

		if (ptrReturnValue != nullptr)
		{
			void* ptrReturnAddress = ptrReturnValue(szInterfaceName.data(), nullptr);

			//this occurs when we've found the module, but not the correct interface name
			if (ptrReturnAddress == nullptr)
			{
				sConsole.log(eLogType::ERR, xorstr_("could not find interface: %s in module: %s"), szInterfaceName.data(), szModule.data());
				return nullptr;
			}

			//cast the return address to our typename, giving us the pointer to the interface list. we also log this action
			sConsole.log(eLogType::LOG, xorstr_("found interface: %s in module: %s at address: 0x%x"), szInterfaceName.data(), szModule.data(), ptrReturnAddress);
			return static_cast<T*>(ptrReturnAddress);
		}

		//this occurs when we've got the wrong module name, i.e one that isn't loaded, or spelt correctly on
		//initialization of the interfaces.
		sConsole.log(eLogType::ERR, xorstr_("could not find module: %s"), szModule.data());
		return nullptr;
	}

	//in all honesty, i have no idea how this actually works to get the function. it just does i suppose, lol.
	template<typename T>
	inline T vfunc(void* ptrBase, std::size_t iIndex)
	{
		return (*reinterpret_cast<T**>(ptrBase))[iIndex];
	}

	inline std::uint8_t* find_signature(std::string_view szModule, std::string_view szSignature)
	{
		//converts the letters and numbers into a byte array
		static auto vecPatternToBytes = [](const char* szPattern) -> std::vector<std::size_t>
		{
			std::vector<std::size_t> vecBytes;

			char* szStart = const_cast<char*>(szPattern);
			char* szEnd = const_cast<char*>(szPattern) + std::strlen(szPattern);
			for (char* iCurrent = szStart; iCurrent < szEnd; ++iCurrent)
			{
				if (*iCurrent == '?')
				{
					++iCurrent;

					if (*iCurrent == '?')
						++iCurrent;

					vecBytes.push_back(-1);
				}
				else
					vecBytes.push_back(std::strtoul(iCurrent, &iCurrent, 16));
			}
			return vecBytes;
		};

		HMODULE hModule = GetModuleHandleA(szModule.data());
		if (!hModule)
			return nullptr;

		MODULEINFO hModuleInfo;
		if (!K32GetModuleInformation(GetCurrentProcess(), hModule, &hModuleInfo, sizeof(MODULEINFO)))
			return nullptr;

		unsigned char* szImageBytes = reinterpret_cast<unsigned char*>(hModule);
		if (!szImageBytes)
			return nullptr;

		unsigned long lImageSize = hModuleInfo.SizeOfImage;
		if (!lImageSize)
			return nullptr;

		std::vector<std::size_t> vecByteArray = vecPatternToBytes(szSignature.data());
		std::size_t iSignatureSize = vecByteArray.size();
		std::size_t* iSignagureByteCount = vecByteArray.data();

		for (std::size_t i = 0; i < lImageSize - iSignatureSize; ++i)
		{
			bool bByteSequenceFound = true;

			for (unsigned long j = 0; j < iSignatureSize; ++j)
			{
				if (szImageBytes[i + j] != iSignagureByteCount[j] && iSignagureByteCount[j] != -1)
				{
					bByteSequenceFound = false;
					break;
				}
			}

			if (bByteSequenceFound)
				return &szImageBytes[i];
		}
		return nullptr;
	}

	inline void custom_clantag(const char* szClantag)
	{
		static void(__fastcall* custom_clantag)(const char*, const char*) = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(nUtilities::find_signature(xorstr_("engine.dll"), xorstr_("53 56 57 8B DA 8B F9 FF 15")));
		custom_clantag(szClantag, szClantag);
	}

	inline void custom_skybox(const char* szSkybox)
	{
		static void(__fastcall * custom_skybox)(const char*) = reinterpret_cast<void(__fastcall*)(const char*)>(nUtilities::find_signature(xorstr_("engine.dll"), xorstr_("55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45")));
		custom_skybox(szSkybox);
	}
}