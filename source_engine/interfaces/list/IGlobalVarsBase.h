#pragma once

struct IGlobalVarsBase
{
private:
	char szPad01[0x04]; //4
public:
	int iFrameCount; //8
private:
	char szPad02[0x08]; //16
public:
	float flCurtime; //20
private:
	char szPad03[0x8]; //28
public:
	int iTickCount; //32
	float flIntervalPerTick; // 36
private:
	char szPad04[0x1A]; //62
};