#pragma once
//used in: math includes
#include "vector3d.h"
#include "matrix3x4.h"

namespace nMath
{
	//used in bounding box calculations
	inline void vector_transform(vector3d_t<float>& vecInput, const matrix3x4_t sMatrix, vector3d_t<float>& vecOutput)
	{
		vecOutput.tX = vecInput.dot(sMatrix[0]) + sMatrix[0][3];
		vecOutput.tY = vecInput.dot(sMatrix[1]) + sMatrix[1][3];
		vecOutput.tZ = vecInput.dot(sMatrix[2]) + sMatrix[2][3];
	}
}