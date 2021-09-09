#include "event_manager.h"
//used in: console logging
#include "../console/console.h"
//used in: entity variables
#include "../../source_engine/entities/entities.h"
//used in: player name
#include "../../source_engine/definitions/playerinfo.h"

//the event listener works will all game events https://wiki.alliedmods.net/Counter-Strike:_Global_Offensive_Events#player_hurt
//however a lot of them won't be used not only because most have no relevancy to us but primarily because some of these events
//can be detected by community anticheats that utilise some event registering methods. this doesn't mean that we can't use these
//specific events at all as we can attach a listener dynamically when we're in need of it and remove it when we don't, for the
//sake of time i'm leaving these out, though. the way these communal anticheats work involves checking events that aren't used by client.dll
//so logically the client would never have to listen to those events and having those events on the listener obviously indicates
//something is up. so to know which ones are used by client.dll are to simply open up client.dll in ida and look through the strings
//for a specific event, most are used in client.dll anyways. event's id like to have include bomb_beginplant, bomb_abortplant, bullet_impact
//to name a few. but these aren't used in client.dll unfortunately

//global events list, don't xor these, it breaks adding events :| i have absolutely no idea why xoring these strings causes the
//listener to break entirely, but no matter what i do with them xored the game crashes. the only way around this that i see is to
//manually add the listeners rather than using a loop. potentially some string conversion problems, shouldn't matter though
static std::vector<std::string_view> vecEventNames = { ("round_start"), ("player_hurt"), ("player_given_c4"), ("bomb_planted"), ("bomb_defused"), ("bomb_exploded"), ("hostage_follows")};

bool gameeventimplementation_t::allocate()
{
	for (std::string_view &szEventNames : vecEventNames)
	{
		nInterfaces::ptrGameEventManager->add_listener(this, szEventNames.data());
		sConsole.log(eLogType::LOG, xorstr_("%s event added to listener"), szEventNames);
	}

	sConsole.log(eLogType::MAIN, xorstr_("events finished allocating"));
	return true;
}

void gameeventimplementation_t::free()
{
	nInterfaces::ptrGameEventManager->remove_listener(this);
	sConsole.log(eLogType::LOG, xorstr_("game events removed from listener"));
}

void gameeventimplementation_t::fire_game_event(IVGameEventManager* ptrGameEventManager)
{
	//events aren't going to be used when local player goes null, this only happens when we're not in a game i believe
	//(as the local player swaps to the spectated player if we're dead i think)
	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return;

	//don't xorstr any of the following event names, no idea why but it causes a major problem of the events with similar names occuring at the same time
	//e.g player_hurt occurs but because player_given_c4 also has player_ in it, that event happens too :|
	if (std::strncmp(ptrGameEventManager->get_name(), "round_start", sizeof("round_start")) == 0)
	{
		//set the playerhurttime to 0, this prevents the visual hitmarker from rendering constantly on server disconnect
		flPlayerHurtTime = 0.f;
		nUtilities::custom_clantag(nMenu::ptrCustomClantagTextbox->GetText().c_str());
		nUtilities::custom_skybox(xorstr_("sky_csgo_night02b")); //all other skybox textures suck imo

		//this removes the 3d skybox that a lot of the maps have
		if (ptrLocalPlayer->skybox_area() != 255)
			ptrLocalPlayer->skybox_area() = 255;

		//clear sound lists
		vecSoundLocations.clear();
		vecSoundList.remove_all();
	}

	if (std::strncmp(ptrGameEventManager->get_name(), "player_hurt", sizeof("player_hurt")) == 0)
	{
		//xoring these strings seems perfectly fine, though
		int iUserId = ptrGameEventManager->get_int(xorstr_("userid"));
		int iUserIdAttacker = ptrGameEventManager->get_int(xorstr_("attacker"));
		int sDamageDealt = ptrGameEventManager->get_int(xorstr_("dmg_health"));
		int iHealthRemaining = ptrGameEventManager->get_int(xorstr_("health"));

		basecsplayer_t* ptrVictim = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_player_by_userid(iUserId)));
		if (ptrVictim == nullptr)
			return;
		basecsplayer_t* ptrAttacker = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_player_by_userid(iUserIdAttacker)));
		if (ptrAttacker == nullptr)
			return;

		//get player info, for player name
		playerinfo_t sPlayerInfo{};
		if (!nInterfaces::ptrEngine->get_player_info(ptrVictim->index(), &sPlayerInfo))
			return;

		//make sure that only events caused by the localplayer are registered
		if (ptrAttacker == ptrLocalPlayer && ptrVictim != ptrLocalPlayer)
		{
			//only used in hitmarker
			flPlayerHurtTime = nInterfaces::ptrGlobalVars->flCurtime;
			if (nMenu::ptrHitmarkerCheckbox->GetState())
				nInterfaces::ptrSurface->play_sound(xorstr_("buttons\\arena_switch_press_02.wav"));

			//construct player hurt logs
			if (nMenu::ptrEventLoggerMultibox->GetValue(0))
			{
				std::string szPlayerHurtLogs;

				//if we attack a teammate, label it as friendly fire
				if (ptrVictim->get_team() == ptrLocalPlayer->get_team())
				{
					szPlayerHurtLogs.append(xorstr_("[friendly fire] ")).append(sPlayerInfo.szName).append(xorstr_(" hit for ")).append(std::to_string(sDamageDealt)).append(xorstr_(" (")).append(std::to_string(iHealthRemaining)).append(xorstr_(" health remaining)"));
					deqEventLoggerList.emplace_front(szPlayerHurtLogs, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(255, 99, 71, 255));
				}
				else
				{
					szPlayerHurtLogs.append(xorstr_("[player hurt] ")).append(sPlayerInfo.szName).append(xorstr_(" hit for ")).append(std::to_string(sDamageDealt)).append(xorstr_(" (")).append(std::to_string(iHealthRemaining)).append(xorstr_(" health remaining)"));
					deqEventLoggerList.emplace_front(szPlayerHurtLogs, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(191, 255, 0, 255));
				}
			}
		}
	}

	if (std::strncmp(ptrGameEventManager->get_name(), "player_given_c4", sizeof("player_given_c4")) == 0)
	{
		if (nMenu::ptrEventLoggerMultibox->GetValue(1))
		{
			int iUserId = ptrGameEventManager->get_int(xorstr_("userid"));
			basecsplayer_t* ptrBombReceiver = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_player_by_userid(iUserId)));

			if (ptrBombReceiver != ptrLocalPlayer)
			{
				playerinfo_t sPlayerInfo{};
				if (!nInterfaces::ptrEngine->get_player_info(ptrBombReceiver->index(), &sPlayerInfo))
					return;

				std::string szBombReceivedLog;
				szBombReceivedLog.append(xorstr_("[received bomb] ")).append(sPlayerInfo.szName).append(xorstr_(" received the bomb on round start"));
				deqEventLoggerList.emplace_front(szBombReceivedLog, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(255, 99, 71, 255));
			}
		}
	}

	if (std::strncmp(ptrGameEventManager->get_name(), "bomb_planted", sizeof("bomb_planted")) == 0)
	{
		if (nMenu::ptrEventLoggerMultibox->GetValue(1))
		{
			int iUserId = ptrGameEventManager->get_int(xorstr_("userid"));
			basecsplayer_t* ptrBombPlanter = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_player_by_userid(iUserId)));
			if (ptrBombPlanter == nullptr)
				return;

			if (ptrBombPlanter != ptrLocalPlayer)
			{
				playerinfo_t sPlayerInfo{};
				if (!nInterfaces::ptrEngine->get_player_info(ptrBombPlanter->index(), &sPlayerInfo))
					return;

				std::string szPlantedBombLog;
				szPlantedBombLog.append(xorstr_("[planted bomb] ")).append(sPlayerInfo.szName).append(xorstr_(" planted the bomb"));
				deqEventLoggerList.emplace_front(szPlantedBombLog, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(255, 99, 71, 255));
			}
		}
	}

	if (std::strncmp(ptrGameEventManager->get_name(), "bomb_defused", sizeof("bomb_defused")) == 0)
	{
		if (nMenu::ptrEventLoggerMultibox->GetValue(1))
		{
			int iUserId = ptrGameEventManager->get_int(xorstr_("userid"));
			basecsplayer_t* ptrBombDefuser = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_player_by_userid(iUserId)));
			if (ptrBombDefuser == nullptr)
				return;

			if (ptrBombDefuser != ptrLocalPlayer)
			{
				playerinfo_t sPlayerInfo{};
				if (!nInterfaces::ptrEngine->get_player_info(ptrBombDefuser->index(), &sPlayerInfo))
					return;

				std::string szDefusedBombLog;
				szDefusedBombLog.append(xorstr_("[defused bomb] ")).append(sPlayerInfo.szName).append(xorstr_(" defused the bomb"));
				deqEventLoggerList.emplace_front(szDefusedBombLog, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(255, 99, 71, 255));
			}
		}
	}
	
	//unused as of now
	if (std::strncmp(ptrGameEventManager->get_name(), "bomb_exploded", sizeof("bomb_exploded")) == 0)
	{
		//unused right now, will be used for 3d bomb esp (as the planted bomb is globaly networked)
	}

	if (std::strncmp(ptrGameEventManager->get_name(), "hostage_follows", sizeof("hostage_follows")) == 0)
	{
		if (nMenu::ptrEventLoggerMultibox->GetValue(1))
		{
			int iUserId = ptrGameEventManager->get_int(xorstr_("userid"));
			int iHostageId = ptrGameEventManager->get_int(xorstr_("hostage"));
			basecsplayer_t* ptrHostageRescuer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_player_by_userid(iUserId)));
			if (ptrHostageRescuer == nullptr)
				return;

			if (ptrHostageRescuer != ptrLocalPlayer)
			{
				playerinfo_t sPlayerInfo{};
				if (!nInterfaces::ptrEngine->get_player_info(ptrHostageRescuer->index(), &sPlayerInfo))
					return;

				std::string szHostageRescuceLog;
				szHostageRescuceLog.append(xorstr_("[hostage rescued] ")).append(sPlayerInfo.szName).append(xorstr_(" rescued a hostage"));
				deqEventLoggerList.emplace_front(szHostageRescuceLog, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(255, 99, 71, 255));
			}
		}
	}
}