#include "miscellaneous.h"
//used in: menu element states
#include "../../menu/menu.h"
//used in: event variables
#include "../../../other/events/event_manager.h"
//used in: rendering functions
#include "../../../other/renderer/renderer.h"
//used in: entity helpers
#include "../../../source_engine/entities/entities.h"
//used in: interface helpers
#include "../../../source_engine/interfaces/interfaces.h"

void nMiscellaneous::bhop(usercmd_t* ptrCmd)
{
	if (!nMenu::ptrBunnyhopCheckbox->GetState())
		return;

	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));

	int iMoveType = ptrLocalPlayer->get_movetype();
	if ((iMoveType == MOVETYPE_LADDER) || (iMoveType == MOVETYPE_NOCLIP))
		return;

	if ((ptrCmd->iButtons & IN_JUMP) && !(ptrLocalPlayer->get_flags() & FL_ONGROUND))
		ptrCmd->iButtons &= ~IN_JUMP;
}

void nMiscellaneous::hitmarker_paint()
{
	if (!nMenu::ptrHitmarkerCheckbox->GetState())
		return;

	//only run hitmarker whilst we're ingame, also force playerhurttime to 0 as this will prevent it from rendering the hitmarker
	if (!nInterfaces::ptrEngine->is_connected() || !nInterfaces::ptrEngine->is_in_game())
	{
		sGameEventImplementation.flPlayerHurtTime = 0;
		return;
	}

	if (sGameEventImplementation.flPlayerHurtTime + 0.25f > nInterfaces::ptrGlobalVars->flCurtime)
	{
		FGUI::DIMENSION dmScreenSize = nRender::screen_size();
		int iSceenCenterX = dmScreenSize.m_iWidth / 2;
		int iSceenCenterY = dmScreenSize.m_iHeight / 2;
		nRender::line(iSceenCenterX - 5, iSceenCenterY - 5, iSceenCenterX - 2, iSceenCenterY - 2, FGUI::COLOR(255, 255, 255, 255)); //top left
		nRender::line(iSceenCenterX + 5, iSceenCenterY - 5, iSceenCenterX + 2, iSceenCenterY - 2, FGUI::COLOR(255, 255, 255, 255)); //top right
		nRender::line(iSceenCenterX + 5, iSceenCenterY + 5, iSceenCenterX + 2, iSceenCenterY + 2, FGUI::COLOR(255, 255, 255, 255)); //bottom right
		nRender::line(iSceenCenterX - 5, iSceenCenterY + 5, iSceenCenterX - 2, iSceenCenterY + 2, FGUI::COLOR(255, 255, 255, 255)); //bottom left
	}
}

void nMiscellaneous::event_logger_paint()
{
	if (sGameEventImplementation.deqEventLoggerList.empty())
		return;

	//remove the last event if there's more than 15 events
	if (sGameEventImplementation.deqEventLoggerList.size() >= 15)
		sGameEventImplementation.deqEventLoggerList.pop_back();

	for (unsigned int iIndex = 0; iIndex < sGameEventImplementation.deqEventLoggerList.size(); ++iIndex)
	{
		if (sGameEventImplementation.deqEventLoggerList[iIndex].flCurtime + 4 > nInterfaces::ptrGlobalVars->flCurtime)
		{
			nRender::outlined_rectangle(10, (30 + (iIndex * 22)), nRender::text_size(nRender::ulMuseoSans, sGameEventImplementation.deqEventLoggerList[iIndex].szMessage.data()).m_iWidth + 10, 20, FGUI::COLOR(40, 40, 40, 255));
			nRender::outlined_rectangle(11, (31 + (iIndex * 22)), nRender::text_size(nRender::ulMuseoSans, sGameEventImplementation.deqEventLoggerList[iIndex].szMessage.data()).m_iWidth + 8, 18, FGUI::COLOR(22, 22, 22, 255));
			nRender::line(11, 31 + (iIndex * 22), 11, 31 + 17 + (iIndex * 22), sGameEventImplementation.deqEventLoggerList[iIndex].sColour);
			nRender::rectangle(12, 32 + (iIndex * 22), nRender::text_size(nRender::ulMuseoSans, sGameEventImplementation.deqEventLoggerList[iIndex].szMessage.data()).m_iWidth + 6, 16, FGUI::COLOR(30, 30, 30, 255));
			nRender::text(15, 34 + (iIndex * 22), nRender::ulMuseoSans, FGUI::COLOR(255, 255, 255, 255), sGameEventImplementation.deqEventLoggerList[iIndex].szMessage.data());
		}
		else
		{
			sGameEventImplementation.deqEventLoggerList.erase(sGameEventImplementation.deqEventLoggerList.begin() + iIndex);
			continue;
		}
	}
}