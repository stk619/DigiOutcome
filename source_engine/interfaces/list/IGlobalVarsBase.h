#pragma once

struct IGlobalVarsBase
{
private:
	char szPad01[0x04]; //4
public:
	int iFrameCount; //8
private:
	char szPad02[0x36]; //62
};