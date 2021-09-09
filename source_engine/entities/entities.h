#pragma once
#include "../../common_includes.h"
//used in: bounding box calculatios, debug_overlay
#include "../interfaces/interfaces.h"
//used in: weapon data
#include "../definitions/cs_weapon_data.h"
//used in: animation overlays
#include "../definitions/animationlayers.h"
//used in: prop getting
#include "../../other/netvars/netvars.h"
//used in: virtual func grabbing
#include "../../other/utilities/utilities.h"

struct boundingbox_t
{
	boundingbox_t() = default;
	boundingbox_t(float flX, float flY, float flWidth, float flHeight)
	{
		this->flX = flX;
		this->flY = flY;
		this->flWidth = flWidth;
		this->flHeight = flHeight;
	}

	float flX;
	float flY;
	float flWidth;
	float flHeight;
};

//base entity, namely DT_BaseEntity->props
struct baseentity_t
{
public:
	//get entity renderable
	void* renderable()
	{
		return reinterpret_cast<void*>(reinterpret_cast<std::size_t>(this) + 0x4);
	}

	void* get_model()
	{
		return nUtilities::vfunc<void* (__thiscall*)(void*)>(renderable(), 8)(renderable());
	}

	//get entity networkable
	void* networkable()
	{
		return reinterpret_cast<void*>(reinterpret_cast<std::size_t>(this) + 0x8);
	}

	clientclass_t* get_client_class()
	{
		return nUtilities::vfunc<clientclass_t*(__thiscall*)(void*)>(networkable(), 2)(networkable());
	}

	bool isdormant()
	{
		return nUtilities::vfunc<bool(__thiscall*)(void*)>(networkable(), 9)(networkable());
	}

	int index()
	{
		return nUtilities::vfunc<int(__thiscall*)(void*)>(networkable(), 10)(networkable());
	}

	//get player collidable functions, mins, maxs
	void* collidable()
	{
		return nUtilities::vfunc<void* (__thiscall*)(void*)>(this, 3)(this);
	}

	vector3d_t<float>& get_mins()
	{
		return nUtilities::vfunc<vector3d_t<float>&(__thiscall*)(void*)>(collidable(), 1)(collidable());
	}

	vector3d_t<float>& get_maxs()
	{
		return nUtilities::vfunc<vector3d_t<float>&(__thiscall*)(void*)>(collidable(), 2)(collidable());
	}

	//better than using the vfunc, but if i need to for whatever reason
	//baseentity, idx 155, no parameters
	//bool isalive()
	//{
		//should be using lifestates
		//return get_lifestate() == static_cast<std::byte>(LIFE_ALIVE);
	//}
	//lifestate stopped working for me?
	bool isalive()
	{
		return nUtilities::vfunc<bool(__thiscall*)(void*)>(this, 155)(this);
	}

	bool isplayer()
	{
		return nUtilities::vfunc<bool(__thiscall*)(void*)>(this, 157)(this);
	}

	int get_movetype()
	{
		//hardcoded offset: 0x0 - int - can't seem to find an actual offset
		//static std::size_t uiMovetypeOffset = nNetvarManager::umOffsets[sHash.hash("DT_BaseEntity->movetype")];
		//return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiMovetypeOffset);
		//https://github.com/frk1/hazedumper/blob/master/csgo.cs#L15
		//valve including the movetype netvar, but having it not work as it should :D smh
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + 0x25C);
	}

	float get_spawn_time()
	{
		return *reinterpret_cast<float*>(reinterpret_cast<std::size_t>(this) + 0x20);
	}

	unsigned int& get_team()
	{
		//hardcoded offset: 0xf4 - unsigned int
		static std::size_t uiTeamOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseEntity->m_iTeamNum"))];
		return *reinterpret_cast<unsigned int*>(reinterpret_cast<std::size_t>(this) + uiTeamOffset);
	}

	vector3d_t<float>& get_origin()
	{
		//hardcoded offset: 0xac - vector3d_t<float>
		static std::size_t ulOriginOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseEntity->m_vecOrigin"))];
		return *reinterpret_cast<vector3d_t<float>*>(reinterpret_cast<std::size_t>(this) + ulOriginOffset);
	}

	matrix3x4_t& get_coordinate_frame()
	{
		//hardcoded offset: unused
		static std::size_t uiCoordinateFrameOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseEntity->m_CollisionGroup"))] - 0x30;
		return *reinterpret_cast<matrix3x4_t*>(reinterpret_cast<std::size_t>(this) + uiCoordinateFrameOffset);
	}
	
	int& get_hostage_state()
	{
		//hardcoded offset: 0x2f34 - int
		static std::size_t uiHostageStateOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CHostage->m_nHostageState"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiHostageStateOffset);
	}

	std::size_t& get_grenade_handle()
	{
		//hardcoded offset: 0x29a0 - std::size_t
		static std::size_t uiGrenadeThrowerOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseGrenade->m_hThrower"))];
		return *reinterpret_cast<std::size_t*>(reinterpret_cast<std::size_t>(this) + uiGrenadeThrowerOffset);
	}

	int& get_smoke_grenade_effect_tick()
	{
		//hardcoded offset: 0x2a10 - int
		static std::size_t uiSmokeTickBeginOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_SmokeGrenadeProjectile->m_nSmokeEffectTickBegin"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiSmokeTickBeginOffset);
	}

	bool& get_smoke_effect_began()
	{
		//hardcoded offset: 0x2a14 - bool
		static std::size_t uiSmokeEffectBeganOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_SmokeGrenadeProjectile->m_bDidSmokeEffect"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiSmokeEffectBeganOffset);
	}

	int& get_explode_effect_begin()
	{
		//hardcoded offset: 0x29e4 - int
		static std::size_t uiExplodeEffectTickBeginOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseCSGrenadeProjectile->m_nExplodeEffectTickBegin"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiExplodeEffectTickBeginOffset);
	}

	int& get_grenade_bounces()
	{
		//hardcoded offset: 0x29dc - int
		static std::size_t uiGrenadeBouncesOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseCSGrenadeProjectile->m_nBounces"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiGrenadeBouncesOffset);
	}

	bool& get_incindiary_grenade()
	{
		//hardcoded offset: 0x2a10 - bool
		static std::size_t uiIsIncindiaryGrenade = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_MolotovProjectile->m_bIsIncGrenade"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiIsIncindiaryGrenade);
	}

	float& get_simulation_time()
	{
		//hardcoded offset: 0x268 - float
		static std::size_t uiSimulationTimeOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseEntity->m_flSimulationTime"))];
		return *reinterpret_cast<float*>(reinterpret_cast<std::size_t>(this) + uiSimulationTimeOffset);
	}

	//entity bounding box calculations, this is taken directly off of unknowncheats, not proud of it, but w/e
	//https://www.unknowncheats.me/forum/counterstrike-global-offensive/124388-bounding-esp-boxes.html
	boundingbox_t get_bounding_box()
	{
		//model collidable mins and maxs; model "range"
		vector3d_t<float> vecMins = this->get_mins();
		vector3d_t<float> vecMaxs = this->get_maxs();

		//points list for where each corner of the box should be, this also works with 3d boxes afaik
		vector3d_t<float> vecPointsList[8] = {
			vector3d_t<float>(vecMins.tX, vecMins.tY, vecMins.tZ),
			vector3d_t<float>(vecMins.tX, vecMaxs.tY, vecMins.tZ),
			vector3d_t<float>(vecMaxs.tX, vecMaxs.tY, vecMins.tZ),
			vector3d_t<float>(vecMaxs.tX, vecMins.tY, vecMins.tZ),
			vector3d_t<float>(vecMaxs.tX, vecMaxs.tY, vecMaxs.tZ),
			vector3d_t<float>(vecMins.tX, vecMaxs.tY, vecMaxs.tZ),
			vector3d_t<float>(vecMins.tX, vecMins.tY, vecMaxs.tZ),
			vector3d_t<float>(vecMaxs.tX, vecMins.tY, vecMaxs.tZ)
		};

		//haha math
		matrix3x4_t& sCoordinateFrame = this->get_coordinate_frame();
		vector3d_t<float> vecTransformedPoints[8]{};
		vector3d_t<float> vecScreenPoints[8]{};
		for (int iIndex = 0; iIndex < 8; ++iIndex)
		{
			nMath::vector_transform(vecPointsList[iIndex], sCoordinateFrame, vecTransformedPoints[iIndex]);
			if (!nInterfaces::ptrDebugOverlay->world_to_screen(vecTransformedPoints[iIndex], vecScreenPoints[iIndex]))
				return boundingbox_t(0, 0, 0, 0);
		}

		//asign side positions
		float flLeft = vecScreenPoints[0].tX;
		float flBottom = vecScreenPoints[0].tY;
		float flRight = vecScreenPoints[0].tX;
		float flTop = vecScreenPoints[0].tY;

		//clamp values, tried using std::clamp, but that doesn't seem to function as though i wanted it too
		for (int iIndex = 1; iIndex < 8; ++iIndex)
		{
			if (flLeft > vecScreenPoints[iIndex].tX)
				flLeft = vecScreenPoints[iIndex].tX;
			if (flBottom < vecScreenPoints[iIndex].tY)
				flBottom = vecScreenPoints[iIndex].tY;
			if (flRight < vecScreenPoints[iIndex].tX)
				flRight = vecScreenPoints[iIndex].tX;
			if (flTop > vecScreenPoints[iIndex].tY)
				flTop = vecScreenPoints[iIndex].tY;
		}

		//temp, return val
		boundingbox_t sBoundingBox{};
		sBoundingBox.flX = flLeft;
		sBoundingBox.flY = flTop;
		sBoundingBox.flWidth = flRight - flLeft;
		sBoundingBox.flHeight = flBottom - flTop;

		return sBoundingBox;
	}

	animationlayer_t* get_animation_overlays()
	{
		return *reinterpret_cast<animationlayer_t**>(reinterpret_cast<std::size_t>(this) + 0x2980);
	}

	int get_sequence_activity(int iSequence)
	{
		//this needs to be studiohdr_t* but right now i don't need the struct
		void* ptrStudioModel = nInterfaces::ptrModelInfo->get_studio_model(this->get_model());

		static int(__fastcall * sequence_acitvity)(void*, void*, int) = reinterpret_cast<int(__fastcall*)(void*, void*, int)>(nUtilities::find_signature(xorstr_("client.dll"), xorstr_("55 8B EC 53 8B 5D 08 56 8B F1 83")));
		return sequence_acitvity(this, ptrStudioModel, iSequence);
	}

	void set_abs_origin(const vector3d_t<float>& vecOrigin)
	{
		static void(__thiscall * set_origin)(void*, const vector3d_t<float>&) = reinterpret_cast<void(__thiscall*)(void*, const vector3d_t<float>&)>(nUtilities::find_signature(xorstr_("client.dll"), xorstr_("55 8B EC 83 E4 F8 51 53 56 57 8B F1")));
		return set_origin(this, vecOrigin);
	}
};

//base combat character, namely DT_BaseCombatCharacter->props
struct basecombatcharacter_t : baseentity_t
{
public:
	csweapondata_t* get_weapon_data()
	{
		return nUtilities::vfunc<csweapondata_t* (__thiscall*)(void*)>(this, 460)(this);
	}

	std::size_t& get_active_weapon()
	{
		//hardcoded offset: 0x2ef8 - std::size_t
		static std::size_t uiActiveWeaponOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseCombatCharacter->m_hActiveWeapon"))];
		return *reinterpret_cast<std::size_t*>(reinterpret_cast<std::size_t>(this) + uiActiveWeaponOffset);
	}

	int& get_ammo()
	{
		//hardcoded offset: 0x3264 - int
		static std::size_t uiAmmoOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseCombatWeapon->m_iClip1"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiAmmoOffset);
	}

	short& get_item_definition_index() //unused
	{
		//hardcoded offset: 0x2faa - short
		static std::size_t uiItemDefinitionIndexOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BaseAttributableItem->m_iItemDefinitionIndex"))];
		return *reinterpret_cast<short*>(reinterpret_cast<std::size_t>(this) + uiItemDefinitionIndexOffset);
	}

	bool& get_bomb_arming()
	{
		//hardcoded offset: 0x33f0 - bool
		static std::size_t uiBombArmingOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_WeaponC4->m_bStartedArming"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiBombArmingOffset);
	}
	
	bool& get_bomb_placed_animation()
	{
		//hardcoded offset: 0x33f8 - bool
		static std::size_t uiBombPlacedAnimationOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_WeaponC4->m_bBombPlacedAnimation"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiBombPlacedAnimationOffset);
	}
};

//base player, namley DT_BasePlayer->props
struct baseplayer_t : basecombatcharacter_t
{
public:
	int& get_flags()
	{
		//hardcoded offset: 0x104 - int
		static std::size_t uiFlagsOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BasePlayer->m_fFlags"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiFlagsOffset);
	}

	int& get_health()
	{
		//hardcoded offset: 0x100 - int
		static std::size_t uiHealthOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BasePlayer->m_iHealth"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiHealthOffset);
	}

	std::byte& get_lifestate() //unused
	{
		//hardcoded offset: 0x25f - byte
		static std::size_t uiHealthOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BasePlayer->m_lifeState"))];
		return *reinterpret_cast<std::byte*>(reinterpret_cast<std::size_t>(this) + uiHealthOffset);
	}

	int& skybox_area()
	{
		//hardcoded offset: 0x3100 - int
		static std::size_t uiSkyboxArea = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BasePlayer->m_skybox3d.area"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiSkyboxArea);
	}

	const char& get_last_place_name()
	{
		//hardcoded offset: 0x35b4 - std::string_view
		static std::size_t uiLastPlaceNameOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_BasePlayer->m_szLastPlaceName"))];
		return *reinterpret_cast<const char*>(reinterpret_cast<std::size_t>(this) + uiLastPlaceNameOffset);
	}
};

//base animating, generally animating functions
struct baseanimating_t : baseplayer_t
{
public:

};

//base cs player, namely DT_CSPlayer->props
struct basecsplayer_t : baseanimating_t
{
public:
	bool& get_scoped()
	{
		//hardcoded offset: 0x3928 - bool
		static std::size_t uiScopedOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_bIsScoped"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiScopedOffset);
	}

	bool& get_helmet()
	{
		//hardcoded offset: 0xb370 - bool
		static std::size_t uiHasHelmetOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_bHasHelmet"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiHasHelmetOffset);
	}

	int& get_armour()
	{
		//hardcoded offset: 0xb37c - int
		static std::size_t uiArmourValueOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_ArmorValue"))];
		return *reinterpret_cast<int*>(reinterpret_cast<std::size_t>(this) + uiArmourValueOffset);
	}

	float& get_max_flash_alpha()
	{
		//hardcoded offset: 0xa41c - float
		static std::size_t uiMaxFlashAlphaOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_flFlashMaxAlpha"))];
		return *reinterpret_cast<float*>(reinterpret_cast<std::size_t>(this) + uiMaxFlashAlphaOffset);
	}

	float& get_flashbang_time_remaining()
	{
		//hardcoded offset: unused
		static std::size_t uiFlashbangTimeRemainingOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_flFlashDuration"))] - 0x10;
		return *reinterpret_cast<float*>(reinterpret_cast<std::size_t>(this) + uiFlashbangTimeRemainingOffset);
	}

	bool& get_defuser()
	{
		//hardcoded offset: 0xb38c - bool
		static std::size_t uiHasDefuserOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_bHasDefuser"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiHasDefuserOffset);
	}

	bool& get_player_defusing()
	{
		//hardcoded offset: 0x3930 - bool
		static std::size_t uiIsDefusingOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_bIsDefusing"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiIsDefusingOffset);
	}

	bool& get_grabbing_hostage()
	{
		//hardcoded offset: 0x3931 - bool
		static std::size_t uiGrabbingHostageOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_bIsGrabbingHostage"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiGrabbingHostageOffset);
	}

	bool& get_player_walking()
	{
		//hardcoded offset: 0x3929 - bool
		static std::size_t uiPlayerWalkingOffset = nNetvarManager::umOffsets[sHash.hash(xorstr_("DT_CSPlayer->m_bIsWalking"))];
		return *reinterpret_cast<bool*>(reinterpret_cast<std::size_t>(this) + uiPlayerWalkingOffset);
	}

	bool get_bomb_carrier()
	{
		static bool(__fastcall * bomb_carrier)(void*) = reinterpret_cast<bool(__fastcall*)(void*)>(nUtilities::find_signature(xorstr_("client.dll"), xorstr_("56 8B F1 85 F6 74 31 8B 06 8B 80 ? ? ? ? FF D0 84 C0 74 ?")));
		return bomb_carrier(this);
	}
};