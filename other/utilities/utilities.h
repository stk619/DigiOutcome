#pragma once
#include "../../common_includes.h"
//used in: interface logging
#include "../console/console.h"

namespace nUtilities
{
	//get interfaces, this is a simple method that isn't really too complicated, just gets return address of the 
	//interface used, this converts it to a pointer that we can use. realistically we should be walking through the
	//interface list as valve can do what they've seemingly done here https://www.unknowncheats.me/forum/counterstrike-global-offensive/444181-vac-monitors-createinterface-calls.html
	//but this seems to have taken effect 2+ years ago without any problems, this is just a more "simple method"
	template<typename T>
	inline T* get_interface(const std::string_view& szModule, const std::string_view& szInterfaceName)
	{
		//this is our CreateInterface export, would use std::string_view instead of const char but ptrReturnValue
		//changes this to a const char anyway. this is essentially the main portion of our interface list too.
		//this is supposedly bad as this is most likely a vac detected module that i'm outright walking into, but the
		//module itself probably just lowers trust factor, more mentioned above.
		using ptrInterfaceFunction = void* (*)(const char*, std::size_t*);
		const ptrInterfaceFunction _Notnull_ ptrReturnValue = reinterpret_cast<ptrInterfaceFunction>(GetProcAddress(GetModuleHandleA(szModule.data()), "CreateInterface"));

		if (ptrReturnValue != nullptr)
		{
			void* ptrReturnAddress = ptrReturnValue(szInterfaceName.data(), nullptr);

			//this occurs when we've found the module, but not the correct interface name
			if (ptrReturnAddress == nullptr)
				sConsole.log(eLogType::ERR, "could not find %s in the %s module", szInterfaceName.data(), szModule.data());

			//cast the return address to our typename, giving us the pointer to the interface list.
			return static_cast<T*>(ptrReturnAddress);
		}

		//this occurs when we've got the wrong module name, i.e one that isn't loaded, or spelt correctly on
		//initialization of the interfaces.
		sConsole.log(eLogType::ERR, "could not find %s", szModule.data());
		return nullptr;
	}

	template<typename T>
	inline T vfunc(void* ptrBase, std::size_t iIndex)
	{
		return (*reinterpret_cast<T**>(ptrBase))[iIndex];
	}
}