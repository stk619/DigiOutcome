#pragma once

#define FGUI_IMPLEMENTATION
#include "../FGUI/FGUI.h"

namespace nMenu
{
	bool allocate();

	inline std::shared_ptr<FGUI::CContainer> ptrMainWindow;

	inline std::shared_ptr<FGUI::CTabPanel> ptrMainTabs;

	//aimbot

	//visuals
	inline std::shared_ptr<FGUI::CContainer> ptrPlayerEspGroupbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrBoundingBoxCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrNameCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrHealthBarCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrAmmoBarCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrWeaponNameCheckbox;
	inline std::shared_ptr<FGUI::CMultiBox> ptrFlagListMultibox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrGlowCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrOutOfFovCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrSoundsCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrDormantCheckbox;

	inline std::shared_ptr<FGUI::CContainer> ptrChamsGroupbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrVisibleChamsCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrInvisChamsCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrDisableOcclusionCheckbox;

	inline std::shared_ptr<FGUI::CContainer> ptrWorldGroupbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrHostageCheckbox;
	inline std::shared_ptr<FGUI::CMultiBox> ptrDroppedItemsMultibox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrThrownGrenadesCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrBombCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrGrenadePredictionCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrSpectatorsCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrRecoilCrosshairCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrBulletTracersCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrBulletImpactsCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrWorldPropModsCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrStaticPropModsCheckbox;
	inline std::shared_ptr<FGUI::CMultiBox> ptrRemoveablesMultibox;

	//miscellaneous
	inline std::shared_ptr<FGUI::CContainer> ptrMiscGroupbox;
	inline std::shared_ptr<FGUI::CSlider> ptrFovSlider;
	inline std::shared_ptr<FGUI::CSlider> ptrFovViewmodelSlider;
	inline std::shared_ptr<FGUI::CCheckBox> ptrBunnyhopCheckbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrInfiniteDuckCheckbox;
	inline std::shared_ptr<FGUI::CKeyBinder> ptrEdgeJumpKeybinder;
	inline std::shared_ptr<FGUI::CKeyBinder> ptrThirdPersonKeybinder;
	inline std::shared_ptr<FGUI::CSlider> ptrThirdpersonDistSlider;
	inline std::shared_ptr<FGUI::CCheckBox> ptrAutoPistolCheckbox;
	inline std::shared_ptr<FGUI::CTextBox> ptrCustomClantagTextbox;
	inline std::shared_ptr<FGUI::CCheckBox> ptrHitmarkerCheckbox;
	inline std::shared_ptr<FGUI::CMultiBox> ptrEventLoggerMultibox;

	inline std::shared_ptr<FGUI::CContainer> ptrSettingsGroupbox;
	inline std::shared_ptr<FGUI::CComboBox> ptrConfigCombobox;
	inline std::shared_ptr<FGUI::CButton> ptrSaveConfigButton;
	inline std::shared_ptr<FGUI::CButton> ptrLoadConfigButton;

	//players
	inline std::shared_ptr<FGUI::CContainer> ptrPlayersGroupbox;
	inline std::shared_ptr<FGUI::CListBox> ptrPlayersListBox;

	inline std::shared_ptr<FGUI::CContainer> ptrModificationsGroupbox;
}