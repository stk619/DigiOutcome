#include "input.h"
//used in: console logging
#include "../console/console.h"
//used in: globalvars interface
#include "../../source_engine/interfaces/interfaces.h"

//window procedure hooking, this is what we will be using for our input struct
//http://www.winprog.org/tutorial/window_click.html
//this is taken from: https://github.com/binkynz/cstrike-hack/tree/master/cstrike/input
//as i've never used wndproc before this hasn't been coded by myself, in the past i've
//instead been relying on Valve's input system interface for input management as well as the 
//surface interface's virtual function for scroll delta and mouse positioning, this works much better!

WNDPROC oWndProcOriginal = NULL;

void input_t::handle_wndproc_input(UINT uiMessage, WPARAM uiParameter, LPARAM lParameter)
{
	int iKey;
	eKeyState iKeyState;

	//whenever we move our mouse, this will update its exact position, this means we don't
	//need to access valve's stupid surface vfunc for our mouse position :D
	if (uiMessage == WM_MOUSEMOVE)
		sInput.vecMousePosition = { static_cast<float>(GET_X_LPARAM(lParameter)), static_cast<float>(GET_Y_LPARAM(lParameter)) };

	//different keys produce different message types, this acts as a handler for them
	//https://wiki.winehq.org/List_Of_Windows_Messages list of used messages
	switch (uiMessage)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		iKey = uiParameter;
		iKeyState = eKeyState::DOWN;
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		iKey = uiParameter;
		iKeyState = eKeyState::UP;
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		iKey = VK_LBUTTON;
		iKeyState = uiMessage == WM_LBUTTONUP ? eKeyState::UP : eKeyState::DOWN;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		iKey = VK_RBUTTON;
		iKeyState = uiMessage == WM_RBUTTONUP ? eKeyState::UP : eKeyState::DOWN;
		break;
	//the original source never accounted for xbutton inputs. this does it though :D
	//https://docs.microsoft.com/en-us/windows/win32/learnwin32/mouse-clicks
	//https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-xbuttondown
	//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	//i'm loove microsoft :DDD
	case WM_XBUTTONDBLCLK:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		iKey = (GET_XBUTTON_WPARAM(uiParameter) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		iKeyState = uiMessage == WM_XBUTTONUP ? eKeyState::UP : eKeyState::DOWN;
		break;
	//same situation for the middle mouse clicks :|
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		iKey = VK_MBUTTON;
		iKeyState = uiMessage == WM_MBUTTONUP ? eKeyState::UP : eKeyState::DOWN;
		break;
	default:
		return;
	}

	//key state handler, allows us to use eKeyState::DOWN as a held down key, with a slight delay
	//as well as toggled functions
	if (sInput.arrKeyStates[iKey].iKeyState == eKeyState::UP && iKeyState == eKeyState::DOWN)
	{
		sInput.arrKeyStates[iKey].iFrameCount = nInterfaces::ptrGlobalVars->iFrameCount + 1;
		sInput.arrKeyStates[iKey].iKeyState = eKeyState::TOGGLED;
		sInput.iLastKeyPressed = iKey;
	}
	else
		sInput.arrKeyStates[iKey].iKeyState = iKeyState;
}


//winproc hooking
bool input_t::allocate()
{
	//manual logging of the hooked function, this is because the hooking system used here doesn't
	//allow for hooking methods such as this.
	oWndProcOriginal = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hGlobalWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&wndproc)));
	if (!oWndProcOriginal)
		return false;
	sConsole.log(eLogType::LOG, xorstr_("wndproc hooked at address: 0x%x, original: 0x%x"), &wndproc, oWndProcOriginal);

	sConsole.log(eLogType::MAIN, xorstr_("input finished allocating"));
	return true;
}

//no need to null check the original function as for it to even free, it can't be null to begin with
void input_t::free()
{
	SetWindowLongPtr(hGlobalWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProcOriginal));
}

//hooking window process for the input functionality
LRESULT __stdcall input_t::wndproc(HWND hWindow, UINT uiMessage, WPARAM uiParameter, LPARAM lParameter)
{
	//only in a different function due to the default case in the switch list, it needs to return a value of LRESULT if
	//placed into the hook here.
	sInput.handle_wndproc_input(uiMessage, uiParameter, lParameter);
	
	if (nConfiguration::sMenu.bOpened)
		return 11;

	return CallWindowProcW(oWndProcOriginal, hWindow, uiMessage, uiParameter, lParameter);
}

//functions
bool input_t::key_held(int iKey)
{
	return sInput.arrKeyStates[iKey].iKeyState == eKeyState::DOWN;
}

bool input_t::key_up(int iKey)
{
	return sInput.arrKeyStates[iKey].iKeyState == eKeyState::UP;
}

bool input_t::toggle_key(int iKey)
{
	if (sInput.arrKeyStates[iKey].iKeyState != eKeyState::TOGGLED)
		return false;

	return sInput.arrKeyStates[iKey].iFrameCount == nInterfaces::ptrGlobalVars->iFrameCount;
}

bool input_t::toggle_key(int iKey, bool & bItem)
{
	if (sInput.toggle_key(iKey))
		bItem = !bItem;

	return bItem;
}

bool input_t::mouse_in_boundaries(int iX, int iY, int iWidth, int iHeight)
{
	return (sInput.vecMousePosition.flX > iX) && (sInput.vecMousePosition.flY > iY) && (sInput.vecMousePosition.flX < (iX + iWidth)) && (sInput.vecMousePosition.flY < (iY + iHeight));
}