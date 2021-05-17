#pragma once

//clientmode input struct, allows us to easily go to thirdperson
//https://www.unknowncheats.me/forum/counterstrike-global-offensive/428036-easy-alternative-internal-third-person-basically-3-lines.html
//NOTE: this is actually an interface, however no virtual functin usage is required as of right now
//		so adding interface isn't needed, that and this interface doesn't have a direct name, but is
//		obtained by signature which gets outdated a lot

struct clientmode_input_t
{
private:
	char szPad01[0xAD]; //173
public:
	//are we in thirdperson?
	bool bCamInThirdperson; //177
private:
	char szPad02[0x02]; //179
public:
	//vector that points where the camera is from behind the player
	vector3d_t vecCameraOffset;
private:
	char szPad03[0x48]; //263
public:
	//camera state
	int iCamCommand; //267
};