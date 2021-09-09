#pragma once
//https://git.byr.ac.cn/Gaojianli/cstrike15_src/-/blob/master/public/cdll_int.h#L129
struct playerinfo_t
{
private:
	char szPad01[0x8]; //8
public:
	union //16
	{
		unsigned long long ullXuid;
		struct 
		{
			int iXuidLow;
			int iXuidHigh;
		};
	};
	char szName[128]; //144
	int iUserId; //148
	char szGuid[33]; //181
	unsigned int uiFriendsId; //185
	char szFriendsName[128]; //313
	bool bFakePlayer; //317
	bool bIsHLTV; //321
	unsigned int iCustomFiles[4];
	char szFilesDownloaded;
};
