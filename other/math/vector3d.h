#pragma once

//simple vector struct with 3d vector co-ordinates
struct vector3d_t
{
	vector3d_t() = default;
	vector3d_t(float flX, float flY, float flZ)
	{
		this->flX = flX;
		this->flY = flY;
		this->flZ = flZ;
	}

	float flX;
	float flY;
	float flZ;
};