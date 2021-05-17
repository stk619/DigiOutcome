#pragma once
#include "../../common_includes.h"
//used in: recv variable dump
#include "../../source_engine/definitions/received_props.h"

//networked variable manager, essentially like an auto offset grabber
//handles a wide variety of functions, a list can be found here:
//https://pastebin.com/raw/Rb2TYAcg by utilising the offsets generated from these
//we can add them to our player/entity pointers giving us the desired result :D

namespace nNetvarManager
{
	//sets up the netvar manager, called once
	bool allocate();
	void dump_vars(std::string_view szNetvarName, receivedtable_t* ptrTable, std::size_t uiOffset = 0);

	//mapped list that contains the offset of our netvar
	//unordered map because it really doesn't matter too much
	//atleast it shouldn't matter as we're hashing the values
	//plus it's quicker than std::map
	inline std::unordered_map<std::size_t, std::size_t> umOffsets;
}