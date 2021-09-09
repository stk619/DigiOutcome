#pragma once
#include "../../common_includes.h"

struct csweapondata_t
{
public:
	std::byte	pad0[0x14];				// 0x0000
	int			iMaxClip1;				// 0x0014
	int			iMaxClip2;				// 0x0018
	int			iDefaultClip1;			// 0x001C
	int			iDefaultClip2;			// 0x0020
	int			iPrimaryMaxReserveAmmo; // 0x0024
	int			iSecondaryMaxReserveAmmo; // 0x0028
	char* szWorldModel;			// 0x002C
	char* szViewModel;			// 0x0030
	char* szDroppedModel;			// 0x0034
	std::byte	pad1[0x50];				// 0x0038
	char* szHudName;				// 0x0088
	char* szWeaponName;			// 0x008C
	std::byte	pad2[0x2];				// 0x0090
	bool		bIsMeleeWeapon;			// 0x0092
	std::byte	pad3[0x9];				// 0x0093
	float		flWeaponWeight;			// 0x009C
	std::byte	pad4[0x28];				// 0x00A0
	int			nWeaponType;			// 0x00C8
	std::byte	pad5[0x4];				// 0x00CC
	int			iWeaponPrice;			// 0x00D0
	int			iKillAward;				// 0x00D4
	std::byte	pad6[0x4];				// 0x00D8
	float		flCycleTime;			// 0x00DC
	float		flCycleTimeAlt;			// 0x00E0
	std::byte	pad7[0x8];				// 0x00E4
	bool		bFullAuto;				// 0x00EC
	std::byte	pad8[0x3];				// 0x00ED
	int			iDamage;				// 0x00F0
	float		flArmorRatio;			// 0x00F4
	int			iBullets;				// 0x00F8
	float		flPenetration;			// 0x00FC
	std::byte	pad9[0x8];				// 0x0100
	float		flRange;				// 0x0108
	float		flRangeModifier;		// 0x010C
	float		flThrowVelocity;		// 0x0110
	std::byte	pad10[0xC];				// 0x0114
	bool		bHasSilencer;			// 0x0120
	std::byte	pad11[0xB];				// 0x0121
	char* szBulletType;			// 0x012C
	float		flMaxSpeed;				// 0x0130
	float		flMaxSpeedAlt;			// 0x0134
	float		flSpread;				// 0x0138
	float		flSpreadAlt;			// 0x013C
	std::byte	pad12[0x44];			// 0x0180
	int			iRecoilSeed;			// 0x0184
	std::byte	pad13[0x20];			// 0x0188
};