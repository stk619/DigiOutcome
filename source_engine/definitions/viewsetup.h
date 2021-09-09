#pragma once

//viewsetup
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/public/view_shared.h#L120
//only ever used for a few functions so far, list can be found here

struct viewsetup_t
{
private:
	char szPad01[0xB0]; //176
public:
	float flFov; //180
private:
	char szPad02[0x98]; //332
};