#include "menu.h"

#include "../../common_includes.h"
//used in: font declarations
#include "../../other/renderer/renderer.h"
//used in: console logging
#include "../../other/console/console.h"
//used in: config event push back
#include "../../other/events/event_manager.h"

//awesome naming system :D
std::array<std::string, 10U> arrConfigNames = { xorstr_("Alpha.json"), xorstr_("Bravo.json"), xorstr_("Charlie.json"), xorstr_("Delta.json"), xorstr_("Echo.json"), xorstr_("Foxtrot.json"), xorstr_("Golf.json"), xorstr_("Hotel.json"), xorstr_("India.json"), xorstr_("Juliett.json") };

void save_config()
{
	nMenu::ptrMainWindow->SaveToFile(arrConfigNames[nMenu::ptrConfigCombobox->GetIndex()]);

	//construct event
	std::string szConfigEvent;
	szConfigEvent.append(xorstr_("[config saved] ")).append(arrConfigNames[nMenu::ptrConfigCombobox->GetIndex()]);
	sGameEventImplementation.deqEventLoggerList.emplace_front(szConfigEvent, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(0, 150, 255));
}

void load_config()
{
	nMenu::ptrMainWindow->LoadFromFile(arrConfigNames[nMenu::ptrConfigCombobox->GetIndex()]);

	//construct event
	std::string szConfigEvent;
	szConfigEvent.append(xorstr_("[config loaded] ")).append(arrConfigNames[nMenu::ptrConfigCombobox->GetIndex()]);
	sGameEventImplementation.deqEventLoggerList.emplace_front(szConfigEvent, nInterfaces::ptrGlobalVars->flCurtime, FGUI::COLOR(0, 150, 255));
}

bool nMenu::allocate()
{
	static FGUI::CBuilder cBuilder;

	static FGUI::WIDGET_FONT sMuseoSansBold;
	sMuseoSansBold.m_strFamily = xorstr_("Museo Sans");
	sMuseoSansBold.m_iSize = 12;
	sMuseoSansBold.m_nFlags = (eFontFlags::FONTFLAG_NONE);
	sMuseoSansBold.m_bBold = true;

	static FGUI::WIDGET_FONT sMuseoSans;
	sMuseoSans.m_strFamily = xorstr_("Museo Sans");
	sMuseoSans.m_iSize = 12;
	sMuseoSans.m_nFlags = (eFontFlags::FONTFLAG_ANTIALIAS);
	sMuseoSans.m_bBold = false;

	ptrMainWindow = std::make_shared<FGUI::CContainer>();
	cBuilder.Widget(ptrMainWindow).Title(xorstr_("csgo.assistant")).Position(100, 100).Size(602, 550).Font(sMuseoSansBold).Key(VK_INSERT).Flag(FGUI::WIDGET_FLAG::LIMIT);
	{
		ptrMainTabs = std::make_shared<FGUI::CTabPanel>();
		cBuilder.Widget(ptrMainTabs).Position(10, 16).Font(sMuseoSansBold).Tabs({ xorstr_("Aimbot"), xorstr_("Visuals"), xorstr_("Miscellaneous"), xorstr_("Players") }).Style(FGUI::ESTabLayout_t::HORIZONTAL).SpawnIn(ptrMainWindow, false);
		{
			//aimbot

			//visuals
			{
				ptrPlayerEspGroupbox = std::make_shared<FGUI::CContainer>();
				cBuilder.Widget(ptrPlayerEspGroupbox).Title(xorstr_("Players")).Position(10, 61).Size(270, 313).Font(sMuseoSansBold).Medium(ptrMainTabs, 1).SpawnIn(ptrMainWindow, false);
				{
					ptrBoundingBoxCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrBoundingBoxCheckbox).Title(xorstr_("Bounding box")).Position(10, 15).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrNameCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrNameCheckbox).Title(xorstr_("Name")).Position(10, 41).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrHealthBarCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrHealthBarCheckbox).Title(xorstr_("Health bar")).Position(10, 67).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrAmmoBarCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrAmmoBarCheckbox).Title(xorstr_("Ammo bar")).Position(10, 93).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrWeaponNameCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrWeaponNameCheckbox).Title(xorstr_("Weapon name")).Position(10, 119).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrFlagListMultibox = std::make_shared<FGUI::CMultiBox>();
					cBuilder.Widget(ptrFlagListMultibox).Title(xorstr_("Flags")).Position(10, 145).Font(sMuseoSans).Entries({ xorstr_("Armour"), xorstr_("Location"), xorstr_("Objectives"), xorstr_("Scoped"), xorstr_("Reloading"), xorstr_("Flashed"), xorstr_("Walking")}).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrGlowCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrGlowCheckbox).Title(xorstr_("Glow")).Position(10, 175).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrOutOfFovCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrOutOfFovCheckbox).Title(xorstr_("Out of fov arrows")).Position(10, 201).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrSoundsCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrSoundsCheckbox).Title(xorstr_("Sound rings")).Position(10, 227).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);

					ptrDormantCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrDormantCheckbox).Title(xorstr_("Dormant")).Position(10, 253).Font(sMuseoSans).SpawnIn(ptrPlayerEspGroupbox, false);
				}

				ptrChamsGroupbox = std::make_shared<FGUI::CContainer>();
				cBuilder.Widget(ptrChamsGroupbox).Title(xorstr_("Chams")).Position(10, 395).Size(270, 99).Font(sMuseoSansBold).Medium(ptrMainTabs, 1).SpawnIn(ptrMainWindow, false);
				{
					ptrVisibleChamsCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrVisibleChamsCheckbox).Title(xorstr_("Visible chams")).Position(10, 15).Font(sMuseoSans).SpawnIn(ptrChamsGroupbox, false);

					ptrInvisChamsCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrInvisChamsCheckbox).Title(xorstr_("Inisible chams")).Position(10, 41).Font(sMuseoSans).SpawnIn(ptrChamsGroupbox, false);

					ptrDisableOcclusionCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrDisableOcclusionCheckbox).Title(xorstr_("Disable occlusion")).Position(10, 67).Font(sMuseoSans).SpawnIn(ptrChamsGroupbox, false);
				}

				ptrWorldGroupbox = std::make_shared<FGUI::CContainer>();
				cBuilder.Widget(ptrWorldGroupbox).Title(xorstr_("World")).Position(301, 61).Size(270, 433).Font(sMuseoSansBold).Medium(ptrMainTabs, 1).SpawnIn(ptrMainWindow, false);
				{
					ptrHostageCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrHostageCheckbox).Title(xorstr_("Hostages")).Position(10, 15).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrDroppedItemsMultibox = std::make_shared<FGUI::CMultiBox>();
					cBuilder.Widget(ptrDroppedItemsMultibox).Title(xorstr_("Dropped items")).Position(10, 41).Font(sMuseoSans).Entries({ xorstr_("Weapons"), xorstr_("Items") }).SpawnIn(ptrWorldGroupbox, false);

					ptrThrownGrenadesCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrThrownGrenadesCheckbox).Title(xorstr_("Thrown grenades")).Position(10, 71).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrBombCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrBombCheckbox).Title(xorstr_("Bomb")).Position(10, 97).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrGrenadePredictionCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrGrenadePredictionCheckbox).Title(xorstr_("Grenade prediction")).Position(10, 123).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrSpectatorsCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrSpectatorsCheckbox).Title(xorstr_("Spectators")).Position(10, 149).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrRecoilCrosshairCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrRecoilCrosshairCheckbox).Title(xorstr_("Recoil crosshair")).Position(10, 175).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrBulletTracersCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrBulletTracersCheckbox).Title(xorstr_("Bullet tracers")).Position(10, 201).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrBulletImpactsCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrBulletImpactsCheckbox).Title(xorstr_("Bullet impacts")).Position(10, 227).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrWorldPropModsCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrWorldPropModsCheckbox).Title(xorstr_("World prop modulation")).Position(10, 253).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrStaticPropModsCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrStaticPropModsCheckbox).Title(xorstr_("Static prop modulation")).Position(10, 279).Font(sMuseoSans).SpawnIn(ptrWorldGroupbox, false);

					ptrRemoveablesMultibox = std::make_shared<FGUI::CMultiBox>();
					cBuilder.Widget(ptrRemoveablesMultibox).Title(xorstr_("Removeables")).Position(10, 305).Font(sMuseoSans).Entries({ xorstr_("Post processing"), xorstr_("Flashbangs"), xorstr_("Smoke grenades"), xorstr_("Recoil"), xorstr_("Scope overlay") }).SpawnIn(ptrWorldGroupbox, false);

				}
			}

			//miscellaneous
			{
				ptrMiscGroupbox = std::make_shared<FGUI::CContainer>();
				cBuilder.Widget(ptrMiscGroupbox).Title(xorstr_("Miscellaneous")).Position(10, 61).Size(270, 433).Font(sMuseoSansBold).Medium(ptrMainTabs, 2).SpawnIn(ptrMainWindow, false);
				{
					ptrFovSlider = std::make_shared<FGUI::CSlider>();
					cBuilder.Widget(ptrFovSlider).Title(xorstr_("Fov")).Position(10, 27).Font(sMuseoSans).Range(0, 60).Value(0).SpawnIn(ptrMiscGroupbox, false);

					ptrFovViewmodelSlider = std::make_shared<FGUI::CSlider>();
					cBuilder.Widget(ptrFovViewmodelSlider).Title(xorstr_("Viewmodel Fov")).Position(10, 59).Font(sMuseoSans).Range(0, 60).Value(0).SpawnIn(ptrMiscGroupbox, false);

					ptrBunnyhopCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrBunnyhopCheckbox).Title(xorstr_("Bunnyhop")).Position(10, 79).Font(sMuseoSans).SpawnIn(ptrMiscGroupbox, false);

					ptrInfiniteDuckCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrInfiniteDuckCheckbox).Title(xorstr_("Infinite duck")).Position(10, 105).Font(sMuseoSans).SpawnIn(ptrMiscGroupbox, false);

					ptrEdgeJumpKeybinder = std::make_shared<FGUI::CKeyBinder>();
					cBuilder.Widget(ptrEdgeJumpKeybinder).Title(xorstr_("Edge jump key")).Position(10, 131).Font(sMuseoSans).Style(FGUI::KEY_BINDER_STYLE::HOLD).SpawnIn(ptrMiscGroupbox, false);

					ptrThirdPersonKeybinder = std::make_shared<FGUI::CKeyBinder>();
					cBuilder.Widget(ptrThirdPersonKeybinder).Title(xorstr_("Thirdperson key")).Position(10, 161).Font(sMuseoSans).Style(FGUI::KEY_BINDER_STYLE::TOGGLE).SpawnIn(ptrMiscGroupbox, false);

					ptrThirdpersonDistSlider = std::make_shared<FGUI::CSlider>();
					cBuilder.Widget(ptrThirdpersonDistSlider).Title(xorstr_("Thirdperson distance")).Position(10, 203).Font(sMuseoSans).Range(150, 300).Value(200).SpawnIn(ptrMiscGroupbox, false);

					ptrAutoPistolCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrAutoPistolCheckbox).Title(xorstr_("Auto pistol")).Position(10, 223).Font(sMuseoSans).SpawnIn(ptrMiscGroupbox, false);

					ptrCustomClantagTextbox = std::make_shared<FGUI::CTextBox>();
					cBuilder.Widget(ptrCustomClantagTextbox).Title(xorstr_("Clantag")).Position(10, 249).Font(sMuseoSans).Length(12).SpawnIn(ptrMiscGroupbox, false);

					ptrHitmarkerCheckbox = std::make_shared<FGUI::CCheckBox>();
					cBuilder.Widget(ptrHitmarkerCheckbox).Title(xorstr_("Hitmarker")).Position(10, 279).Font(sMuseoSans).SpawnIn(ptrMiscGroupbox, false);

					ptrEventLoggerMultibox = std::make_shared<FGUI::CMultiBox>();
					cBuilder.Widget(ptrEventLoggerMultibox).Title(xorstr_("Event logger")).Position(10, 305).Font(sMuseoSans).Entries({ xorstr_("Damage"), xorstr_("Objectives") }).SpawnIn(ptrMiscGroupbox, false);
				}

				ptrSettingsGroupbox = std::make_shared<FGUI::CContainer>();
				cBuilder.Widget(ptrSettingsGroupbox).Title(xorstr_("Settings")).Position(301, 61).Size(270, 433).Font(sMuseoSansBold).Medium(ptrMainTabs, 2).SpawnIn(ptrMainWindow, false);
				{
					ptrConfigCombobox = std::make_shared<FGUI::CComboBox>();
					cBuilder.Widget(ptrConfigCombobox).Title(xorstr_("Custom configuration")).Position(10, 15).Font(sMuseoSans).Entries({ xorstr_("Alpha"), xorstr_("Bravo"), xorstr_("Charlie"), xorstr_("Delta"), xorstr_("Echo"), xorstr_("Foxtrot"), xorstr_("Golf"), xorstr_("Hotel"), xorstr_("India"), xorstr_("Juliett") }).SpawnIn(ptrSettingsGroupbox, false);

					ptrSaveConfigButton = std::make_shared<FGUI::CButton>();
					cBuilder.Widget(ptrSaveConfigButton).Title(xorstr_("Save configuration")).Position(10, 45).Font(sMuseoSans).Callback(save_config).SpawnIn(ptrSettingsGroupbox, false);

					ptrLoadConfigButton = std::make_shared<FGUI::CButton>();
					cBuilder.Widget(ptrLoadConfigButton).Title(xorstr_("Load configuration")).Position(10, 85).Font(sMuseoSans).Callback(load_config).SpawnIn(ptrSettingsGroupbox, false);
				}
			}

			//players
			{
				ptrPlayersGroupbox = std::make_shared<FGUI::CContainer>();
				cBuilder.Widget(ptrPlayersGroupbox).Title(xorstr_("Players")).Position(10, 61).Size(270, 433).Font(sMuseoSansBold).Medium(ptrMainTabs, 3).SpawnIn(ptrMainWindow, false);
				{
					ptrPlayersListBox = std::make_shared<FGUI::CListBox>();
					cBuilder.Widget(ptrPlayersListBox).Title(xorstr_("")).Position(10, 15).Size(251, 409).Font(sMuseoSans).SpawnIn(ptrPlayersGroupbox, false);
				}

				ptrModificationsGroupbox = std::make_shared<FGUI::CContainer>();
				cBuilder.Widget(ptrModificationsGroupbox).Title(xorstr_("Modifications")).Position(301, 61).Size(270, 433).Font(sMuseoSansBold).Medium(ptrMainTabs, 3).SpawnIn(ptrMainWindow, false);
				{

				}
			}
		}
	}

	sConsole.log(eLogType::MAIN, xorstr_("menu finished allocating"));
	return true;
}