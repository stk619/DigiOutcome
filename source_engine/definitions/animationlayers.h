#pragma once

//truly bananas
//https://git.byr.ac.cn/Gaojianli/cstrike15_src/-/blob/master/game/client/animationlayer.h

struct animationlayer_t
{
private:
	char szPad01[0x18]; //24
public:
	unsigned int iSequence; //28
private:
	char szPad02[0x4]; //32
public:
	float flWeight; //36
private:
	char szPad03[0x8]; //44
public:
	float flCycle; //48
	void* ptrAnimationOwner;//52
private:
	char szPad04[0x4]; //56
};