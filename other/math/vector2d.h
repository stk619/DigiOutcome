#pragma once

//vector struct for 2 dimensional coordinates
template <typename T = int> 
struct vector2d_t
{
	vector2d_t() = default;
	vector2d_t(T tX, T tY)
	{
		this->tX = tX;
		this->tY = tY;
	}

	T tX;
	T tY;

	vector2d_t operator+(vector2d_t vecAdd)
	{
		return { this->tX - vecAdd.tX, this->tY - vecAdd.tY };
	}

	vector2d_t operator-(vector2d_t vecSub)
	{
		return { this->tX - vecSub.tX, this->tY - vecSub.tY };
	}

	vector2d_t operator/(vector2d_t vecDiv)
	{
		return { this->tX / vecDiv.tX, this->tY / vecDiv.tY };
	}

	vector2d_t operator*(vector2d_t vecMul)
	{
		return { this->tX * vecMul.tX, this->tY * vecMul.tY };
	}

	vector2d_t operator+=(vector2d_t vecAdd)
	{
		return { this->tX += vecAdd.tX, this->tY += vecAdd.tY };
	}

	vector2d_t operator-=(vector2d_t vecSub)
	{
		return { this->tX -= vecSub.tX, this->tY -= vecSub.tY };
	}

	vector2d_t operator/=(vector2d_t vecDiv)
	{
		return { this->tX /= vecDiv.tX, this->tY /= vecDiv.tY };
	}

	vector2d_t operator*=(vector2d_t vecMul)
	{
		return { this->tX *= vecMul.tX, this->tY *= vecMul.tY };
	}
};