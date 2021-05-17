#include "../hooks.h"

//just forces viewmodel fov to be 100 instead of the usual 68 i believe
float __fastcall nHooks::viewmodel_fov(void* edx, void* ecx)
{
	return 75.0f;
}