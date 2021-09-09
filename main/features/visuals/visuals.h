#pragma once
#include "../../../common_includes.h"
//used in: entity information
#include "../../../source_engine/entities/entities.h"

namespace nVisuals
{
	//adds players to an array which we sort, this improves performance
	void tick();
	//handles all player entities, specifically enemies
	void players(basecsplayer_t* ptrCurrentEntity);
	//handles all hostage entities
	void hostages(basecsplayer_t* ptrCurrentEntity);
	//handles all grenade entities, thrown, current effects
	void thrown_grenades(basecsplayer_t* ptrCurrentEntity);
}