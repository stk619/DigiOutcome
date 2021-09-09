#pragma once
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"
//used in: utl_vector definitions
#include "../../../other/utilities/tier1_utl.h"

struct sound_info 
{
	int m_guid;
	void* m_file_name;
	int	m_sound_source;
	int	m_channel;
	int	m_speaker_entity;
	float m_volume;
	float m_last_spatialized_volume;
	float m_radius;
	int	m_pitch;
	vector3d_t<float>* m_origin;
	vector3d_t<float>* m_direction;
	bool m_update_positions;
	bool m_is_sentence;
	bool m_dry_mix;
	bool m_speaker;
	bool m_from_server;
};

struct IEngineSounds
{
private:
	enum eIndices
	{
		GETALLACTIVESOUNDS = 19
	};

public:
	void get_all_active_sounds(utl_vector<sound_info>& vecSoundList)
	{
		return nUtilities::vfunc<void(__thiscall*)(IEngineSounds*, utl_vector<sound_info>&)>(this, GETALLACTIVESOUNDS)(this, vecSoundList);
	}
};