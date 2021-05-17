#pragma once
#include "../../common_includes.h"

enum class eKeyState
{
	UP = 0,
	TOGGLED = 1,
	DOWN = 2,
};

struct key_state_t 
{
	eKeyState iKeyState;
	int iFrameCount;
};

//pretty much pasted input handler, messing around with nInterfaces::ptrInputSystem->is_button_down was just
//pissing me off so bad, this just works better.
struct input_t
{
public:
	//general handling
	bool allocate();
	void free();
private:
	//hook and hook handler
	void handle_wndproc_input(UINT uiMessage, WPARAM uiParameter, LPARAM lParameter);
	static LRESULT __stdcall wndproc(HWND hWindow, UINT uiMessage, WPARAM uiParameter, LPARAM lParameter);

public:
	//functions
	bool key_held(int iKey);
	bool key_up(int iKey);
	bool toggle_key(int iKey);
	bool toggle_key(int iKey, bool& bItem);
	bool mouse_in_boundaries(int iX, int iY, int iWidth, int iHeight);

private:
	//members
	//array of key states, for now we assume they're all up
	std::array<key_state_t, 256> arrKeyStates = { eKeyState::UP };
	int iLastKeyPressed;
	vector2d_t vecMousePosition;
};
inline input_t sInput;