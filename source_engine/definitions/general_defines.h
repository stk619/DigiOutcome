#pragma once

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

//for paint hook taken from the leaked source
//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/public/ienginevgui.h
enum class ePaintMode
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_UIGAMEPANELS = (1 << 1),
};

//player flag states
//https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/const.h#L110
//this has some weird #if defines, if these don't work for whatever reason, check the link for more info
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

//check sv_dump_class_info for the newest class id's if valve changes things
//this also includes their netvar names too
enum class eClassId
{
	CAI_BaseNPC = 0, //(DT_AI_BaseNPC) :12 387
	CAK47, //(DT_WeaponAK47) : 1 517
	CBaseAnimating, //(DT_BaseAnimating) : 25 102
	CBaseAnimatingOverlay, //(DT_BaseAnimatingOverlay) : 2 208
	CBaseAttributableItem, //(DT_BaseAttributableItem) : 8 280
	CBaseButton, //(DT_BaseButton) : 1 55
	CBaseCombatCharacter, //(DT_BaseCombatCharacter) : 9 376
	CBaseCombatWeapon, //(DT_BaseCombatWeapon) : 14 505
	CBaseCSGrenade, //(DT_BaseCSGrenade) : 7 521
	CBaseCSGrenadeProjectile, //(DT_BaseCSGrenadeProjectile) : 6 112
	CBaseDoor, //(DT_BaseDoor) : 2 56
	CBaseEntity, //(DT_BaseEntity) : 44 52
	CBaseFlex, //(DT_BaseFlex) : 4 306
	CBaseGrenade, //(DT_BaseGrenade) : 8 107
	CBaseParticleEntity, //(DT_BaseParticleEntity) : 1 52
	CBasePlayer, //(DT_BasePlayer) : 43 567
	CBasePropDoor, //(DT_BasePropDoor) : 7 83
	CBaseTeamObjectiveResource, //(DT_BaseTeamObjectiveResource) : 29 721
	CBaseTempEntity, //(DT_BaseTempEntity) : 0 0
	CBaseToggle, //(DT_BaseToggle) : 4 55
	CBaseTrigger, //(DT_BaseTrigger) : 3 57
	CBaseViewModel, //(DT_BaseViewModel) : 14 14
	CBaseVPhysicsTrigger, //(DT_BaseVPhysicsTrigger) : 1 52
	CBaseWeaponWorldModel, //(DT_BaseWeaponWorldModel) : 5 5
	CBeam, //(DT_Beam) : 24 42
	CBeamSpotlight, //(DT_BeamSpotlight) : 9 60
	CBoneFollower, //(DT_BoneFollower) : 3 54
	CBRC4Target, //(DT_BRC4Target) : 3 104
	CBreachCharge, //(DT_WeaponBreachCharge) : 1 515
	CBreachChargeProjectile, //(DT_BreachChargeProjectile) : 5 111
	CBreakableProp, //(DT_BreakableProp) : 3 104
	CBreakableSurface, //(DT_BreakableSurface) : 10 316
	CBumpMine, //(DT_WeaponBumpMine) : 1 515
	CBumpMineProjectile, //(DT_BumpMineProjectile) : 4 110
	CC4, //(DT_WeaponC4) : 6 520
	CCascadeLight, //(DT_CascadeLight) : 7 7
	CChicken, //(DT_CChicken) : 3 111
	CColorCorrection, //(DT_ColorCorrection) : 12 12
	CColorCorrectionVolume, //(DT_ColorCorrectionVolume) : 2 2
	CCSGameRulesProxy, //(DT_CSGameRulesProxy) : 2 1126
	CCSPlayer, //(DT_CSPlayer) : 125 1744
	CCSPlayerResource, //(DT_CSPlayerResource) : 56 3563
	CCSRagdoll, //(DT_CSRagdoll) : 13 13
	CCSTeam, //(DT_CSTeam) : 1 16
	CDangerZone, //(DT_DangerZone) : 8 59
	CDangerZoneController, //(DT_DangerZoneController) : 10 106
	CDEagle, //(DT_WeaponDEagle) : 1 517
	CDecoyGrenade, //(DT_DecoyGrenade) : 1 521
	CDecoyProjectile, //(DT_DecoyProjectile) : 1 112
	CDrone, //(DT_Drone) : 10 86
	CDronegun, //(DT_Dronegun) : 5 106
	CDynamicLight, //(DT_DynamicLight) : 8 59
	CDynamicProp, //(DT_DynamicProp) : 6 109
	CEconEntity, //(DT_EconEntity) : 8 484
	CEconWearable, //(DT_WearableItem) : 1 484
	CEmbers, //(DT_Embers) : 5 56
	CEntityDissolve, //(DT_EntityDissolve) : 11 62
	CEntityFlame, //(DT_EntityFlame) : 3 54
	CEntityFreezing, //(DT_EntityFreezing) : 5 105
	CEntityParticleTrail, //(DT_EntityParticleTrail) : 4 57
	CEnvAmbientLight, //(DT_EnvAmbientLight) : 2 6
	CEnvDetailController, //(DT_DetailController) : 2 2
	CEnvDOFController, //(DT_EnvDOFController) : 8 59
	CEnvGasCanister, //(DT_EnvGasCanister) : 29 120
	CEnvParticleScript, //(DT_EnvParticleScript) : 2 103
	CEnvProjectedTexture, //(DT_EnvProjectedTexture) : 22 73
	CEnvQuadraticBeam, //(DT_QuadraticBeam) : 5 56
	CEnvScreenEffect, //(DT_EnvScreenEffect) : 3 54
	CEnvScreenOverlay, //(DT_EnvScreenOverlay) : 8 57
	CEnvTonemapController, //(DT_EnvTonemapController) : 14 65
	CEnvWind, //(DT_EnvWind) : 1 12
	CFEPlayerDecal, //(DT_FEPlayerDecal) : 16 194
	CFireCrackerBlast, //(DT_FireCrackerBlast) : 1 310
	CFireSmoke, //(DT_FireSmoke) : 7 58
	CFireTrail, //(DT_FireTrail) : 3 54
	CFish, //(DT_CFish) : 8 8
	CFists, //(DT_WeaponFists) : 2 516
	CFlashbang, //(DT_Flashbang) : 1 521
	CFogController, //(DT_FogController) : 18 18
	CFootstepControl, //(DT_FootstepControl) : 3 59
	CFunc_Dust, //(DT_Func_Dust) : 13 20
	CFunc_LOD, //(DT_Func_LOD) : 3 54
	CFuncAreaPortalWindow, //(DT_FuncAreaPortalWindow) : 5 56
	CFuncBrush, //(DT_FuncBrush) : 1 52
	CFuncConveyor, //(DT_FuncConveyor) : 2 53
	CFuncLadder, //(DT_FuncLadder) : 5 56
	CFuncMonitor, //(DT_FuncMonitor) : 1 52
	CFuncMoveLinear, //(DT_FuncMoveLinear) : 3 57
	CFuncOccluder, //(DT_FuncOccluder) : 2 2
	CFuncReflectiveGlass, //(DT_FuncReflectiveGlass) : 1 52
	CFuncRotating, //(DT_FuncRotating) : 9 54
	CFuncSmokeVolume, //(DT_FuncSmokeVolume) : 12 63
	CFuncTrackTrain, //(DT_FuncTrackTrain) : 1 52
	CGameRulesProxy, //(DT_GameRulesProxy) : 0 0
	CGrassBurn, //(DT_GrassBurn) : 2 53
	CHandleTest, //(DT_HandleTest) : 3 54
	CHEGrenade, //(DT_HEGrenade) : 1 521
	CHostage, //(DT_CHostage) : 21 252
	CHostageCarriableProp, //(DT_HostageCarriableProp) : 1 102
	CIncendiaryGrenade, //(DT_IncendiaryGrenade) : 1 521
	CInferno, //(DT_Inferno) : 7 310
	CInfoLadderDismount, //(DT_InfoLadderDismount) : 1 52
	CInfoMapRegion, //(DT_InfoMapRegion) : 3 54
	CInfoOverlayAccessor, //(DT_InfoOverlayAccessor) : 2 2
	CItem_Healthshot, //(DT_Item_Healthshot) : 1 516
	CItemCash, //(DT_ItemCash) : 1 484
	CItemDogtags, //(DT_ItemDogtags) : 3 486
	CKnife, //(DT_WeaponKnife) : 1 515
	CKnifeGG, //(DT_WeaponKnifeGG) : 1 515
	CLightGlow, //(DT_LightGlow) : 12 12
	CMapVetoPickController, //(DT_MapVetoPickController) : 16 640
	CMaterialModifyControl, //(DT_MaterialModifyControl) : 13 64
	CMelee, //(DT_WeaponMelee) : 2 516
	CMolotovGrenade, //(DT_MolotovGrenade) : 1 521
	CMolotovProjectile, //(DT_MolotovProjectile) : 2 113
	CMovieDisplay, //(DT_MovieDisplay) : 12 63
	CParadropChopper, //(DT_ParadropChopper) : 9 100
	CParticleFire, //(DT_ParticleFire) : 2 2
	CParticlePerformanceMonitor, //(DT_ParticlePerformanceMonitor) : 3 54
	CParticleSystem, //(DT_ParticleSystem) : 15 145
	CPhysBox, //(DT_PhysBox) : 1 52
	CPhysBoxMultiplayer, //(DT_PhysBoxMultiplayer) : 3 54
	CPhysicsProp, //(DT_PhysicsProp) : 8 79
	CPhysicsPropMultiplayer, //(DT_PhysicsPropMultiplayer) : 5 83
	CPhysMagnet, //(DT_PhysMagnet) : 1 102
	CPhysPropAmmoBox, //(DT_PhysPropAmmoBox) : 1 83
	CPhysPropLootCrate, //(DT_PhysPropLootCrate) : 5 87
	CPhysPropRadarJammer, //(DT_PhysPropRadarJammer) : 1 83
	CPhysPropWeaponUpgrade, //(DT_PhysPropWeaponUpgrade) : 1 83
	CPlantedC4, //(DT_PlantedC4) : 9 110
	CPlasma, //(DT_Plasma) : 7 58
	CPlayerPing, //(DT_PlayerPing) : 6 57
	CPlayerResource, //(DT_PlayerResource) : 10 650
	CPointCamera, //(DT_PointCamera) : 10 61
	CPointCommentaryNode, //(DT_PointCommentaryNode) : 9 110
	CPointWorldText, //(DT_PointWorldText) : 4 55
	CPoseController, //(DT_PoseController) : 12 69
	CPostProcessController, //(DT_PostProcessController) : 3 64
	CPrecipitation, //(DT_Precipitation) : 2 53
	CPrecipitationBlocker, //(DT_PrecipitationBlocker) : 1 52
	CPredictedViewModel, //(DT_PredictedViewModel) : 1 14
	CProp_Hallucination, //(DT_Prop_Hallucination) : 4 105
	CPropCounter, //(DT_PropCounter) : 2 103
	CPropDoorRotating, //(DT_PropDoorRotating) : 1 83
	CPropJeep, //(DT_PropJeep) : 2 117
	CPropVehicleDriveable, //(DT_PropVehicleDriveable) : 15 116
	CRagdollManager, //(DT_RagdollManager) : 1 1
	CRagdollProp, //(DT_Ragdoll) : 8 107
	CRagdollPropAttached, //(DT_Ragdoll_Attached) : 5 111
	CRopeKeyframe, //(DT_RopeKeyframe) : 24 24
	CSCAR17, //(DT_WeaponSCAR17) : 1 517
	CSceneEntity, //(DT_SceneEntity) : 6 22
	CSensorGrenade, //(DT_SensorGrenade) : 1 521
	CSensorGrenadeProjectile, //(DT_SensorGrenadeProjectile) : 1 112
	CShadowControl, //(DT_ShadowControl) : 5 5
	CSlideshowDisplay, //(DT_SlideshowDisplay) : 9 75
	CSmokeGrenade, //(DT_SmokeGrenade) : 1 521
	CSmokeGrenadeProjectile, //(DT_SmokeGrenadeProjectile) : 3 114
	CSmokeStack, //(DT_SmokeStack) : 19 70
	CSnowball, //(DT_Snowball) : 1 521
	CSnowballPile, //(DT_SnowballPile) : 1 102
	CSnowballProjectile, //(DT_SnowballProjectile) : 1 112
	CSpatialEntity, //(DT_SpatialEntity) : 5 5
	CSpotlightEnd, //(DT_SpotlightEnd) : 3 54
	CSprite, //(DT_Sprite) : 12 63
	CSpriteOriented, //(DT_SpriteOriented) : 1 63
	CSpriteTrail, //(DT_SpriteTrail) : 9 71
	CStatueProp, //(DT_StatueProp) : 6 84
	CSteamJet, //(DT_SteamJet) : 12 63
	CSun, //(DT_Sun) : 10 10
	CSunlightShadowControl, //(DT_SunlightShadowControl) : 10 10
	CSurvivalSpawnChopper, //(DT_SurvivalSpawnChopper) : 8 99
	CTablet, //(DT_WeaponTablet) : 19 528
	CTeam, //(DT_Team) : 17 16
	CTeamplayRoundBasedRulesProxy, //(DT_TeamplayRoundBasedRulesProxy) : 2 106
	CTEArmorRicochet, //(DT_TEArmorRicochet) : 1 2
	CTEBaseBeam, //(DT_BaseBeam) : 15 15
	CTEBeamEntPoint, //(DT_TEBeamEntPoint) : 5 19
	CTEBeamEnts, //(DT_TEBeamEnts) : 3 17
	CTEBeamFollow, //(DT_TEBeamFollow) : 2 16
	CTEBeamLaser, //(DT_TEBeamLaser) : 3 17
	CTEBeamPoints, //(DT_TEBeamPoints) : 3 17
	CTEBeamRing, //(DT_TEBeamRing) : 3 17
	CTEBeamRingPoint, //(DT_TEBeamRingPoint) : 4 18
	CTEBeamSpline, //(DT_TEBeamSpline) : 3 2
	CTEBloodSprite, //(DT_TEBloodSprite) : 9 9
	CTEBloodStream, //(DT_TEBloodStream) : 7 9
	CTEBreakModel, //(DT_TEBreakModel) : 12 11
	CTEBSPDecal, //(DT_TEBSPDecal) : 4 3
	CTEBubbles, //(DT_TEBubbles) : 7 6
	CTEBubbleTrail, //(DT_TEBubbleTrail) : 7 6
	CTEClientProjectile, //(DT_TEClientProjectile) : 6 5
	CTEDecal, //(DT_TEDecal) : 6 5
	CTEDust, //(DT_TEDust) : 4 6
	CTEDynamicLight, //(DT_TEDynamicLight) : 9 8
	CTEEffectDispatch, //(DT_TEEffectDispatch) : 2 22
	CTEEnergySplash, //(DT_TEEnergySplash) : 3 3
	CTEExplosion, //(DT_TEExplosion) : 9 11
	CTEFireBullets, //(DT_TEFireBullets) : 12 12
	CTEFizz, //(DT_TEFizz) : 5 4
	CTEFootprintDecal, //(DT_TEFootprintDecal) : 6 5
	CTEFoundryHelpers, //(DT_TEFoundryHelpers) : 2 1
	CTEGaussExplosion, //(DT_TEGaussExplosion) : 3 5
	CTEGlowSprite, //(DT_TEGlowSprite) : 6 5
	CTEImpact, //(DT_TEImpact) : 4 3
	CTEKillPlayerAttachments, //(DT_TEKillPlayerAttachments) : 2 1
	CTELargeFunnel, //(DT_TELargeFunnel) : 3 5
	CTEMetalSparks, //(DT_TEMetalSparks) : 2 2
	CTEMuzzleFlash, //(DT_TEMuzzleFlash) : 5 4
	CTEParticleSystem, //(DT_TEParticleSystem) : 4 3
	CTEPhysicsProp, //(DT_TEPhysicsProp) : 11 10
	CTEPlantBomb, //(DT_TEPlantBomb) : 3 3
	CTEPlayerAnimEvent, //(DT_TEPlayerAnimEvent) : 3 3
	CTEPlayerDecal, //(DT_TEPlayerDecal) : 7 6
	CTEProjectedDecal, //(DT_TEProjectedDecal) : 5 4
	CTERadioIcon, //(DT_TERadioIcon) : 2 1
	CTEShatterSurface, //(DT_TEShatterSurface) : 15 14
	CTEShowLine, //(DT_TEShowLine) : 2 4
	CTesla, //(DT_Tesla) : 3 54
	CTESmoke, //(DT_TESmoke) : 5 4
	CTESparks, //(DT_TESparks) : 4 6
	CTESprite, //(DT_TESprite) : 5 4
	CTESpriteSpray, //(DT_TESpriteSpray) : 7 6
	CTest_ProxyToggle_Networkable, //(DT_ProxyToggle) : 2 53
	CTestTraceline, //(DT_TestTraceline) : 6 6
	CTEWorldDecal, //(DT_TEWorldDecal) : 3 2
	CTriggerPlayerMovement, //(DT_TriggerPlayerMovement) : 1 57
	CTriggerSoundOperator, //(DT_TriggerSoundOperator) : 2 58
	CVGuiScreen, //(DT_VGuiScreen) : 8 59
	CVoteController, //(DT_VoteController) : 6 61
	CWaterBullet, //(DT_WaterBullet) : 1 102
	CWaterLODControl, //(DT_WaterLODControl) : 2 2
	CWeaponAug, //(DT_WeaponAug) : 1 517
	CWeaponAWP, //(DT_WeaponAWP) : 1 517
	CWeaponBaseItem, //(DT_WeaponBaseItem) : 2 516
	CWeaponBizon, //(DT_WeaponBizon) : 1 517
	CWeaponCSBase, //(DT_WeaponCSBase) : 15 515
	CWeaponCSBaseGun, //(DT_WeaponCSBaseGun) : 3 517
	CWeaponCycler, //(DT_WeaponCycler) : 1 505
	CWeaponElite, //(DT_WeaponElite) : 1 517
	CWeaponFamas, //(DT_WeaponFamas) : 1 517
	CWeaponFiveSeven, //(DT_WeaponFiveSeven) : 1 517
	CWeaponG3SG1, //(DT_WeaponG3SG1) : 1 517
	CWeaponGalil, //(DT_WeaponGalil) : 1 517
	CWeaponGalilAR, //(DT_WeaponGalilAR) : 1 517
	CWeaponGlock, //(DT_WeaponGlock) : 1 517
	CWeaponHKP2000, //(DT_WeaponHKP2000) : 1 517
	CWeaponM249, //(DT_WeaponM249) : 1 517
	CWeaponM3, //(DT_WeaponM3) : 2 516
	CWeaponM4A1, //(DT_WeaponM4A1) : 1 517
	CWeaponMAC10, //(DT_WeaponMAC10) : 1 517
	CWeaponMag7, //(DT_WeaponMag7) : 1 517
	CWeaponMP5Navy, //(DT_WeaponMP5Navy) : 1 517
	CWeaponMP7, //(DT_WeaponMP7) : 1 517
	CWeaponMP9, //(DT_WeaponMP9) : 1 517
	CWeaponNegev, //(DT_WeaponNegev) : 1 517
	CWeaponNOVA, //(DT_WeaponNOVA) : 2 516
	CWeaponP228, //(DT_WeaponP228) : 1 517
	CWeaponP250, //(DT_WeaponP250) : 1 517
	CWeaponP90, //(DT_WeaponP90) : 1 517
	CWeaponSawedoff, //(DT_WeaponSawedoff) : 2 516
	CWeaponSCAR20, //(DT_WeaponSCAR20) : 1 517
	CWeaponScout, //(DT_WeaponScout) : 1 517
	CWeaponSG550, //(DT_WeaponSG550) : 1 517
	CWeaponSG552, //(DT_WeaponSG552) : 1 517
	CWeaponSG556, //(DT_WeaponSG556) : 1 517
	CWeaponShield, //(DT_WeaponShield) : 1 517
	CWeaponSSG08, //(DT_WeaponSSG08) : 1 517
	CWeaponTaser, //(DT_WeaponTaser) : 2 518
	CWeaponTec9, //(DT_WeaponTec9) : 1 517
	CWeaponTMP, //(DT_WeaponTMP) : 1 517
	CWeaponUMP45, //(DT_WeaponUMP45) : 1 517
	CWeaponUSP, //(DT_WeaponUSP) : 1 517
	CWeaponXM1014, //(DT_WeaponXM1014) : 2 516
	CWeaponZoneRepulsor, //(DT_WeaponZoneRepulsor) : 1 517
	CWorld, //(DT_WORLD) : 11 62
	CWorldVguiText, //(DT_WorldVguiText) : 7 58
	DustTrail, //(DT_DustTrail) : 14 65
	MovieExplosion, //(DT_MovieExplosion) : 1 52
	ParticleSmokeGrenade, //(DT_ParticleSmokeGrenade) : 7 58
	RocketTrail, //(DT_RocketTrail) : 16 67
	SmokeTrail, //(DT_SmokeTrail) : 16 67
	SporeExplosion, //(DT_SporeExplosion) : 8 59
	SporeTrail, //(DT_SporeTrail) : 8 59
};

//https://git.byr.ac.cn/Gaojianli/cstrike15_src/-/blob/master/game/shared/cstrike15/cs_weapon_parse.h
enum eWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_EQUIPMENT,
	WEAPONTYPE_STACKABLEITEM,
	WEAPONTYPE_UNKNOWN
};

//https://git.byr.ac.cn/Gaojianli/cstrike15_src/-/blob/master/game/client/glow_outline_effect.h#L23
//used to change the outline of the glow
enum eGlowRenderStyle
{
	GLOWRENDERSTYLE_DEFAULT = 0,
	GLOWRENDERSTYLE_RIMGLOW3D,
	GLOWRENDERSTYLE_EDGE_HIGHLIGHT,
	GLOWRENDERSTYLE_EDGE_HIGHLIGHT_PULSE,
	GLOWRENDERSTYLE_COUNT,
};

//https://git.byr.ac.cn/Gaojianli/cstrike15_src/-/blob/master/public/istudiorender.h#L100
enum eDrawModelFlags
{
	STUDIO_NONE = 0x00000000,
	STUDIO_RENDER = 0x00000001,
	STUDIO_VIEWXFORMATTACHMENTS = 0x00000002,
	STUDIO_DRAWTRANSLUCENTSUBMODELS = 0x00000004,
	STUDIO_TWOPASS = 0x00000008,
	STUDIO_STATIC_LIGHTING = 0x00000010,
	STUDIO_WIREFRAME = 0x00000020,
	STUDIO_ITEM_BLINK = 0x00000040,
	STUDIO_NOSHADOWS = 0x00000080,
	STUDIO_WIREFRAME_VCOLLIDE = 0x00000100,
	STUDIO_NOLIGHTING_OR_CUBEMAP = 0x00000200,
	STUDIO_SKIP_FLEXES = 0x00000400,
	STUDIO_DONOTMODIFYSTENCILSTATE = 0x00000800,
	STUDIO_SKIP_DECALS = 0x10000000,
	STUDIO_SHADOWTEXTURE = 0x20000000,
	STUDIO_SHADOWDEPTHTEXTURE = 0x40000000,
	STUDIO_TRANSPARENCY = 0x80000000
};