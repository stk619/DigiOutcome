#include "../hooks.h"
//used in: menu variables
#include "../../../main/menu/menu.h"

//https://git.byr.ac.cn/Gaojianli/cstrike15_src/-/blob/master/game/client/cstrike15/c_cs_player.cpp#L3315
//we hook the function and make it glow other players for us, that way we don't need to populate the glow struct or anything
//and we essentially make glow the lazy way

bool __cdecl nHooks::glow_effect_spectator(basecsplayer_t* ptrEntity, basecsplayer_t* ptrLocalPlayer, eGlowRenderStyle& sGlowRenderStyle, vector3d_t<float>& vecGlowColour, 
											float& flAlphaStart, float& flAlpha, float& flTimeStart, float& flTimeTarget, bool& bAnimate)
{
	static bool(__cdecl * oGlowEffectSpectator)(basecsplayer_t*, basecsplayer_t*, eGlowRenderStyle&, vector3d_t<float>&, float&, float&, float&, float&, bool&) = sDetours.get_original<decltype(&nHooks::glow_effect_spectator)>(xorstr_("GlowEffectSpectator"));

	if (!nMenu::ptrGlowCheckbox->GetState())
		return oGlowEffectSpectator(ptrEntity, ptrLocalPlayer, sGlowRenderStyle, vecGlowColour, flAlphaStart, flAlpha, flTimeStart, flTimeTarget, bAnimate);

	if (ptrEntity == ptrLocalPlayer || ptrEntity->get_team() == ptrLocalPlayer->get_team())
		return oGlowEffectSpectator(ptrEntity, ptrLocalPlayer, sGlowRenderStyle, vecGlowColour, flAlphaStart, flAlpha, flTimeStart, flTimeTarget, bAnimate);

	//render default glow as it's nice enough
	sGlowRenderStyle = GLOWRENDERSTYLE_DEFAULT;
	vecGlowColour = { 0.f / 255.f, 150.f / 255.f, 255.f / 255.f };
	flAlpha = 150.f / 255.f;

	return true; //oGlowEffectSpectator(ecx, edx, sGlowRenderStyle, vecGlowColour, flAlphaStart, flAlpha, flTimeStart, flTimeTarget, bAnimate);
}