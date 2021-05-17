#pragma once
#include "../../other/netvars/netvars.h"
//used in: inheritance
#include "base_entity.h"

//base player, inherited by combatcharacter
struct baseplayer_t : baseentity_t
{
public:
	int get_flags()
	{
		//hardcoded offset: 0x104 - int
		static std::size_t uiFlagsOffset = nNetvarManager::umOffsets[sHash.hash("DT_BasePlayer->m_fFlags")];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiFlagsOffset);
	}

	int get_health()
	{
		//hardcoded offset: 0x100 - int
		static std::size_t uiHealthOffset = nNetvarManager::umOffsets[sHash.hash("DT_BasePlayer->m_iHealth")];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiHealthOffset);
	}

	std::byte get_lifestate()
	{
		//hardcoded offset: 0x25f - byte
		static std::size_t uiHealthOffset = nNetvarManager::umOffsets[sHash.hash("DT_BasePlayer->m_lifeState")];
		return *reinterpret_cast<std::byte*>(reinterpret_cast<std::size_t>(this) + uiHealthOffset);
	}
};