#include "nitro/types.h"

extern void ScriptCmd_SetScreenSwap(void); /* ScriptCmd_SetScreenSwap */
extern void func_ov001_0208c764(void); /* DefaultStepDone */
extern void func_ov001_0208d5c8(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_ReleaseSceneActors(void); /* ScriptCmd_ReleaseSceneActors */
extern void ScriptOp_RunActorPass(void); /* ScriptOp_RunActorPass */
extern void func_ov001_0208d1ac(void); /* ScriptCmd_BeginBrightnessFade */
extern void ScriptCmd_UpdateScreenBrightnessFades(void); /* ScriptCmd_UpdateScreenBrightnessFades */
extern void func_ov001_0208d5c0(void); /* DefaultStepDone */
extern void func_ov001_0208d5c4(void); /* DefaultStepDone */
extern void func_ov001_0208c768(void); /* ScriptCmd_InitActorCollision */
extern void func_ov001_0208c810(void); /* ScriptCmd_PlaceActor */
extern void func_ov001_0208c8cc(void); /* ScriptCmd_DetachActorAnimation */
extern void ScriptCmd_PlayActorUnnamedMotion(void); /* ScriptCmd_PlayActorUnnamedMotion */
extern void func_ov001_0208c940(void); /* ScriptCmd_AttachActorToParent */
extern void Script_ApplyActorAnimationState(void); /* Script_ApplyActorAnimationState */
extern void func_ov001_0208e54c(void); /* ScriptCmd_AttachActorObject */
extern void ScriptCmd_ShowActor(void); /* ScriptCmd_ShowActor */
extern void ScriptCmd_HideActor(void); /* ScriptCmd_HideActor */
extern void func_ov001_0208cabc(void); /* ScriptCmd_SetActorProbeSphere */
extern void func_ov001_0208cb3c(void); /* updateActorTransitionParameterRampCommand */
extern void func_ov001_0208cbbc(void);
extern void func_ov001_0208ded8(void); /* Script_MakeActorTranslucentAndClearVerticalOffset */
extern void PlaceActorRelativeToActor(void); /* PlaceActorRelativeToActor */
extern void func_ov001_0208cbdc(void); /* Script_SetActorParameterFromInteger */
extern void ScriptCmd_PlaceActor_0208e114(void); /* ScriptCmd_PlaceActor */
extern void ScriptCmd_BindActorTarget(void); /* ScriptCmd_BindActorTarget */
extern void ScriptCmd_SetElemFieldIfFlagSet(void); /* ScriptCmd_SetElemFieldIfFlagSet */
extern void func_ov001_0208e4b4(void); /* ScriptCmd_SetActorPlaybackRate */
extern void ScriptCmd_SetActorFlagBit4(void); /* ScriptCmd_SetActorFlagBit4 */
extern void ScriptCmd_SetActorPrimarySlot(void); /* ScriptCmd_SetActorPrimarySlot */
extern void ScriptCmd_SetActorAlpha(void); /* ScriptCmd_SetActorAlpha */
extern void func_ov001_0208e430(void); /* ScriptCmd_UpdateActorAlphaFade */
extern void ScriptCmd_StartActorRotation(void); /* ScriptCmd_StartActorRotation */
extern void func_ov001_0208debc(void); /* DefaultStepDone */
extern void func_ov001_0208dd08(void); /* DefaultStepDone */
extern void func_ov001_0208cce4(void); /* ScriptCmd_PlayActorMotionOrBlend */
extern void func_ov001_0208cda8(void); /* ScriptCmd_StoreIfFree */
extern void ScriptCmd_TestActorSlotMaskBit(void); /* ScriptCmd_TestActorSlotMaskBit */
extern void func_ov001_0208d624(void); /* ScriptCmd_PlayActorMotion */
extern void func_ov001_0208df2c(void); /* Script_SetActorAnimationFrame */
extern void func_ov001_0208ceec(void); /* ScriptCmd_SetActorMoveTarget */
extern void ScriptCmd_WaitActorReady(void); /* ScriptCmd_WaitActorReady */
extern void ScriptCmd_SetActorHeadingTowardTarget(void); /* ScriptCmd_SetActorHeadingTowardTarget */
extern void ScriptCmd_SetActorHeadingDegrees(void); /* ScriptCmd_SetActorHeadingDegrees */
extern void func_ov001_0208d29c(void); /* ScriptCmd_StartChannelTransform */
extern void ScriptCmd_SetActorChannelState(void); /* ScriptCmd_SetActorChannelState */
extern void ScriptCmd_PlayActorChannel(void); /* ScriptCmd_PlayActorChannel */
extern void func_ov001_0208d574(void); /* thumbStep */
extern void func_ov001_0208d55c(void); /* FS_UnloadOverlayImage */
extern void func_ov001_0208d568(void); /* FS_UnloadOverlayImage */
extern void func_ov001_0208d430(void); /* ScriptCmd_SetCameraTarget */
extern void ScriptCmd_ActorTimerOrAnim(void); /* ScriptCmd_ActorTimerOrAnim */
extern void ScriptCmd_ClearActorTimers(void); /* ScriptCmd_ClearActorTimers */
extern void func_ov001_0208e4ac(void); /* DefaultStepDone */
extern void func_ov001_0208e4b0(void); /* DefaultStepDone */
extern void func_ov001_0208e4e4(void); /* ScriptCmd_PlaySoundAtActor */
extern void func_ov001_0208d6d8(void); /* ScriptCmd_ShowActorMessage */
extern void func_ov001_0208dc54(void);
extern void ScriptCmd_ResetAndSetElemField(void); /* ScriptCmd_ResetAndSetElemField */
extern void ScriptCmd_SetElemFieldAndDispatch(void); /* ScriptCmd_SetElemFieldAndDispatch */
extern void func_ov001_0208e5c4(void); /* ScriptCmd_SetEntityFlag */
extern void ScriptCmd_StartScreenOverlayFade(void); /* ScriptCmd_StartScreenOverlayFade */
extern void func_ov001_0208e638(void); /* ScriptCmd_UpdateScreenOverlayFade */
extern void ScriptCmd_PlayActorNamedMotion(void); /* ScriptCmd_PlayActorNamedMotion */
extern void func_ov001_0208db04(void); /* ScriptCmd_ShowSpeakerMessage */
extern void func_ov001_0208dba0(void); /* ScriptCmd_ShowTwoChoiceMessage */
extern void func_ov001_0208e6e8(void); /* ScriptCmd_ShowMessageWindow */
extern void func_ov001_0208e778(void); /* DefaultStepDone */
extern void func_ov001_0208e77c(void); /* ScriptCmd_DispatchToHandler */
extern void ScriptCmd_StartScreenFade(void); /* ScriptCmd_StartScreenFade */
extern void IsResourceReadyOrInitialize(void); /* IsResourceReadyOrInitialize */
extern void func_ov001_0208e7f8(void); /* ScriptCmd_OpenFieldPanelScreen */
extern void ScriptCmd_CloseFieldPanelScreen(void); /* ScriptCmd_CloseFieldPanelScreen */
extern void func_ov001_0208e8c4(void); /* ScriptCmd_SetActorExtraAnimation */
extern void func_ov001_0208e930(void); /* ScriptCmd_SetActorExtraSlot */
extern void func_ov001_0208e9ac(void); /* ScriptCmd_MoveActorToPosition */
extern void ScriptCmd_SetSubScreenVisible(void); /* ScriptCmd_SetSubScreenVisible */
extern void func_ov001_0208ea4c(void); /* ScriptCmd_SetActorSecondarySlot */
extern void func_ov001_0208eabc(void); /* ScriptCmd_TurnActorToHeading */
extern void ScriptCmd_TurnActorTowardTarget(void); /* ScriptCmd_TurnActorTowardTarget */
extern void ScriptCmd_IsActorHeadingReached(void); /* ScriptCmd_IsActorHeadingReached */
extern void ScriptCmd_SetWorkString(void); /* ScriptCmd_SetWorkString */
extern void FreeScriptWorkBuffers(void); /* FreeScriptWorkBuffers */
extern void func_ov001_0208dab8(void); /* DefaultStepDone */
extern void func_ov001_0208dabc(void); /* DefaultStepDone */
extern void func_ov001_0208dac0(void); /* PickRandomUnsetSessionFlag */
extern void func_ov001_0208eba8(void);
extern void func_ov001_0208ebb8(void);
extern void func_ov001_0208ebc8(void); /* ScriptCmd_ShowItemMessage */
extern void ScriptCmd_PlayStageEventAnimation(void); /* ScriptCmd_PlayStageEventAnimation */
extern void func_ov001_0208ecec(void);
extern void func_ov001_0208ed10(void); /* ScriptCmd_SetSceneFlagBit2 */
extern void func_ov001_0208ed54(void); /* ScriptCmd_FaceTargetWithAnims */
extern void ScriptOp_InitSubsystemIfFlagClear(void); /* ScriptOp_InitSubsystemIfFlagClear */
extern void ScriptCmd_QueueCameraAngleTransition(void); /* ScriptCmd_QueueCameraAngleTransition */
extern void func_ov001_0208ee58(void); /* ScriptCmd_EnterPhase */
extern void func_ov001_0208ee68(void);
extern void RefreshPartyMemberStates(void); /* RefreshPartyMemberStates */
extern void func_ov001_0208ef18(void); /* RecordPlayerStateFlags */
extern void Actor_BroadcastCallback(void); /* Actor_BroadcastCallback */
extern void func_ov001_0208ef8c(void); /* ScriptCmd_WaitMenuState */
extern void func_ov001_0208efd4(void); /* FS_UnloadOverlayImage */
extern void func_ov001_0208efe0(void); /* thumbStep */

void (*gActorScriptCommandHandlers[186])(void) = {
    ScriptCmd_SetScreenSwap, /* ScriptCmd_SetScreenSwap */
    NULL,
    func_ov001_0208c764, /* DefaultStepDone */
    NULL,
    func_ov001_0208d5c8, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_ReleaseSceneActors, /* ScriptCmd_ReleaseSceneActors */
    NULL,
    ScriptOp_RunActorPass, /* ScriptOp_RunActorPass */
    NULL,
    func_ov001_0208d1ac, /* ScriptCmd_BeginBrightnessFade */
    ScriptCmd_UpdateScreenBrightnessFades, /* ScriptCmd_UpdateScreenBrightnessFades */
    func_ov001_0208d5c0, /* DefaultStepDone */
    func_ov001_0208d5c4, /* DefaultStepDone */
    func_ov001_0208c768, /* ScriptCmd_InitActorCollision */
    NULL,
    func_ov001_0208c810, /* ScriptCmd_PlaceActor */
    NULL,
    func_ov001_0208c8cc, /* ScriptCmd_DetachActorAnimation */
    NULL,
    ScriptCmd_PlayActorUnnamedMotion, /* ScriptCmd_PlayActorUnnamedMotion */
    NULL,
    func_ov001_0208c940, /* ScriptCmd_AttachActorToParent */
    NULL,
    Script_ApplyActorAnimationState, /* Script_ApplyActorAnimationState */
    NULL,
    func_ov001_0208e54c, /* ScriptCmd_AttachActorObject */
    NULL,
    ScriptCmd_ShowActor, /* ScriptCmd_ShowActor */
    NULL,
    ScriptCmd_HideActor, /* ScriptCmd_HideActor */
    NULL,
    func_ov001_0208cabc, /* ScriptCmd_SetActorProbeSphere */
    func_ov001_0208cb3c, /* updateActorTransitionParameterRampCommand */
    func_ov001_0208cbbc,
    NULL,
    func_ov001_0208ded8, /* Script_MakeActorTranslucentAndClearVerticalOffset */
    NULL,
    PlaceActorRelativeToActor, /* PlaceActorRelativeToActor */
    NULL,
    func_ov001_0208cbdc, /* Script_SetActorParameterFromInteger */
    NULL,
    ScriptCmd_PlaceActor_0208e114, /* ScriptCmd_PlaceActor */
    NULL,
    ScriptCmd_BindActorTarget, /* ScriptCmd_BindActorTarget */
    ScriptCmd_SetElemFieldIfFlagSet, /* ScriptCmd_SetElemFieldIfFlagSet */
    func_ov001_0208e4b4, /* ScriptCmd_SetActorPlaybackRate */
    NULL,
    ScriptCmd_SetActorFlagBit4, /* ScriptCmd_SetActorFlagBit4 */
    NULL,
    ScriptCmd_SetActorPrimarySlot, /* ScriptCmd_SetActorPrimarySlot */
    NULL,
    ScriptCmd_SetActorAlpha, /* ScriptCmd_SetActorAlpha */
    func_ov001_0208e430, /* ScriptCmd_UpdateActorAlphaFade */
    ScriptCmd_StartActorRotation, /* ScriptCmd_StartActorRotation */
    NULL,
    func_ov001_0208debc, /* DefaultStepDone */
    NULL,
    func_ov001_0208dd08, /* DefaultStepDone */
    NULL,
    func_ov001_0208cce4, /* ScriptCmd_PlayActorMotionOrBlend */
    NULL,
    func_ov001_0208cda8, /* ScriptCmd_StoreIfFree */
    ScriptCmd_TestActorSlotMaskBit, /* ScriptCmd_TestActorSlotMaskBit */
    func_ov001_0208d624, /* ScriptCmd_PlayActorMotion */
    NULL,
    func_ov001_0208df2c, /* Script_SetActorAnimationFrame */
    NULL,
    func_ov001_0208ceec, /* ScriptCmd_SetActorMoveTarget */
    NULL,
    ScriptCmd_WaitActorReady, /* ScriptCmd_WaitActorReady */
    NULL,
    ScriptCmd_SetActorHeadingTowardTarget, /* ScriptCmd_SetActorHeadingTowardTarget */
    NULL,
    ScriptCmd_SetActorHeadingDegrees, /* ScriptCmd_SetActorHeadingDegrees */
    NULL,
    func_ov001_0208d29c, /* ScriptCmd_StartChannelTransform */
    NULL,
    ScriptCmd_SetActorChannelState, /* ScriptCmd_SetActorChannelState */
    NULL,
    ScriptCmd_PlayActorChannel, /* ScriptCmd_PlayActorChannel */
    NULL,
    func_ov001_0208d574, /* thumbStep */
    NULL,
    func_ov001_0208d55c, /* FS_UnloadOverlayImage */
    NULL,
    func_ov001_0208d568, /* FS_UnloadOverlayImage */
    NULL,
    func_ov001_0208d430, /* ScriptCmd_SetCameraTarget */
    NULL,
    ScriptCmd_ActorTimerOrAnim, /* ScriptCmd_ActorTimerOrAnim */
    NULL,
    ScriptCmd_ClearActorTimers, /* ScriptCmd_ClearActorTimers */
    NULL,
    func_ov001_0208e4ac, /* DefaultStepDone */
    NULL,
    func_ov001_0208e4b0, /* DefaultStepDone */
    NULL,
    func_ov001_0208e4e4, /* ScriptCmd_PlaySoundAtActor */
    NULL,
    func_ov001_0208d6d8, /* ScriptCmd_ShowActorMessage */
    NULL,
    func_ov001_0208dc54,
    NULL,
    ScriptCmd_ResetAndSetElemField, /* ScriptCmd_ResetAndSetElemField */
    ScriptCmd_SetElemFieldAndDispatch, /* ScriptCmd_SetElemFieldAndDispatch */
    func_ov001_0208e5c4, /* ScriptCmd_SetEntityFlag */
    NULL,
    ScriptCmd_StartScreenOverlayFade, /* ScriptCmd_StartScreenOverlayFade */
    func_ov001_0208e638, /* ScriptCmd_UpdateScreenOverlayFade */
    ScriptCmd_PlayActorNamedMotion, /* ScriptCmd_PlayActorNamedMotion */
    NULL,
    func_ov001_0208db04, /* ScriptCmd_ShowSpeakerMessage */
    NULL,
    func_ov001_0208dba0, /* ScriptCmd_ShowTwoChoiceMessage */
    NULL,
    func_ov001_0208e6e8, /* ScriptCmd_ShowMessageWindow */
    NULL,
    func_ov001_0208e778, /* DefaultStepDone */
    NULL,
    func_ov001_0208e77c, /* ScriptCmd_DispatchToHandler */
    NULL,
    ScriptCmd_StartScreenFade, /* ScriptCmd_StartScreenFade */
    IsResourceReadyOrInitialize, /* IsResourceReadyOrInitialize */
    func_ov001_0208e7f8, /* ScriptCmd_OpenFieldPanelScreen */
    NULL,
    ScriptCmd_CloseFieldPanelScreen, /* ScriptCmd_CloseFieldPanelScreen */
    NULL,
    func_ov001_0208e8c4, /* ScriptCmd_SetActorExtraAnimation */
    NULL,
    func_ov001_0208e930, /* ScriptCmd_SetActorExtraSlot */
    NULL,
    func_ov001_0208e9ac, /* ScriptCmd_MoveActorToPosition */
    NULL,
    ScriptCmd_SetSubScreenVisible, /* ScriptCmd_SetSubScreenVisible */
    NULL,
    func_ov001_0208ea4c, /* ScriptCmd_SetActorSecondarySlot */
    NULL,
    func_ov001_0208eabc, /* ScriptCmd_TurnActorToHeading */
    NULL,
    ScriptCmd_TurnActorTowardTarget, /* ScriptCmd_TurnActorTowardTarget */
    NULL,
    ScriptCmd_IsActorHeadingReached, /* ScriptCmd_IsActorHeadingReached */
    NULL,
    ScriptCmd_SetWorkString, /* ScriptCmd_SetWorkString */
    NULL,
    FreeScriptWorkBuffers, /* FreeScriptWorkBuffers */
    NULL,
    func_ov001_0208dab8, /* DefaultStepDone */
    func_ov001_0208dabc, /* DefaultStepDone */
    func_ov001_0208dac0, /* PickRandomUnsetSessionFlag */
    NULL,
    func_ov001_0208eba8,
    NULL,
    func_ov001_0208ebb8,
    NULL,
    func_ov001_0208ebc8, /* ScriptCmd_ShowItemMessage */
    NULL,
    ScriptCmd_PlayStageEventAnimation, /* ScriptCmd_PlayStageEventAnimation */
    NULL,
    func_ov001_0208ecec,
    NULL,
    func_ov001_0208ed10, /* ScriptCmd_SetSceneFlagBit2 */
    NULL,
    func_ov001_0208ed54, /* ScriptCmd_FaceTargetWithAnims */
    NULL,
    ScriptOp_InitSubsystemIfFlagClear, /* ScriptOp_InitSubsystemIfFlagClear */
    NULL,
    ScriptCmd_QueueCameraAngleTransition, /* ScriptCmd_QueueCameraAngleTransition */
    NULL,
    func_ov001_0208ee58, /* ScriptCmd_EnterPhase */
    NULL,
    func_ov001_0208ee68,
    NULL,
    RefreshPartyMemberStates, /* RefreshPartyMemberStates */
    NULL,
    func_ov001_0208ef18, /* RecordPlayerStateFlags */
    NULL,
    Actor_BroadcastCallback, /* Actor_BroadcastCallback */
    NULL,
    func_ov001_0208ef8c, /* ScriptCmd_WaitMenuState */
    NULL,
    func_ov001_0208efd4, /* FS_UnloadOverlayImage */
    NULL,
    func_ov001_0208efe0, /* thumbStep */
    NULL,
};
