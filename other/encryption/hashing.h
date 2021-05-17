#pragma once
#include "../../common_includes.h"

//simple fnv (Fowler Noll Vo) hasher, found online, modded form of this
//https://github.com/binkynz/cstrike-hack/blob/996d836a5c14192cf77b64ede4f174ebc52b4638/other/hash/hash.cpp
//uses this, compressed into a single file
//https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
struct fnvhash_t
{
public:
	inline std::size_t hash(std::string_view szString) 
	{
		std::size_t iReturn = iBase;
		std::size_t iLength = std::strlen(szString.data());
		for (std::size_t i = 0; i < iLength; ++i)
		{
			iReturn ^= szString[i];
			iReturn *= iPrimary;
		}
		return iReturn;
	}

protected:
	std::size_t iBase = 0x811c9dc5;
	std::size_t iPrimary = 0x01000193;
};
inline fnvhash_t sHash;