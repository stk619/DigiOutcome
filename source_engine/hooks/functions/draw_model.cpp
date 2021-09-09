#include "../hooks.h"
//used in: menu variable reading
#include "../../../main/menu/menu.h"

void __fastcall nHooks::draw_model(void* ecx, void* edx, void* ptrResults, modelrenderinfo_t& sModelInfo, matrix3x4_t* ptrBoneToWorld, float* flFlexWeights, float* flFlexDelayedRates, vector3d_t<float>& vecOrigin, int iFlags)
{
	static void(__fastcall * oDrawModel)(void*, void*, void*, modelrenderinfo_t&, matrix3x4_t *, float*, float*, vector3d_t<float>&, int) = sDetours.get_original<decltype(&nHooks::draw_model)>(xorstr_("DrawModel"));

	basecsplayer_t* ptrLocalPlayer = reinterpret_cast<basecsplayer_t*>(nInterfaces::ptrEntityList->get_client_entity(nInterfaces::ptrEngine->get_local_player()));
	if (ptrLocalPlayer == nullptr)
		return oDrawModel(ecx, edx, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);

	if (!sModelInfo.ptrRenderable)
		return oDrawModel(ecx, edx, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);

	//we get the current entity through IClientRenderable, i'm not using the class here but essentially how it works
	//is that IClientRenderable is located 4 bytes from the start of the entity class (as seen by how i get it in entities.h)
	//sModelInfo.ptrRenderable gives the pointer to IClientRenderable and from there we can subtract the 4 bytes to get the
	//pointer to the entity we're currently indexing
	basecsplayer_t* ptrCurrentEntity = reinterpret_cast<basecsplayer_t*>(sModelInfo.ptrRenderable - 0x4);
	if (ptrCurrentEntity == nullptr)
		return oDrawModel(ecx, edx, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);

	if (ptrCurrentEntity == ptrLocalPlayer || ptrCurrentEntity->get_team() == ptrLocalPlayer->get_team())
		return oDrawModel(ecx, edx, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);

	//skip the flags that override glow
	if (iFlags & (STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS))
		return oDrawModel(ecx, edx, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);

	//only run our chams on players/
	if (nMenu::ptrVisibleChamsCheckbox->GetState() || nMenu::ptrInvisChamsCheckbox->GetState())
	{
		if (ptrCurrentEntity->isplayer() && ptrCurrentEntity->isalive())
		{
			//having the second perameter be nullptr, this makes it so the game will figure out what material type it is automatically
			static IMaterial* ptrMaterial = nInterfaces::ptrMaterialSystem->find_material(xorstr_("debug/debugambientcube"), nullptr);
			static float flVisibleChamColour[3]{};
			flVisibleChamColour[0] = 191.f / 255.f;
			flVisibleChamColour[1] = 255.f / 255.f;
			flVisibleChamColour[2] = 0.f / 255.f;
			if (nMenu::ptrInvisChamsCheckbox->GetState())
			{
				static float flInvisibleChamColour[3]{};
				flInvisibleChamColour[0] = 0.f / 255.f;
				flInvisibleChamColour[1] = 150.f / 255.f;
				flInvisibleChamColour[2] = 255.f / 255.f;
				ptrMaterial->set_material_var_flags(1 << 15, true); //forces ignorez plane, which renders through walls
				nInterfaces::ptrStudioRender->set_colour_modulation(flInvisibleChamColour);
				nInterfaces::ptrStudioRender->forced_material_override(ptrMaterial);
				oDrawModel(ecx, 0, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);
			}
			ptrMaterial->set_material_var_flags(1 << 15, false); //forces ignorez plane, which renders through walls
			nInterfaces::ptrStudioRender->set_colour_modulation(flVisibleChamColour);
			nInterfaces::ptrStudioRender->forced_material_override(ptrMaterial);
			oDrawModel(ecx, edx, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);
			nInterfaces::ptrStudioRender->forced_material_override(nullptr);
			return;
		}
	}
	
	//if all else fails, just call original
	return oDrawModel(ecx, edx, ptrResults, sModelInfo, ptrBoneToWorld, flFlexWeights, flFlexDelayedRates, vecOrigin, iFlags);
}