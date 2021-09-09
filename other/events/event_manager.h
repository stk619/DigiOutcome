#pragma once
#include "../../common_includes.h"
//used in: menu variables also fgui include
#include "../../main/menu/menu.h"
//used in: interface for game events
#include "../../source_engine/interfaces/interfaces.h"

struct eventlogger_t
{
	eventlogger_t() = default;
	eventlogger_t(std::string szMessage, float flCurtime, FGUI::COLOR sColour)
	{
		this->szMessage = szMessage;
		this->flCurtime = flCurtime;
		this->sColour = sColour;
	}

	std::string szMessage;
	float flCurtime;
	FGUI::COLOR sColour;
};

struct gameeventimplementation_t : public gameevent_t
{
public:
	bool allocate();
	void free();
	void fire_game_event(IVGameEventManager* ptrGameEventManager) override;

	std::deque<eventlogger_t> deqEventLoggerList;
	std::vector<vector3d_t<float>> vecSoundLocations;
	float flPlayerHurtTime{};
	utl_vector<sound_info> vecSoundList{};
};
inline gameeventimplementation_t sGameEventImplementation;