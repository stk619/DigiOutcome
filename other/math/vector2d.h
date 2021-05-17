#pragma once

//vector struct for 2 dimensional coordinates
struct vector2d_t
{
public:
	vector2d_t() = default;
	vector2d_t(float flX, float flY)
	{
		this->flX = flX;
		this->flY = flY;
	}

	float flX;
	float flY;
};