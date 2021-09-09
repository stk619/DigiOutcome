#pragma once

//man i really hate messing with matrix stuff
struct matrix3x4_t
{
public:
	float* operator[](int i) { return flMatrix[i]; }
	const float* operator[](int i) const { return flMatrix[i]; }
	float flMatrix[3][4];
};