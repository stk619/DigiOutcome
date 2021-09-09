#pragma once
//used in: virtual functions
#include "../../../other/utilities/utilities.h"

struct IVGameEventManager
{
private:
	enum eIndices
	{
		GETNAME = 1,
		GETINT = 6,
		GETFLOAT = 8,
		GETSTRING = 9
	};

public:
	const char* get_name()
	{
		return nUtilities::vfunc<const char*(__thiscall*)(IVGameEventManager*)>(this, GETNAME)(this);
	}
	int get_int(const char* szEventName, int iDefaultValue = 0)
	{
		return nUtilities::vfunc<int(__thiscall*)(IVGameEventManager*, const char*, int)>(this, GETINT)(this, szEventName, iDefaultValue);
	}
	float get_float(const char* szEventName, float flDefaultValue = 0.f)
	{
		return nUtilities::vfunc<float(__thiscall*)(IVGameEventManager*, const char*, float)>(this, GETFLOAT)(this, szEventName, flDefaultValue);
	}
	const char* get_string(const char* szEventName, const char* szDefaultValue = xorstr_(""))
	{
		return nUtilities::vfunc<const char* (__thiscall*)(IVGameEventManager*, const char*, const char*)>(this, GETSTRING)(this, szEventName, szDefaultValue);
	}
};

struct gameevent_t
{
protected:
	virtual ~gameevent_t() {}
	virtual void fire_game_event(IVGameEventManager* ptrGameEventManager) = 0;
	virtual int get_event_debug_id()
	{
		//always 42 for csgo
		return 42;
	}
};

struct IVGameEventManager2
{
private:
	enum eIndices
	{
		ADDLISTENER = 3,
		REMOVELISTENER = 5
	};

public:
	bool add_listener(gameevent_t* ptrGameEvent, const char* szEventName)
	{
		return nUtilities::vfunc<bool(__thiscall*)(IVGameEventManager2*, gameevent_t*, const char*, bool)>(this, ADDLISTENER)(this, ptrGameEvent, szEventName, false);
	}
	void remove_listener(gameevent_t* ptrGameEvent)
	{
		return nUtilities::vfunc< void(__thiscall*)(IVGameEventManager2*, gameevent_t*)>(this, REMOVELISTENER)(this, ptrGameEvent); //NOTE: only crashes when typing quit in console
	}
};