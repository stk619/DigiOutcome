#pragma once

//simple vector struct with 3d vector co-ordinates
template <typename T = int>
struct vector3d_t
{
	vector3d_t() = default;
	vector3d_t(T tX, T tY, T tZ)
	{
		this->tX = tX;
		this->tY = tY;
		this->tZ = tZ;
	}

	T tX;
	T tY;
	T tZ;

	vector3d_t operator+(vector3d_t vecAdd)
	{
		return { this->tX - vecAdd.tX, this->tY - vecAdd.tY, this->tZ - vecAdd.tZ };
	}

	vector3d_t operator-(vector3d_t vecSub)
	{
		return { this->tX - vecSub.tX, this->tY - vecSub.tY, this->tZ - vecSub.tZ };
	}

	vector3d_t operator/(vector3d_t vecDiv)
	{
		return { this->tX / vecDiv.tX, this->tY / vecDiv.tY, this->tZ - vecDiv.tZ };
	}

	vector3d_t operator*(vector3d_t vecMul)
	{
		return { this->tX * vecMul.tX, this->tY * vecMul.tY, this->tZ - vecMul.tZ };
	}

	vector3d_t operator+=(vector3d_t vecAdd)
	{
		return { this->tX += vecAdd.tX, this->tY += vecAdd.tY, this->tZ - vecAdd.tZ };
	}

	vector3d_t operator-=(vector3d_t vecSub)
	{
		return { this->tX -= vecSub.tX, this->tY -= vecSub.tY, this->tZ - vecSub.tZ };
	}

	vector3d_t operator/=(vector3d_t vecDiv)
	{
		return { this->tX /= vecDiv.tX, this->tY /= vecDiv.tY, this->tZ - vecDiv.tZ };
	}

	vector3d_t operator*=(vector3d_t vecMul)
	{
		return { this->tX *= vecMul.tX, this->tY *= vecMul.tY, this->tZ - vecMul.tZ };
	}

	float length()
	{
		return sqrt(this->tX * this->tX + this->tY * this->tY + this->tZ * this->tZ);
	}

	float distance_to(vector3d_t vecOrigin)
	{
		this->tX -= vecOrigin.tX;
		this->tY -= vecOrigin.tY;
		this->tZ -= vecOrigin.tZ;
		return this->length();
	}

	float dot(const float* flProduct) 
	{
		const vector3d_t<float>& vecThis = *this;
		return (vecThis.tX * flProduct[0] + vecThis.tY * flProduct[1] + vecThis.tZ * flProduct[2]);
	}
};