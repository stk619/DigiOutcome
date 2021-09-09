#include "visuals.h"
//used in: menu variables checks
#include "../../menu/menu.h"
//used in: rendering functions
#include "../../../other/renderer/renderer.h"
//used in: sound events
#include "../../../other/events/event_manager.h"
//used in: entity grabbing functions
#include "../../../source_engine/interfaces/interfaces.h"
//used in: player name
#include "../../../source_engine/definitions/playerinfo.h"

//global variables for visuals
bool bAmmoBarRendered{};
static FGUI::COLOR colDormant = FGUI::COLOR(255, 255, 255, 150);
static FGUI::COLOR colDormantOutlines = FGUI::COLOR(22, 22, 22, 150);

void render_beamring(vector3d_t<float> vecPosition)
{
	BeamInfo_t sBeamInfo;
	sBeamInfo.nType = TE_BEAMRINGPOINT;
	sBeamInfo.pszModelName = xorstr_("sprites/purplelaser1.vmt");
	sBeamInfo.nModelIndex = nInterfaces::ptrModelInfo->get_model_index(xorstr_("sprites/purplelaser1.vmt"));
	sBeamInfo.nHaloIndex = -1;
	sBeamInfo.flHaloScale = 5;
	sBeamInfo.flLife = .50f;
	sBeamInfo.flWidth = 10.f;
	sBeamInfo.flFadeLength = 1.0f;
	sBeamInfo.flAmplitude = 0.f;
	sBeamInfo.flRed = 0.f;
	sBeamInfo.flGreen = 150.f;
	sBeamInfo.flBlue = 255.f;
	sBeamInfo.flBrightness = 255.f;
	sBeamInfo.flSpeed = 0.f;
	sBeamInfo.iStartFrame = 0;
	sBeamInfo.flFrameRate = 60.f;
	sBeamInfo.nSegments = -1;
	sBeamInfo.nFlags = FBEAM_SINENOISE;
	sBeamInfo.vecCenter = vecPosition + vector3d_t<float>(0, 0, -5);
	sBeamInfo.flStartRadius = 20.f;
	sBeamInfo.flEndRadius = 500.f;

	Beam_t* ptrBeam = nInterfaces::ptrRenderBeams->CreateBeamRingPoint(sBeamInfo);
	if (ptrBeam == nullptr)
		return;

	nInterfaces::ptrRenderBeams->DrawBeam(ptrBeam);
}

void nVisuals::tick()
{
	//local player should never go null unless we're in the main menu
	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return;

	//reset each time we loop through entities, prevents us from having to do funky calculations to clear specific
	//elements from the array
	std::vector<std::pair<basecsplayer_t*, float>> vecStoredEntities = {};
	bAmmoBarRendered = false;
	for (int iIndex = 1; iIndex < nInterfaces::ptrEntityList->get_max_entities(); ++iIndex)
	{
		basecsplayer_t* ptrCurrentEntity = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(iIndex));
		if (ptrCurrentEntity == nullptr)
			continue;

		if (!nMenu::ptrDormantCheckbox->GetState() && ptrCurrentEntity->isdormant())
			continue;

		vecStoredEntities.emplace_back(std::make_pair(ptrCurrentEntity, ptrLocalPlayer->get_origin().distance_to(ptrCurrentEntity->get_origin())));
	}

	//sorting method that sorts players faster than normal, also by distance so that the players that are closer to us, render atop all
	//other players networked at the same time, rather than it being sorted by who has the highest entity index, we also declare the lambda
	//as a reference, this prevents copies being made per comparison and instead utilises references, which is more optimised
	std::sort(vecStoredEntities.begin(), vecStoredEntities.end(), [&](std::pair<basecsplayer_t*, float>& vecPlayerA, std::pair<basecsplayer_t*, float>& vecPlayerB) {
		return vecPlayerA.second > vecPlayerB.second;
		});

	//sConsole.log(eLogType::DEBUG, xorstr_("stored entities: %i"), vecStoredEntities.size());

	//now we can render things onto the entities
	for (std::pair<basecsplayer_t*, float>& vecEntityInfo : vecStoredEntities)
	{
		//get difference between curtime and simulation time
		float flDeltaTime = nInterfaces::ptrGlobalVars->flCurtime - vecEntityInfo.first->get_simulation_time();

		//if an entity has been dormant for more than 5 seconds, stop rendering their information
		colDormant.m_ucAlpha = flDeltaTime > 5.f ? 0 : 150;
		colDormantOutlines.m_ucAlpha = flDeltaTime > 5.f ? 0 : 150;

		//we use client classes to check for specific entities that we want to run things on, e.g ccsplayer is all player entities
		//this is where we'll be running calculations surrounding player things; box; name; health; ect 
		clientclass_t* ptrClientClass = vecEntityInfo.first->get_client_class();
		if (ptrClientClass == nullptr)
			continue;

		int iClassId = static_cast<int>(ptrClientClass->iClassID);

		//switch case of course
		switch (iClassId)
		{
		case static_cast<int>(eClassId::CCSPlayer):
			nVisuals::players(vecEntityInfo.first);
			break;
		case static_cast<int>(eClassId::CHostage):
			nVisuals::hostages(vecEntityInfo.first);
			break;
			//we want to run the code on these specific entities, but in the grenade function itself
			//we want to run specific things on each grenade type, so we need two different class id
			//switch cases, this is also strictly for thrown grenades, world grenades are handled later
			//there are also a few other "grenades" but as they're barely used; like the ones in danger
			//zone or the snowballs valve adds for a couple weeks around christmas, they're pointless
		case static_cast<int>(eClassId::CDecoyProjectile):
		case static_cast<int>(eClassId::CSmokeGrenadeProjectile):
		case static_cast<int>(eClassId::CMolotovProjectile):
		case static_cast<int>(eClassId::CInferno):
		case static_cast<int>(eClassId::CBaseCSGrenadeProjectile):
			nVisuals::thrown_grenades(vecEntityInfo.first);
			break;
		}
	}
}

void nVisuals::players(basecsplayer_t* ptrCurrentEntity)
{
	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return;

	//don't add local player here, or our team
	if (ptrCurrentEntity == ptrLocalPlayer || ptrCurrentEntity->get_team() == ptrLocalPlayer->get_team())
		return;

	basecombatcharacter_t* ptrActiveWeapon = reinterpret_cast<basecombatcharacter_t*>(nInterfaces::ptrEntityList->get_client_entity_from_handle(ptrCurrentEntity->get_active_weapon()));
	if (ptrActiveWeapon == nullptr)
		return;

	csweapondata_t* ptrWeaponData = ptrActiveWeapon->get_weapon_data();
	if (ptrWeaponData == nullptr)
		return;

	bAmmoBarRendered = (ptrWeaponData->nWeaponType != WEAPONTYPE_KNIFE && ptrWeaponData->nWeaponType != WEAPONTYPE_C4 && ptrWeaponData->nWeaponType != WEAPONTYPE_GRENADE && ptrWeaponData->nWeaponType != WEAPONTYPE_EQUIPMENT && ptrWeaponData->nWeaponType != WEAPONTYPE_STACKABLEITEM && ptrWeaponData->nWeaponType != WEAPONTYPE_UNKNOWN);

	playerinfo_t sPlayerInfo{};
	if (!nInterfaces::ptrEngine->get_player_info(ptrCurrentEntity->index(), &sPlayerInfo))
		return;

	boundingbox_t sBoundingBox = ptrCurrentEntity->get_bounding_box();
	if (sBoundingBox.flX == 0 || sBoundingBox.flY == 0 || sBoundingBox.flWidth == 0 || sBoundingBox.flHeight == 0)
		return;

	//cast all bounding box positions to ints, preventing warnings about data loss from renderer
	int iCastedBoundingBoxX = static_cast<int>(sBoundingBox.flX);
	int iCastedBoundingBoxY = static_cast<int>(sBoundingBox.flY);
	int iCastedBoundingBoxWidth = static_cast<int>(sBoundingBox.flWidth);
	int iCastedBoundingBoxHeight = static_cast<int>(sBoundingBox.flHeight);

	//get animation related info, this will be used for ammo bar and reloading flag
	animationlayer_t* ptrFirstAnimationLayer = &ptrCurrentEntity->get_animation_overlays()[1];
	animationlayer_t* ptrEighthAnimationLayer = &ptrCurrentEntity->get_animation_overlays()[8];
	if (ptrFirstAnimationLayer->ptrAnimationOwner == nullptr || ptrEighthAnimationLayer->ptrAnimationOwner == nullptr)
		return;
	int iFirstActivity = ptrCurrentEntity->get_sequence_activity(ptrFirstAnimationLayer->iSequence);
	int iEighthActivity = ptrCurrentEntity->get_sequence_activity(ptrEighthAnimationLayer->iSequence);

#pragma warning(disable : 4244) //the health bar requires a float for the calculations, i don't have a proper conversion and it's only 3 warnings that get filtered out here
	//asign colours based off of players being dormant or not
	FGUI::COLOR colBoundingBox = ptrCurrentEntity->isdormant() ? colDormant : FGUI::COLOR(255, 255, 255, 255);
	FGUI::COLOR colText = ptrCurrentEntity->isdormant() ? colDormant : FGUI::COLOR(255, 255, 255, 200);
	FGUI::COLOR colOutlines = ptrCurrentEntity->isdormant() ? colDormantOutlines : FGUI::COLOR(22, 22, 22, 200);
	FGUI::COLOR colBackgrounds = ptrCurrentEntity->isdormant() ? colDormantOutlines : FGUI::COLOR(22, 22, 22, 150);
	FGUI::COLOR colHealthBar = ptrCurrentEntity->isdormant() ? colDormant : FGUI::COLOR(191 - (ptrCurrentEntity->get_health() * 2.55), ptrCurrentEntity->get_health() * 2.55, 0, 255);
	FGUI::COLOR colAmmoBar = ptrCurrentEntity->isdormant() ? colDormant : FGUI::COLOR(0, 150, 255, 255);
#pragma warning(default : 4244)

	//dormant esp handler, this allows us to not only get the player sounds for the sound rings, but also to "extend" our dormant esp
	//as sounds are networked further than players are, we can then update the positions of our esp based off of the origin of the
	//sounds essentially extending our esp
	{
		//remove sounds each iteration, before getting all again
		sGameEventImplementation.vecSoundLocations.clear();
		sGameEventImplementation.vecSoundList.remove_all();
		nInterfaces::ptrEngineSounds->get_all_active_sounds(sGameEventImplementation.vecSoundList);

		static int iSoundGuid[64]{};
		for (int iSoundIndex = 0; iSoundIndex < sGameEventImplementation.vecSoundList.count(); ++iSoundIndex)
		{
			//get the current sound we're iterating through
			sound_info& sCurrentSound = sGameEventImplementation.vecSoundList.element(iSoundIndex);

			//sounds have different channels and sources
			if (sCurrentSound.m_sound_source < 1 || sCurrentSound.m_sound_source > 64 || sCurrentSound.m_channel != 4)
				continue;

			//get the entity that made the sound
			basecsplayer_t* ptrSoundCreator = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(sGameEventImplementation.vecSoundList.element(iSoundIndex).m_sound_source));
			if (ptrSoundCreator == nullptr)
				continue;

			if (ptrSoundCreator == ptrLocalPlayer || ptrSoundCreator->get_team() == ptrLocalPlayer->get_team())
				continue;

			if (ptrSoundCreator->isdormant()) //dormant esp extension
			{
				if (iSoundGuid[sCurrentSound.m_sound_source] < sCurrentSound.m_guid && sCurrentSound.m_origin)
				{
					iSoundGuid[sCurrentSound.m_sound_source] = sCurrentSound.m_guid;
					ptrSoundCreator->set_abs_origin(*sCurrentSound.m_origin);
				}
			}
			else //sound ring addition
			{
				if (iSoundGuid[sCurrentSound.m_sound_source] < sCurrentSound.m_guid && sCurrentSound.m_origin)
				{
					iSoundGuid[sCurrentSound.m_sound_source] = sCurrentSound.m_guid;
					sGameEventImplementation.vecSoundLocations.push_back(*sCurrentSound.m_origin);
				}
			}
		}
	}

	if (nMenu::ptrBoundingBoxCheckbox->GetState())
	{
		nRender::outlined_rectangle(iCastedBoundingBoxX, iCastedBoundingBoxY, iCastedBoundingBoxWidth, iCastedBoundingBoxHeight, colBoundingBox);
		nRender::outlined_rectangle(iCastedBoundingBoxX - 1, iCastedBoundingBoxY - 1, iCastedBoundingBoxWidth + 2, iCastedBoundingBoxHeight + 2, colOutlines);
		nRender::outlined_rectangle(iCastedBoundingBoxX + 1, iCastedBoundingBoxY + 1, iCastedBoundingBoxWidth - 2, iCastedBoundingBoxHeight - 2, colOutlines);
	}

	if (nMenu::ptrNameCheckbox->GetState())
	{
		std::string szPlayerName = sPlayerInfo.szName;
		if (szPlayerName.length() > 20)
			szPlayerName.replace(20, (szPlayerName.length() - 20), xorstr_("..."));

		nRender::text(((iCastedBoundingBoxX + (iCastedBoundingBoxWidth / 2)) - (nRender::text_size(nRender::ulMuseoSans, szPlayerName).m_iWidth / 2)),
			iCastedBoundingBoxY - 13, nRender::ulMuseoSans, colText, szPlayerName);
	}

#pragma warning(disable : 4244) //the health bar requires a float for the calculations, i don't have a proper conversion and it's only 3 warnings that get filtered out here
	if (nMenu::ptrHealthBarCheckbox->GetState())
	{
		//taken from my old project because i absolutely hate working with these dumbass healthbars, the logic is so damn annoying
		constexpr int iMaxHealth = 100;
		const int iHealth = std::clamp<int>(ptrCurrentEntity->get_health(), 0, iMaxHealth);
		float flBarHeight = static_cast<float>(iHealth) / static_cast<float>(iMaxHealth);

		nRender::rectangle(iCastedBoundingBoxX - 6, iCastedBoundingBoxY, 2, iCastedBoundingBoxHeight, colBackgrounds);
		nRender::outlined_rectangle(iCastedBoundingBoxX - 7, iCastedBoundingBoxY - 1, 4, iCastedBoundingBoxHeight + 2, colOutlines);
		nRender::rectangle(iCastedBoundingBoxX - 6, iCastedBoundingBoxY + (iCastedBoundingBoxHeight - iCastedBoundingBoxHeight * flBarHeight), 2,
			iCastedBoundingBoxHeight * flBarHeight - (iHealth >= 100 ? 0 : -1), colHealthBar);

		std::string szHealthText = std::string(std::to_string(iHealth)).append(xorstr_("HP"));

		if (iHealth < iMaxHealth)
			nRender::text(iCastedBoundingBoxX - nRender::text_size(nRender::ulMuseoSans, szHealthText).m_iWidth - 7,
				iCastedBoundingBoxY + (iCastedBoundingBoxHeight - iCastedBoundingBoxHeight * flBarHeight) - (nRender::text_size(nRender::ulMuseoSans, szHealthText).m_iHeight / static_cast<float>(2)),
				nRender::ulMuseoSans, colText, szHealthText);
	}
#pragma warning(default : 4244)

	if (nMenu::ptrAmmoBarCheckbox->GetState())
	{
		//only run this on weapons that have ammo
		if (bAmmoBarRendered)
		{
			const int iAmmoCount = ptrActiveWeapon->get_ammo();
			const int iMaxClip = ptrWeaponData->iMaxClip1;

			float flBarLocation{};
			if (ptrFirstAnimationLayer->flWeight != 0.f && iFirstActivity == 967) //this is literally the only thing sequence activity will be used for but 967 = ACT_CSGO_RELOAD
				flBarLocation = ptrFirstAnimationLayer->flCycle;
			else
				flBarLocation = static_cast<float>(iAmmoCount) / static_cast<float>(iMaxClip);

			nRender::rectangle(iCastedBoundingBoxX, (iCastedBoundingBoxY + iCastedBoundingBoxHeight + 4), iCastedBoundingBoxWidth, 2, colBackgrounds);
			nRender::outlined_rectangle(iCastedBoundingBoxX - 1, (iCastedBoundingBoxY + iCastedBoundingBoxHeight + 3), iCastedBoundingBoxWidth + 2, 4, colOutlines);
			nRender::rectangle(iCastedBoundingBoxX, (iCastedBoundingBoxY + iCastedBoundingBoxHeight + 4), static_cast<int>(iCastedBoundingBoxWidth * flBarLocation), 2, colAmmoBar);
		}
	}

	if (nMenu::ptrWeaponNameCheckbox->GetState())
	{
		//this cleans the weapon name from weapon_"weapon name" to just the regular weapon name, this isn't entirely needed
		//as realistically we'd be able to just std::string szWeaponName.erase(0, 12); which would fix it, but i like this more
		//this also converts the name to what the game uses for the hud
		wchar_t* szLocalizedWeaponName = nInterfaces::ptrLocalize->find_token(ptrWeaponData->szHudName);
		char szBuffer[256]{};
		sprintf_s(szBuffer, xorstr_("%ws"), szLocalizedWeaponName);
		const char* szWeaponName = szBuffer;
		nRender::text(((iCastedBoundingBoxX + (iCastedBoundingBoxWidth / 2)) - (nRender::text_size(nRender::ulMuseoSans, szWeaponName).m_iWidth / 2)),
			bAmmoBarRendered ? ((iCastedBoundingBoxY + iCastedBoundingBoxHeight) + 7) : ((iCastedBoundingBoxY + iCastedBoundingBoxHeight) + 1), nRender::ulMuseoSans, colText, szWeaponName);
	}

	std::vector<std::pair<std::string, FGUI::COLOR>> vecFlagList{};

	if (nMenu::ptrAmmoBarCheckbox->GetState() && bAmmoBarRendered)
		vecFlagList.push_back(std::make_pair(std::to_string(ptrActiveWeapon->get_ammo()).append(xorstr_(" bullets")), FGUI::COLOR(255, 255, 255, 200)));

	if (nMenu::ptrFlagListMultibox->GetValue(0) && ptrCurrentEntity->get_armour() > 0)
		vecFlagList.push_back(std::make_pair(ptrCurrentEntity->get_helmet() ? xorstr_("HK") : xorstr_("K"), FGUI::COLOR(255, 255, 255, 200)));

	if (nMenu::ptrFlagListMultibox->GetValue(1))
		vecFlagList.push_back(std::make_pair(&ptrCurrentEntity->get_last_place_name(), FGUI::COLOR(255, 255, 255, 200)));

	if (nMenu::ptrFlagListMultibox->GetValue(2))
	{
		if (ptrCurrentEntity->get_bomb_carrier())
			vecFlagList.push_back(std::make_pair(xorstr_("Bomb"), FGUI::COLOR(255, 99, 71, 200)));
		if (ptrEighthAnimationLayer->flWeight != 0.f && iEighthActivity == 978)
			vecFlagList.push_back(std::make_pair(xorstr_("Planting"), FGUI::COLOR(255, 99, 71, 200)));
		if (ptrCurrentEntity->get_defuser())
			vecFlagList.push_back(std::make_pair(xorstr_("Kit"), FGUI::COLOR(255, 0, 255, 200)));
		if (ptrCurrentEntity->get_player_defusing())
			vecFlagList.push_back(std::make_pair(xorstr_("Defusing"), FGUI::COLOR(0, 255, 179, 200)));
		if (ptrCurrentEntity->get_grabbing_hostage())
			vecFlagList.push_back(std::make_pair(xorstr_("Rescuing"), FGUI::COLOR(0, 255, 179, 200)));
	}

#pragma warning(disable : 4244) //warnings disabled here, because float conversion is required
	if (nMenu::ptrFlagListMultibox->GetValue(3) && ptrCurrentEntity->get_scoped())
		vecFlagList.push_back(std::make_pair(xorstr_("Scoped"), FGUI::COLOR(0, 150, 255, 200)));

	if (nMenu::ptrFlagListMultibox->GetValue(4) && ptrFirstAnimationLayer->flWeight != 0.f && iFirstActivity == 967)
		vecFlagList.push_back(std::make_pair(xorstr_("Reloading"), FGUI::COLOR((ptrFirstAnimationLayer->flCycle * 255.f), 255 - (ptrFirstAnimationLayer->flCycle * 255.f), 0, 255)));

	if (nMenu::ptrFlagListMultibox->GetValue(5) && ptrCurrentEntity->get_flashbang_time_remaining() > 0.2f)
		vecFlagList.push_back(std::make_pair(xorstr_("Flashed"), FGUI::COLOR(250, 253, 15, (ptrCurrentEntity->get_flashbang_time_remaining() / ptrCurrentEntity->get_max_flash_alpha()) * 255)));
#pragma warning(default : 4244)

	if (nMenu::ptrFlagListMultibox->GetValue(6) && ptrCurrentEntity->get_player_walking())
		vecFlagList.push_back(std::make_pair(xorstr_("Walking"), FGUI::COLOR(255, 0, 106, 200)));

	int iFlagPosition = 0;
	for (std::pair<std::string, FGUI::COLOR>& flagList : vecFlagList)
	{
		//if the player goes dormant, change the text colour
		FGUI::COLOR colFlagColor = ptrCurrentEntity->isdormant() ? colDormant : flagList.second;

		nRender::text(iCastedBoundingBoxX + iCastedBoundingBoxWidth + 2, (iCastedBoundingBoxY - 2) + iFlagPosition, nRender::ulMuseoSans, colFlagColor, flagList.first);
		iFlagPosition += 11;
	}

	if (nMenu::ptrSoundsCheckbox->GetState())
	{
		for (unsigned int iSoundRings = 0; iSoundRings < sGameEventImplementation.vecSoundLocations.size(); ++iSoundRings)
		{
			//render the beams, then erase them from the list
			render_beamring(sGameEventImplementation.vecSoundLocations.at(iSoundRings));
			sGameEventImplementation.vecSoundLocations.erase(sGameEventImplementation.vecSoundLocations.begin() + iSoundRings);
		}
	}
}

void nVisuals::hostages(basecsplayer_t* ptrCurrentEntity)
{
	if (!nMenu::ptrHostageCheckbox->GetState())
		return;

	//don't render anything on hostage if they've been picked up
	if (ptrCurrentEntity->get_hostage_state() != 0)
		return;

	boundingbox_t sBoundingBox = ptrCurrentEntity->get_bounding_box();
	if (sBoundingBox.flX == 0 || sBoundingBox.flY == 0 || sBoundingBox.flWidth == 0 || sBoundingBox.flHeight == 0)
		return;

	//render hostage name
	nRender::text((static_cast<int>(sBoundingBox.flX + (sBoundingBox.flWidth / static_cast<float>(2)) - (nRender::text_size(nRender::ulMuseoSans, xorstr_("Hostage")).m_iWidth / static_cast<float>(2)))),
		static_cast<int>(sBoundingBox.flY) + static_cast<int>(sBoundingBox.flHeight / 2), nRender::ulMuseoSans, FGUI::COLOR(255, 255, 255, 200), xorstr_("Hostage"));
}

void nVisuals::thrown_grenades(basecsplayer_t* ptrCurrentEntity)
{
#pragma warning(disable : 4244)
	if (!nMenu::ptrThrownGrenadesCheckbox->GetState())
		return;

	//no nullptr check as we'd be doing it twice
	clientclass_t* ptrClientClass = ptrCurrentEntity->get_client_class();
	int iClassId = static_cast<int>(ptrClientClass->iClassID);

	//get the handle to the owner who threw the grenade
	basecsplayer_t* ptrGrenadeThrower = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity_from_handle(ptrCurrentEntity->get_grenade_handle()));
	std::string_view szGrenadeThrowerName = xorstr_("NULL");
	if (ptrGrenadeThrower != nullptr)
	{
		//realistically shouldn't have to check return value here either but just in case for this i guess -_-
		playerinfo_t sPlayerInfo{};
		if (!nInterfaces::ptrEngine->get_player_info(ptrGrenadeThrower->index(), &sPlayerInfo))
			return;
		szGrenadeThrowerName = sPlayerInfo.szName;
	}

	FGUI::COLOR colGrenades = ptrCurrentEntity->isdormant() ? colDormant : FGUI::COLOR(255, 255, 255, 200);
	FGUI::COLOR colGrenadesDeadly = ptrCurrentEntity->isdormant() ? colDormant : FGUI::COLOR(255, 99, 71, 255);
	FGUI::COLOR colGrenadeBars = ptrCurrentEntity->isdormant() ? colDormant : FGUI::COLOR(0, 150, 255, 255);
	FGUI::COLOR colOutlines = ptrCurrentEntity->isdormant() ? colDormantOutlines : FGUI::COLOR(22, 22, 22, 200);
	FGUI::COLOR colBackgrounds = ptrCurrentEntity->isdormant() ? colDormantOutlines : FGUI::COLOR(22, 22, 22, 150);

	//grenades can bounce 20 times before popping regardless of velocity, without 20 bounces though
	//grenades will pop at < 0.1f velocity unless of course they're molotovs, flashbangs or high explosive
	//grenades which pop roughly 1.5 seconds after being thrown. players will rarely get this to 20 bounces
	//just a coolish feature to implement imo
	int iGrenadeBounces = ptrCurrentEntity->get_grenade_bounces();

	//a couple years ago valve did something to their grenade system which deletes the actual entitiy of high explosive grenades
	//after the smoke from the explosion dies down, which is pointless in having it like that as grenades won't do damage after 
	//they've exploded, obviously this essentially makes it so the grenade entity is alive way longer than it should be we now use 
	//this netvar which prevents rendering of the entity once it has exploded
	bool bDidExplodeEffectBegin = ptrCurrentEntity->get_explode_effect_begin();

	//gets the spawn time for the grenades, this allows us to do timers for them
	const float flGrenadeSpawnTime = ptrCurrentEntity->get_spawn_time();

	//if we're wanting to have the fire timer we need to do this mess, this is because the molotov effects aren't predictable and are randomised
	//therefore can't get the bounding box to it
	int iCastedBoundingBoxX{};
	int iCastedBoundingBoxY{};
	int iCastedBoundingBoxWidth{};
	int iCastedBoundingBoxHeight{};
	vector3d_t<float> vecScreenPosition{};
	vector2d_t<int> vecCastedScreenPoints{};

	if (iClassId == static_cast<int>(eClassId::CInferno))
	{
		//world to screen the fire position manually, kinda annoying
		vector3d_t<float> vecFireOrigin = ptrCurrentEntity->get_origin();
		if (!nInterfaces::ptrDebugOverlay->world_to_screen(vecFireOrigin, vecScreenPosition))
			return;

		vecCastedScreenPoints = { static_cast<int>(vecScreenPosition.tX), static_cast<int>(vecScreenPosition.tY) };
	}
	else
	{
		boundingbox_t sBoundingBox{};
		sBoundingBox = ptrCurrentEntity->get_bounding_box();
		if (sBoundingBox.flX == 0 || sBoundingBox.flY == 0 || sBoundingBox.flWidth == 0 || sBoundingBox.flHeight == 0)
			return;
		//cast the values to ints, this prevents warnings from the renderer about data loss from float to int conversions
		//could also use #pragma warning(disable : whatever the warning number is)
		iCastedBoundingBoxX = static_cast<int>(sBoundingBox.flX);
		iCastedBoundingBoxY = static_cast<int>(sBoundingBox.flY);
		iCastedBoundingBoxWidth = static_cast<int>(sBoundingBox.flWidth);
		iCastedBoundingBoxHeight = static_cast<int>(sBoundingBox.flHeight);
	}

	//smoke grenade information, have to place this here due to case labels skipping variable namings, which is annoying
	//i could put this into another function but that would just make this messy
	std::string_view szSmokeGrenade = xorstr_("Smoke grenade");
	if (iClassId == static_cast<int>(eClassId::CDecoyProjectile))
		szSmokeGrenade = xorstr_("Decoy");
	constexpr float flSmokeGrenadeDuration = 18.f;
	const int iSmokeStartTick = ptrCurrentEntity->get_smoke_grenade_effect_tick();
	const float flSmokeGrenadeTimer = ((TICKS_TO_TIME(iSmokeStartTick) + flSmokeGrenadeDuration) - nInterfaces::ptrGlobalVars->flCurtime) / flSmokeGrenadeDuration;

	//high explosive grenade and flashbang distinguishing and information this is distinguished by the model name, as the class is called CBaseCSGrenadeProjectile
	//which for some weird reason only includes flashbangs and he grenades. here are the full names of the models in this screenshot https://i.imgur.com/JI5rjDw.png
	//and simply checking character 22 is enough to tell which grenade is which
	std::string_view szHighExplosiveGrenade{};
	if (iClassId != static_cast<int>(eClassId::CInferno))
	{
		void* ptrModel = ptrCurrentEntity->get_model();
		if (ptrModel == nullptr)
			return;
		const char* szModelName = nInterfaces::ptrModelInfo->get_model_name(ptrModel);
		szHighExplosiveGrenade = xorstr_("High explosive grenade");
		if (szModelName[21] == 'l')
			szHighExplosiveGrenade = xorstr_("Flashbang");
	}

	//molotov and incindiary distinguishing and information
	std::string_view szMolotovName = xorstr_("Molotov");
	if (ptrCurrentEntity->get_incindiary_grenade())
		szMolotovName = xorstr_("Incindiary");
	//going to assume we're always playing on 64 tick servers as the difference between 128 and 64 tick changes are super minimal
	constexpr float flFireTime = 7.03125f;
	float flFireBar = ((flGrenadeSpawnTime + flFireTime) - nInterfaces::ptrGlobalVars->flCurtime) / flFireTime;

	switch (iClassId)
	{
	case static_cast<int>(eClassId::CDecoyProjectile):
	case static_cast<int>(eClassId::CSmokeGrenadeProjectile):
	{
		//grenade name
		nRender::text(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, szSmokeGrenade.data()).m_iWidth / static_cast<float>(2))),
			iCastedBoundingBoxY - 13, nRender::ulMuseoSans, colGrenades, szSmokeGrenade.data());
		//grenade thrower
		nRender::text(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, szGrenadeThrowerName.data()).m_iWidth / static_cast<float>(2))),
			iCastedBoundingBoxY + iCastedBoundingBoxHeight + 3, nRender::ulMuseoSans, colGrenades, szGrenadeThrowerName.data());
		//amount of times the grenade has bounced
		nRender::text(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, std::to_string(iGrenadeBounces).append(xorstr_(" bounces"))).m_iWidth / static_cast<float>(2))),
			static_cast<int>(iCastedBoundingBoxY + iCastedBoundingBoxHeight + nRender::text_size(nRender::ulMuseoSans, szGrenadeThrowerName.data()).m_iHeight + 3), nRender::ulMuseoSans, colGrenades, std::to_string(iGrenadeBounces).append(xorstr_(" bounces")));

		//render the timer, decoy grenades just won't run this code, hence why it's here
		if (ptrCurrentEntity->get_smoke_effect_began())
		{
			nRender::rectangle(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, szSmokeGrenade.data()).m_iWidth / static_cast<float>(2))) + 2,
				iCastedBoundingBoxY - 16, nRender::text_size(nRender::ulMuseoSans, szSmokeGrenade.data()).m_iWidth - 1, 2, colBackgrounds);
			nRender::outlined_rectangle(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - static_cast<int>(nRender::text_size(nRender::ulMuseoSans, szSmokeGrenade.data()).m_iWidth / static_cast<float>(2))) + 1,
				iCastedBoundingBoxY - 17, nRender::text_size(nRender::ulMuseoSans, szSmokeGrenade.data()).m_iWidth, 4, colOutlines);
			nRender::rectangle(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - static_cast<int>(nRender::text_size(nRender::ulMuseoSans, szSmokeGrenade.data()).m_iWidth / static_cast<float>(2))) + 2,
				iCastedBoundingBoxY - 16, (nRender::text_size(nRender::ulMuseoSans, szSmokeGrenade.data()).m_iWidth * flSmokeGrenadeTimer) - 1, 2, colGrenadeBars);
		}
		break;
	}
	case static_cast<int>(eClassId::CMolotovProjectile):
	case static_cast<int>(eClassId::CInferno):
	{
		if (ptrGrenadeThrower != nullptr)
		{
			//grenade name
			nRender::text(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, szMolotovName.data()).m_iWidth / static_cast<float>(2))),
				iCastedBoundingBoxY - 13, nRender::ulMuseoSans, colGrenadesDeadly, szMolotovName.data());
			//grenade thrower
			nRender::text(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, szGrenadeThrowerName.data()).m_iWidth / static_cast<float>(2))),
				iCastedBoundingBoxY + iCastedBoundingBoxHeight + 3, nRender::ulMuseoSans, colGrenades, szGrenadeThrowerName.data());
		}

		if (flFireBar > 0.f)
		{
			//render the grenade name
			nRender::text(static_cast<int>(vecCastedScreenPoints.tX - (nRender::text_size(nRender::ulMuseoSans, xorstr_("Fire grenade")).m_iWidth / static_cast<float>(2))),
				vecCastedScreenPoints.tY - 13, nRender::ulMuseoSans, FGUI::COLOR(255, 99, 71, 255), xorstr_("Fire grenade"));
			//the actual timer
			nRender::rectangle(vecCastedScreenPoints.tX - static_cast<int>(nRender::text_size(nRender::ulMuseoSans, xorstr_("Fire grenade")).m_iWidth / static_cast<float>(2)) + 2,
				vecCastedScreenPoints.tY + 1, nRender::text_size(nRender::ulMuseoSans, xorstr_("Fire grenade")).m_iWidth - 2, 2, colBackgrounds);
			nRender::outlined_rectangle(vecCastedScreenPoints.tX - static_cast<int>(nRender::text_size(nRender::ulMuseoSans, xorstr_("Fire grenade")).m_iWidth / static_cast<float>(2)) + 1,
				vecCastedScreenPoints.tY, nRender::text_size(nRender::ulMuseoSans, xorstr_("Fire grenade")).m_iWidth, 4, colOutlines);
			nRender::rectangle(vecCastedScreenPoints.tX - static_cast<int>(nRender::text_size(nRender::ulMuseoSans, xorstr_("Fire grenade")).m_iWidth / static_cast<float>(2)) + 2,
				vecCastedScreenPoints.tY + 1, ((nRender::text_size(nRender::ulMuseoSans, xorstr_("Fire grenade")).m_iWidth - 2) * flFireBar) + 1, 2, colGrenadeBars);
		}
		break;
	}
	case static_cast<int>(eClassId::CBaseCSGrenadeProjectile):
	{
		if (bDidExplodeEffectBegin)
			return;
		//grenade name
		nRender::text(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, szHighExplosiveGrenade.data()).m_iWidth / static_cast<float>(2))),
			iCastedBoundingBoxY - 13, nRender::ulMuseoSans, colGrenadesDeadly, szHighExplosiveGrenade.data());
		//grenade thrower
		nRender::text(static_cast<int>(iCastedBoundingBoxX + iCastedBoundingBoxWidth / static_cast<float>(2) - (nRender::text_size(nRender::ulMuseoSans, szGrenadeThrowerName.data()).m_iWidth / static_cast<float>(2))),
			iCastedBoundingBoxY + iCastedBoundingBoxHeight + 3, nRender::ulMuseoSans, colGrenades, szGrenadeThrowerName.data());
		break;
	}
	}

	//render box 
	nRender::outlined_rectangle(iCastedBoundingBoxX, iCastedBoundingBoxY, iCastedBoundingBoxWidth, iCastedBoundingBoxHeight, colGrenades);
	nRender::outlined_rectangle(iCastedBoundingBoxX - 1, iCastedBoundingBoxY - 1, iCastedBoundingBoxWidth + 2, iCastedBoundingBoxHeight + 2, colOutlines);
	nRender::outlined_rectangle(iCastedBoundingBoxX + 1, iCastedBoundingBoxY + 1, iCastedBoundingBoxWidth - 2, iCastedBoundingBoxHeight - 2, colOutlines);
#pragma warning(default : 4244)
}