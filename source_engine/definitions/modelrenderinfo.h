#pragma once

struct modelrenderinfo_t
{
	vector3d_t<float> vecOrigin;
	vector3d_t<float> angAngles; //QAngle
	std::size_t ptrRenderable;
	void* ptrModel;
private:
	char szPad01[0x4];
public:
	const matrix3x4_t* sModelToWorld;
	const matrix3x4_t* sLightingOffset;
	const vector3d_t<float>* vecLightingOrigin;
	int iFlags;
	int iEntityIndex;
	int iSkin;
	int iBody;
	int iHitboxSet;
	void* sModelInstance;
};