#pragma once
//used in: button codes
#include "general_defines.h"

//size seems to be 100bytes long
struct usercmd_t
{
private:
	char szPad01[0x30]; //48
public:
	//local player button states
	int iButtons; //52
private:
	char szPad02[0x30]; //100
};