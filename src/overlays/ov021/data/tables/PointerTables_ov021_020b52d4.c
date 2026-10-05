#include "nitro/types.h"

extern void func_ov021_020b133c(void); /* ScriptOp_GetPlayerHorizontalOffset */
extern void func_ov021_020b12d8(void); /* ScriptOp_GetPlayerHorizontalDrift */
extern void func_ov021_020b12b8(void);
extern void func_ov021_020b1290(void); /* ScriptOp_GetObjectVectorMagnitude */
extern void func_ov021_020b1260(void); /* ScriptOp_IsStageEntryKind24 */
extern void func_ov021_020b1250(void);
extern void func_ov021_020b122c(void); /* ScriptOp_GetPlayerLockFlag */
extern void func_ov021_020b1194(void); /* ScriptCmd_GetTargetFacingDot */
extern void func_ov021_020b116c(void); /* ScriptOp_GetObjectVerticalOffset */
extern void func_ov021_020b1140(void); /* ScriptOp_IsObjectCounterNonpositive */
extern void func_ov021_020b1134(void);
extern void func_ov021_020b1128(void);
extern void func_ov021_020b111c(void);
extern void func_ov021_020b10fc(void); /* ReadContextFlagBit8 */
extern void func_ov021_020b10dc(void); /* ScriptOp_GetObjectFixedField */
extern void func_ov021_020b10c0(void);
extern void func_ov021_020b10b0(void);
extern void func_ov021_020b1090(void); /* ReadContextFlagBit9 */
extern void func_ov021_020b1064(void); /* ScriptOp_GetPlayerStateBit0 */
extern void func_ov021_020b1014(void); /* ScriptOp_GetAttachPointScale */
extern void func_ov021_020b0ff0(void); /* ScriptOp_GetOwnerIntegerField */
extern void func_ov021_020b0fd4(void);
extern void func_ov021_020b0f94(void); /* ScriptOp_GetPlayerAngleDegrees */
extern void func_ov021_020b0f0c(void); /* ScriptCmd_CheckTargetLineOfSight */
extern void func_ov021_020b0edc(void);
extern void func_ov021_020b0e80(void); /* SampleGridCellValue */
extern void func_ov021_020b0e40(void); /* ScriptOp_GetObjectTypeId */
extern void func_ov021_020b0e24(void);
extern void func_ov021_020b0df0(void);
extern void func_ov021_020b0dd4(void);
extern void func_ov021_020b0d8c(void);
extern void func_ov021_020b0d44(void); /* ScriptOp_FindNearestFreeSlot */
extern void func_ov021_020b0cfc(void);
extern void func_ov021_020b0cd8(void); /* ScriptOp_GetActiveObjectValue */
extern void func_ov021_020b0cb8(void); /* ReadContextFlagBit10 */
extern void func_ov021_020b0c9c(void); /* ScriptOp_GetFirstSharedValue */
extern void func_ov021_020b0c80(void); /* ScriptOp_GetSecondSharedValue */
extern void func_ov021_020b0c60(void); /* ReadContextFlagBit11 */
extern void func_ov021_020b0c08(void); /* ScriptOp_IsPlayerAnimDone */
extern void func_ov021_020b0bec(void);
extern void func_ov021_020b0b8c(void); /* ScriptOp_GetEventActorValue */
extern void func_ov021_020b0b74(void);
extern void func_ov021_020b0b40(void); /* ScriptOp_GetEventFlagPairBits */
extern void func_ov021_020b0b20(void); /* ReadContextFlagBit13 */
extern void func_ov021_020b0b0c(void);
extern void func_ov021_020b0af0(void);
extern void func_ov021_020b0ad4(void);
extern void func_ov021_020b0ab0(void); /* ScriptOp_GetPlayerHiddenFlag */
extern void func_ov021_020b0a68(void);
extern void func_ov021_020b2000(void); /* SetScriptContextVector */
extern void func_ov021_020b1fb0(void); /* AddScriptContextVector */
extern void func_ov021_020b1f98(void); /* SubmitActorRender */
extern void func_ov021_020b1f54(void);
extern void PickSpawnPointNearPlayer(void); /* PickSpawnPointNearPlayer */
extern void func_ov021_020b1e04(void); /* ScriptOp_GetObjectPosition */
extern void func_ov021_020b1d98(void); /* ScriptOp_DropToGround */
extern void func_ov021_020b1d34(void); /* ScriptOp_MoveAlongPlayerFacing */
extern void func_ov021_020b1ccc(void); /* ScriptOp_MoveAgainstPlayerFacing */
extern void func_ov021_020b1c70(void); /* ScriptOp_StepTowardPlayer */
extern void func_ov021_020b1c50(void); /* ScriptOp_GetCameraTarget */
extern void func_ov021_020b1c04(void);
extern void func_ov021_020b1bd4(void); /* ScriptOp_GetObjectPositionById */
extern void func_ov021_020b1bb4(void); /* ScriptOp_GetStageAnchorB */
extern void func_ov021_020b1b94(void); /* ScriptOp_GetStageAnchorA */
extern void func_ov021_020b1b74(void); /* LoadSavedPosition */
extern void func_ov021_020b1b1c(void); /* ScriptOp_GetGridCellPosition */
extern void func_ov021_020b1af4(void);
extern void func_ov021_020b1a9c(void);
extern void func_ov021_020b1a50(void); /* ScriptOp_GetSlotPosition */
extern void func_ov021_020b19f0(void); /* ScriptOp_ProjectObjectMovement */
extern void func_ov021_020b19d0(void); /* LoadStageEntryPosition */
extern void ScriptOp_PlaceAroundPlayer(void); /* ScriptOp_PlaceAroundPlayer */
extern void ScriptOp_PlaceNearPlayerOnGround(void); /* ScriptOp_PlaceNearPlayerOnGround */
extern void func_ov021_020b170c(void); /* ScriptOp_GetMotionTarget */
extern void func_ov021_020b1688(void); /* ScriptCmd_PushRandomSpherical */
extern void func_ov021_020b1608(void); /* ScriptCmd_PushRandomHorizontal */
extern void func_ov021_020b15e0(void); /* ScriptOp_GetMotionAnchor */
extern void func_ov021_020b1394(void); /* ScriptOp_FindNearbyOpenCell */

void (*gScriptQueryHandlers[173])(void) = {
    NULL,
    func_ov021_020b133c, /* ScriptOp_GetPlayerHorizontalOffset */
    func_ov021_020b12d8, /* ScriptOp_GetPlayerHorizontalDrift */
    func_ov021_020b12b8,
    func_ov021_020b1290, /* ScriptOp_GetObjectVectorMagnitude */
    func_ov021_020b1260, /* ScriptOp_IsStageEntryKind24 */
    func_ov021_020b1250,
    func_ov021_020b122c, /* ScriptOp_GetPlayerLockFlag */
    func_ov021_020b1194, /* ScriptCmd_GetTargetFacingDot */
    func_ov021_020b116c, /* ScriptOp_GetObjectVerticalOffset */
    func_ov021_020b1140, /* ScriptOp_IsObjectCounterNonpositive */
    NULL,
    NULL,
    func_ov021_020b1134,
    func_ov021_020b1128,
    func_ov021_020b111c,
    NULL,
    func_ov021_020b10fc, /* ReadContextFlagBit8 */
    NULL,
    func_ov021_020b10dc, /* ScriptOp_GetObjectFixedField */
    NULL,
    NULL,
    func_ov021_020b10c0,
    func_ov021_020b10b0,
    func_ov021_020b1090, /* ReadContextFlagBit9 */
    func_ov021_020b1064, /* ScriptOp_GetPlayerStateBit0 */
    NULL,
    NULL,
    func_ov021_020b1014, /* ScriptOp_GetAttachPointScale */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0ff0, /* ScriptOp_GetOwnerIntegerField */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0fd4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0f94, /* ScriptOp_GetPlayerAngleDegrees */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0f0c, /* ScriptCmd_CheckTargetLineOfSight */
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0edc,
    func_ov021_020b0e80, /* SampleGridCellValue */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0e40, /* ScriptOp_GetObjectTypeId */
    NULL,
    NULL,
    NULL,
    func_ov021_020b0e24,
    func_ov021_020b0df0,
    NULL,
    func_ov021_020b0dd4,
    NULL,
    func_ov021_020b0d8c,
    func_ov021_020b0d44, /* ScriptOp_FindNearestFreeSlot */
    func_ov021_020b0cfc,
    NULL,
    NULL,
    func_ov021_020b0cd8, /* ScriptOp_GetActiveObjectValue */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0cb8, /* ReadContextFlagBit10 */
    func_ov021_020b0c9c, /* ScriptOp_GetFirstSharedValue */
    func_ov021_020b0c80, /* ScriptOp_GetSecondSharedValue */
    NULL,
    func_ov021_020b0c60, /* ReadContextFlagBit11 */
    func_ov021_020b0c08, /* ScriptOp_IsPlayerAnimDone */
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0bec,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0b8c, /* ScriptOp_GetEventActorValue */
    NULL,
    func_ov021_020b0b74,
    NULL,
    func_ov021_020b0b40, /* ScriptOp_GetEventFlagPairBits */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0b20, /* ReadContextFlagBit13 */
    func_ov021_020b0b0c,
    NULL,
    NULL,
    func_ov021_020b0af0,
    func_ov021_020b0ad4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0ab0, /* ScriptOp_GetPlayerHiddenFlag */
    func_ov021_020b0a68,
    NULL,
    NULL,
};

void (*gScriptVectorHandlers[33])(void) = {
    NULL,
    func_ov021_020b2000, /* SetScriptContextVector */
    func_ov021_020b1fb0, /* AddScriptContextVector */
    func_ov021_020b1f98, /* SubmitActorRender */
    func_ov021_020b1f54,
    PickSpawnPointNearPlayer, /* PickSpawnPointNearPlayer */
    func_ov021_020b1e04, /* ScriptOp_GetObjectPosition */
    func_ov021_020b1d98, /* ScriptOp_DropToGround */
    func_ov021_020b1d34, /* ScriptOp_MoveAlongPlayerFacing */
    func_ov021_020b1ccc, /* ScriptOp_MoveAgainstPlayerFacing */
    func_ov021_020b1c70, /* ScriptOp_StepTowardPlayer */
    func_ov021_020b1c50, /* ScriptOp_GetCameraTarget */
    func_ov021_020b1c04,
    func_ov021_020b1bd4, /* ScriptOp_GetObjectPositionById */
    func_ov021_020b1bb4, /* ScriptOp_GetStageAnchorB */
    func_ov021_020b1b94, /* ScriptOp_GetStageAnchorA */
    func_ov021_020b1b74, /* LoadSavedPosition */
    NULL,
    NULL,
    NULL,
    func_ov021_020b1b1c, /* ScriptOp_GetGridCellPosition */
    func_ov021_020b1af4,
    func_ov021_020b1a9c,
    func_ov021_020b1a50, /* ScriptOp_GetSlotPosition */
    func_ov021_020b19f0, /* ScriptOp_ProjectObjectMovement */
    func_ov021_020b19d0, /* LoadStageEntryPosition */
    ScriptOp_PlaceAroundPlayer, /* ScriptOp_PlaceAroundPlayer */
    ScriptOp_PlaceNearPlayerOnGround, /* ScriptOp_PlaceNearPlayerOnGround */
    func_ov021_020b170c, /* ScriptOp_GetMotionTarget */
    func_ov021_020b1688, /* ScriptCmd_PushRandomSpherical */
    func_ov021_020b1608, /* ScriptCmd_PushRandomHorizontal */
    func_ov021_020b15e0, /* ScriptOp_GetMotionAnchor */
    func_ov021_020b1394, /* ScriptOp_FindNearbyOpenCell */
};
