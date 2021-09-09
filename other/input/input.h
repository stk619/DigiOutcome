#pragma once
#include "../../common_includes.h"

#define FGUI_IMPLEMENTATION
#include "../../main/FGUI/FGUI.h"

//used in: surface cursor positioning
#include "../../source_engine/interfaces/interfaces.h"

//i keep getting unresolved externals from having all this listed in the .cpp file, i'm not sure why, it's probably because the include system
//of mine is wonky lol and that's just defining everything multiple times in different locations, i'm leaving this all in the .h file as this
//actually works
namespace nInput
{
	inline std::array<bool, 256> arrCurrentPressedKeys;
	inline std::array<bool, 256> arrpOldPressedKeys;
	inline FGUI::POINT ptCursorPosition;
	inline FGUI::POINT ptCursorPositionDelta;

	inline void poll_input()
	{
		static FGUI::POINT ptLastKnownPosition = { 0, 0 };

		std::copy(arrCurrentPressedKeys.begin(), arrCurrentPressedKeys.end(), arrpOldPressedKeys.begin());

		for (int iKeyIndex = 0; iKeyIndex < 256; ++iKeyIndex)
			arrCurrentPressedKeys.at(iKeyIndex) = GetAsyncKeyState(iKeyIndex);

		nInterfaces::ptrSurface->get_cursor_pos(ptCursorPosition.m_iX, ptCursorPosition.m_iY);
		ptCursorPositionDelta = { (ptCursorPosition.m_iX - ptLastKnownPosition.m_iX), (ptCursorPosition.m_iY - ptLastKnownPosition.m_iY) };
		ptLastKnownPosition = ptCursorPosition;
	}

	inline bool key_held(unsigned int uiKeyCode)
	{
		return arrCurrentPressedKeys.at(uiKeyCode);
	}

	inline bool key_released(unsigned int uiKeyCode)
	{
		return (!arrCurrentPressedKeys.at(uiKeyCode) && arrpOldPressedKeys.at(uiKeyCode));
	}

	inline bool key_pressed(unsigned int uiKeyCode)
	{
		return (arrCurrentPressedKeys.at(uiKeyCode) && !arrpOldPressedKeys.at(uiKeyCode));
	}

	inline FGUI::POINT get_cursor_pos()
	{
		return ptCursorPosition;
	}

	inline FGUI::POINT cursor_pos_delta()
	{
		return ptCursorPositionDelta;
	}

	inline bool mouse_in_boundaries(FGUI::AREA arArea)
	{
		return (get_cursor_pos().m_iX > arArea.m_iLeft && get_cursor_pos().m_iY > arArea.m_iTop &&
			get_cursor_pos().m_iX < arArea.m_iLeft + arArea.m_iRight && get_cursor_pos().m_iY < arArea.m_iTop + arArea.m_iBottom);
	}

	inline bool allocate()
	{
		FGUI::INPUT.PullInput = poll_input;
		FGUI::INPUT.IsKeyHeld = key_held;
		FGUI::INPUT.IsKeyReleased = key_released;
		FGUI::INPUT.IsKeyPressed = key_pressed;
		FGUI::INPUT.GetCursorPos = get_cursor_pos;
		FGUI::INPUT.GetCursorPosDelta = cursor_pos_delta;
		FGUI::INPUT.IsCursorInArea = mouse_in_boundaries;

		FGUI::INPUT.SetInputType(FGUI::INPUT_TYPE::WIN_32);

		sConsole.log(eLogType::MAIN, xorstr_("input finished allocating"));
		return true;
	}
}