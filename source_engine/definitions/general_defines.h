#pragma once

//for our font management
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/game/client/imessagechars.h#L24
typedef unsigned int hFont;

//font flags
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/common/vgui_surfacelib/ifontsurface.h#L32
enum eFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,		// custom generated font - never fall back to asian compatibility mode
	FONTFLAG_BITMAP = 0x800,		// compiled bitmap font - no fallbacks
};

//for cmd->iButtons taken from leaked sdk
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/game/shared/in_buttons.h
enum eButtonStates
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVE_LEFT = (1 << 9),
	IN_MOVE_RIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_WEAPON1 = (1 << 20),
	IN_WEAPON2 = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_GRENADE1 = (1 << 23),
	IN_GRENADE2 = (1 << 24),
	IN_LOOKSPIN = (1 << 25),
};

//for paint hook taken from the leaked sdk
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/public/ienginevgui.h
enum class ePaintMode
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_UIGAMEPANELS = (1 << 1),
};

//player flag states
//https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/const.h#L110
//NOTE: this has some weird #if defines, if these don't work for whatever reason, check the link for more info
enum eFlagStates
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3), //the only difference is FL_ANIMDUCKING goes here /shrug, idk which part the game takes lol
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8),
	FL_INWATER = (1 << 9),
	FL_FLY = (1 << 10),
	FL_SWIM = (1 << 11),
	FL_CONVEYOR = (1 << 12),
	FL_NPC = (1 << 13),
	FL_GODMODE = (1 << 14),
	FL_NOTARGET = (1 << 15),
	FL_AIMTARGET = (1 << 16),
	FL_PARTIALGROUND = (1 << 17),
	FL_STATICPROP = (1 << 18),
	FL_GRAPHED = (1 << 19),
	FL_GRENADE = (1 << 20),
	FL_STEPMOVEMENT = (1 << 21),
	FL_DONTTOUCH = (1 << 22),
	FL_BASEVELOCITY = (1 << 23),
	FL_WORLDBRUSH = (1 << 24),
	FL_OBJECT = (1 << 25),
	FL_KILLME = (1 << 26),
	FL_ONFIRE = (1 << 27),
	FL_DISSOLVING = (1 << 28),
	FL_TRANSRAGDOLL = (1 << 29),
	FL_UNBLOCKABLE_BY_PLAYER = (1 << 30),
};

//player life states
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/public/const.h#L254
enum eLifeStates
{
	LIFE_ALIVE = 0,
	LIFE_DYING = 0,
	LIFE_DEAD = 0,
	LIFE_RESPAWNABLE = 0,
	LIFE_DISCARDBODY = 0,
};

enum eMoveType
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC = 1,
	MOVETYPE_WALK = 2,
	MOVETYPE_STEP = 3,
	MOVETYPE_FLY = 4,
	MOVETYPE_FLYGRAVITY = 5,
	MOVETYPE_VPHYSICS = 6,
	MOVETYPE_PUSH = 7,
	MOVETYPE_NOCLIP = 8,
	MOVETYPE_LADDER = 9,
	MOVETYPE_OBSERVER = 10,
	MOVETYPE_CUSTOM = 11,
};