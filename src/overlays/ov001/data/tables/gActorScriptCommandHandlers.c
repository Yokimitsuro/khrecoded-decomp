#include "nitro/types.h"

extern void ScriptCmd_SetScreenSwap(void); /* ScriptCmd_SetScreenSwap */
extern void func_ov001_0208c764(void); /* DefaultStepDone */
extern void func_ov001_0208d5c8(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_ReleaseSceneActors(void); /* ScriptCmd_ReleaseSceneActors */
extern void ScriptOp_RunActorPass(void); /* ScriptOp_RunActorPass */
extern void ScriptCmd_BeginBrightnessFade(void); /* ScriptCmd_BeginBrightnessFade */
extern void ScriptCmd_UpdateScreenBrightnessFades(void); /* ScriptCmd_UpdateScreenBrightnessFades */
extern void func_ov001_0208d5c0(void); /* DefaultStepDone */
extern void func_ov001_0208d5c4(void); /* DefaultStepDone */
extern void ScriptCmd_InitActorCollision(void); /* ScriptCmd_InitActorCollision */
extern void ScriptCmd_PlaceActor(void); /* ScriptCmd_PlaceActor */
extern void ScriptCmd_DetachActorAnimation(void); /* ScriptCmd_DetachActorAnimation */
extern void ScriptCmd_PlayActorUnnamedMotion(void); /* ScriptCmd_PlayActorUnnamedMotion */
extern void ScriptCmd_AttachActorToParent(void); /* ScriptCmd_AttachActorToParent */
extern void Script_ApplyActorAnimationState(void); /* Script_ApplyActorAnimationState */
extern void ScriptCmd_AttachActorObject(void); /* ScriptCmd_AttachActorObject */
extern void ScriptCmd_ShowActor(void); /* ScriptCmd_ShowActor */
extern void ScriptCmd_HideActor(void); /* ScriptCmd_HideActor */
extern void ScriptCmd_SetActorProbeSphere(void); /* ScriptCmd_SetActorProbeSphere */
extern void func_ov001_0208cb3c(void); /* updateActorTransitionParameterRampCommand */
extern void func_ov001_0208cbbc(void);
extern void func_ov001_0208ded8(void); /* Script_MakeActorTranslucentAndClearVerticalOffset */
extern void PlaceActorRelativeToActor(void); /* PlaceActorRelativeToActor */
extern void Script_SetActorParameterFromInteger(void); /* Script_SetActorParameterFromInteger */
extern void ScriptCmd_PlaceActor_0208e114(void); /* ScriptCmd_PlaceActor */
extern void ScriptCmd_BindActorTarget(void); /* ScriptCmd_BindActorTarget */
extern void ScriptCmd_SetElemFieldIfFlagSet(void); /* ScriptCmd_SetElemFieldIfFlagSet */
extern void ScriptCmd_SetActorPlaybackRate(void); /* ScriptCmd_SetActorPlaybackRate */
extern void ScriptCmd_SetActorFlagBit4(void); /* ScriptCmd_SetActorFlagBit4 */
extern void ScriptCmd_SetActorPrimarySlot(void); /* ScriptCmd_SetActorPrimarySlot */
extern void ScriptCmd_SetActorAlpha(void); /* ScriptCmd_SetActorAlpha */
extern void ScriptCmd_UpdateActorAlphaFade(void); /* ScriptCmd_UpdateActorAlphaFade */
extern void ScriptCmd_StartActorRotation(void); /* ScriptCmd_StartActorRotation */
extern void func_ov001_0208debc(void); /* DefaultStepDone */
extern void func_ov001_0208dd08(void); /* DefaultStepDone */
extern void ScriptCmd_PlayActorMotionOrBlend(void); /* ScriptCmd_PlayActorMotionOrBlend */
extern void func_ov001_0208cda8(void); /* ScriptCmd_StoreIfFree */
extern void ScriptCmd_TestActorSlotMaskBit(void); /* ScriptCmd_TestActorSlotMaskBit */
extern void ScriptCmd_PlayActorMotion(void); /* ScriptCmd_PlayActorMotion */
extern void func_ov001_0208df2c(void); /* Script_SetActorAnimationFrame */
extern void ScriptCmd_SetActorMoveTarget(void); /* ScriptCmd_SetActorMoveTarget */
extern void ScriptCmd_WaitActorReady(void); /* ScriptCmd_WaitActorReady */
extern void ScriptCmd_SetActorHeadingTowardTarget(void); /* ScriptCmd_SetActorHeadingTowardTarget */
extern void ScriptCmd_SetActorHeadingDegrees(void); /* ScriptCmd_SetActorHeadingDegrees */
extern void ScriptCmd_StartChannelTransform(void); /* ScriptCmd_StartChannelTransform */
extern void ScriptCmd_SetActorChannelState(void); /* ScriptCmd_SetActorChannelState */
extern void ScriptCmd_PlayActorChannel(void); /* ScriptCmd_PlayActorChannel */
extern void func_ov001_0208d574(void); /* thumbStep */
extern void func_ov001_0208d55c(void); /* FS_UnloadOverlayImage */
extern void func_ov001_0208d568(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_SetCameraTarget(void); /* ScriptCmd_SetCameraTarget */
extern void ScriptCmd_ActorTimerOrAnim(void); /* ScriptCmd_ActorTimerOrAnim */
extern void ScriptCmd_ClearActorTimers(void); /* ScriptCmd_ClearActorTimers */
extern void func_ov001_0208e4ac(void); /* DefaultStepDone */
extern void func_ov001_0208e4b0(void); /* DefaultStepDone */
extern void ScriptCmd_PlaySoundAtActor(void); /* ScriptCmd_PlaySoundAtActor */
extern void ScriptCmd_ShowActorMessage(void); /* ScriptCmd_ShowActorMessage */
extern void func_ov001_0208dc54(void);
extern void ScriptCmd_ResetAndSetElemField(void); /* ScriptCmd_ResetAndSetElemField */
extern void ScriptCmd_SetElemFieldAndDispatch(void); /* ScriptCmd_SetElemFieldAndDispatch */
extern void ScriptCmd_SetEntityFlag(void); /* ScriptCmd_SetEntityFlag */
extern void ScriptCmd_StartScreenOverlayFade(void); /* ScriptCmd_StartScreenOverlayFade */
extern void ScriptCmd_UpdateScreenOverlayFade(void); /* ScriptCmd_UpdateScreenOverlayFade */
extern void ScriptCmd_PlayActorNamedMotion(void); /* ScriptCmd_PlayActorNamedMotion */
extern void ScriptCmd_ShowSpeakerMessage(void); /* ScriptCmd_ShowSpeakerMessage */
extern void ScriptCmd_ShowTwoChoiceMessage(void); /* ScriptCmd_ShowTwoChoiceMessage */
extern void ScriptCmd_ShowMessageWindow(void); /* ScriptCmd_ShowMessageWindow */
extern void func_ov001_0208e778(void); /* DefaultStepDone */
extern void func_ov001_0208e77c(void); /* ScriptCmd_DispatchToHandler */
extern void ScriptCmd_StartScreenFade(void); /* ScriptCmd_StartScreenFade */
extern void IsResourceReadyOrInitialize(void); /* IsResourceReadyOrInitialize */
extern void ScriptCmd_OpenFieldPanelScreen(void); /* ScriptCmd_OpenFieldPanelScreen */
extern void ScriptCmd_CloseFieldPanelScreen(void); /* ScriptCmd_CloseFieldPanelScreen */
extern void ScriptCmd_SetActorExtraAnimation(void); /* ScriptCmd_SetActorExtraAnimation */
extern void ScriptCmd_SetActorExtraSlot(void); /* ScriptCmd_SetActorExtraSlot */
extern void ScriptCmd_MoveActorToPosition(void); /* ScriptCmd_MoveActorToPosition */
extern void ScriptCmd_SetSubScreenVisible(void); /* ScriptCmd_SetSubScreenVisible */
extern void ScriptCmd_SetActorSecondarySlot(void); /* ScriptCmd_SetActorSecondarySlot */
extern void ScriptCmd_TurnActorToHeading(void); /* ScriptCmd_TurnActorToHeading */
extern void ScriptCmd_TurnActorTowardTarget(void); /* ScriptCmd_TurnActorTowardTarget */
extern void ScriptCmd_IsActorHeadingReached(void); /* ScriptCmd_IsActorHeadingReached */
extern void ScriptCmd_SetWorkString(void); /* ScriptCmd_SetWorkString */
extern void FreeScriptWorkBuffers(void); /* FreeScriptWorkBuffers */
extern void func_ov001_0208dab8(void); /* DefaultStepDone */
extern void func_ov001_0208dabc(void); /* DefaultStepDone */
extern void PickRandomUnsetSessionFlag(void); /* PickRandomUnsetSessionFlag */
extern void func_ov001_0208eba8(void);
extern void func_ov001_0208ebb8(void);
extern void ScriptCmd_ShowItemMessage(void); /* ScriptCmd_ShowItemMessage */
extern void ScriptCmd_PlayStageEventAnimation(void); /* ScriptCmd_PlayStageEventAnimation */
extern void func_ov001_0208ecec(void);
extern void func_ov001_0208ed10(void); /* ScriptCmd_SetSceneFlagBit2 */
extern void ScriptCmd_FaceTargetWithAnims(void); /* ScriptCmd_FaceTargetWithAnims */
extern void ScriptOp_InitSubsystemIfFlagClear(void); /* ScriptOp_InitSubsystemIfFlagClear */
extern void ScriptCmd_QueueCameraAngleTransition(void); /* ScriptCmd_QueueCameraAngleTransition */
extern void func_ov001_0208ee58(void); /* ScriptCmd_EnterPhase */
extern void func_ov001_0208ee68(void);
extern void RefreshPartyMemberStates(void); /* RefreshPartyMemberStates */
extern void RecordPlayerStateFlags(void); /* RecordPlayerStateFlags */
extern void Actor_BroadcastCallback(void); /* Actor_BroadcastCallback */
extern void ScriptCmd_WaitMenuState(void); /* ScriptCmd_WaitMenuState */
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
    ScriptCmd_BeginBrightnessFade, /* ScriptCmd_BeginBrightnessFade */
    ScriptCmd_UpdateScreenBrightnessFades, /* ScriptCmd_UpdateScreenBrightnessFades */
    func_ov001_0208d5c0, /* DefaultStepDone */
    func_ov001_0208d5c4, /* DefaultStepDone */
    ScriptCmd_InitActorCollision, /* ScriptCmd_InitActorCollision */
    NULL,
    ScriptCmd_PlaceActor, /* ScriptCmd_PlaceActor */
    NULL,
    ScriptCmd_DetachActorAnimation, /* ScriptCmd_DetachActorAnimation */
    NULL,
    ScriptCmd_PlayActorUnnamedMotion, /* ScriptCmd_PlayActorUnnamedMotion */
    NULL,
    ScriptCmd_AttachActorToParent, /* ScriptCmd_AttachActorToParent */
    NULL,
    Script_ApplyActorAnimationState, /* Script_ApplyActorAnimationState */
    NULL,
    ScriptCmd_AttachActorObject, /* ScriptCmd_AttachActorObject */
    NULL,
    ScriptCmd_ShowActor, /* ScriptCmd_ShowActor */
    NULL,
    ScriptCmd_HideActor, /* ScriptCmd_HideActor */
    NULL,
    ScriptCmd_SetActorProbeSphere, /* ScriptCmd_SetActorProbeSphere */
    func_ov001_0208cb3c, /* updateActorTransitionParameterRampCommand */
    func_ov001_0208cbbc,
    NULL,
    func_ov001_0208ded8, /* Script_MakeActorTranslucentAndClearVerticalOffset */
    NULL,
    PlaceActorRelativeToActor, /* PlaceActorRelativeToActor */
    NULL,
    Script_SetActorParameterFromInteger, /* Script_SetActorParameterFromInteger */
    NULL,
    ScriptCmd_PlaceActor_0208e114, /* ScriptCmd_PlaceActor */
    NULL,
    ScriptCmd_BindActorTarget, /* ScriptCmd_BindActorTarget */
    ScriptCmd_SetElemFieldIfFlagSet, /* ScriptCmd_SetElemFieldIfFlagSet */
    ScriptCmd_SetActorPlaybackRate, /* ScriptCmd_SetActorPlaybackRate */
    NULL,
    ScriptCmd_SetActorFlagBit4, /* ScriptCmd_SetActorFlagBit4 */
    NULL,
    ScriptCmd_SetActorPrimarySlot, /* ScriptCmd_SetActorPrimarySlot */
    NULL,
    ScriptCmd_SetActorAlpha, /* ScriptCmd_SetActorAlpha */
    ScriptCmd_UpdateActorAlphaFade, /* ScriptCmd_UpdateActorAlphaFade */
    ScriptCmd_StartActorRotation, /* ScriptCmd_StartActorRotation */
    NULL,
    func_ov001_0208debc, /* DefaultStepDone */
    NULL,
    func_ov001_0208dd08, /* DefaultStepDone */
    NULL,
    ScriptCmd_PlayActorMotionOrBlend, /* ScriptCmd_PlayActorMotionOrBlend */
    NULL,
    func_ov001_0208cda8, /* ScriptCmd_StoreIfFree */
    ScriptCmd_TestActorSlotMaskBit, /* ScriptCmd_TestActorSlotMaskBit */
    ScriptCmd_PlayActorMotion, /* ScriptCmd_PlayActorMotion */
    NULL,
    func_ov001_0208df2c, /* Script_SetActorAnimationFrame */
    NULL,
    ScriptCmd_SetActorMoveTarget, /* ScriptCmd_SetActorMoveTarget */
    NULL,
    ScriptCmd_WaitActorReady, /* ScriptCmd_WaitActorReady */
    NULL,
    ScriptCmd_SetActorHeadingTowardTarget, /* ScriptCmd_SetActorHeadingTowardTarget */
    NULL,
    ScriptCmd_SetActorHeadingDegrees, /* ScriptCmd_SetActorHeadingDegrees */
    NULL,
    ScriptCmd_StartChannelTransform, /* ScriptCmd_StartChannelTransform */
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
    ScriptCmd_SetCameraTarget, /* ScriptCmd_SetCameraTarget */
    NULL,
    ScriptCmd_ActorTimerOrAnim, /* ScriptCmd_ActorTimerOrAnim */
    NULL,
    ScriptCmd_ClearActorTimers, /* ScriptCmd_ClearActorTimers */
    NULL,
    func_ov001_0208e4ac, /* DefaultStepDone */
    NULL,
    func_ov001_0208e4b0, /* DefaultStepDone */
    NULL,
    ScriptCmd_PlaySoundAtActor, /* ScriptCmd_PlaySoundAtActor */
    NULL,
    ScriptCmd_ShowActorMessage, /* ScriptCmd_ShowActorMessage */
    NULL,
    func_ov001_0208dc54,
    NULL,
    ScriptCmd_ResetAndSetElemField, /* ScriptCmd_ResetAndSetElemField */
    ScriptCmd_SetElemFieldAndDispatch, /* ScriptCmd_SetElemFieldAndDispatch */
    ScriptCmd_SetEntityFlag, /* ScriptCmd_SetEntityFlag */
    NULL,
    ScriptCmd_StartScreenOverlayFade, /* ScriptCmd_StartScreenOverlayFade */
    ScriptCmd_UpdateScreenOverlayFade, /* ScriptCmd_UpdateScreenOverlayFade */
    ScriptCmd_PlayActorNamedMotion, /* ScriptCmd_PlayActorNamedMotion */
    NULL,
    ScriptCmd_ShowSpeakerMessage, /* ScriptCmd_ShowSpeakerMessage */
    NULL,
    ScriptCmd_ShowTwoChoiceMessage, /* ScriptCmd_ShowTwoChoiceMessage */
    NULL,
    ScriptCmd_ShowMessageWindow, /* ScriptCmd_ShowMessageWindow */
    NULL,
    func_ov001_0208e778, /* DefaultStepDone */
    NULL,
    func_ov001_0208e77c, /* ScriptCmd_DispatchToHandler */
    NULL,
    ScriptCmd_StartScreenFade, /* ScriptCmd_StartScreenFade */
    IsResourceReadyOrInitialize, /* IsResourceReadyOrInitialize */
    ScriptCmd_OpenFieldPanelScreen, /* ScriptCmd_OpenFieldPanelScreen */
    NULL,
    ScriptCmd_CloseFieldPanelScreen, /* ScriptCmd_CloseFieldPanelScreen */
    NULL,
    ScriptCmd_SetActorExtraAnimation, /* ScriptCmd_SetActorExtraAnimation */
    NULL,
    ScriptCmd_SetActorExtraSlot, /* ScriptCmd_SetActorExtraSlot */
    NULL,
    ScriptCmd_MoveActorToPosition, /* ScriptCmd_MoveActorToPosition */
    NULL,
    ScriptCmd_SetSubScreenVisible, /* ScriptCmd_SetSubScreenVisible */
    NULL,
    ScriptCmd_SetActorSecondarySlot, /* ScriptCmd_SetActorSecondarySlot */
    NULL,
    ScriptCmd_TurnActorToHeading, /* ScriptCmd_TurnActorToHeading */
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
    PickRandomUnsetSessionFlag, /* PickRandomUnsetSessionFlag */
    NULL,
    func_ov001_0208eba8,
    NULL,
    func_ov001_0208ebb8,
    NULL,
    ScriptCmd_ShowItemMessage, /* ScriptCmd_ShowItemMessage */
    NULL,
    ScriptCmd_PlayStageEventAnimation, /* ScriptCmd_PlayStageEventAnimation */
    NULL,
    func_ov001_0208ecec,
    NULL,
    func_ov001_0208ed10, /* ScriptCmd_SetSceneFlagBit2 */
    NULL,
    ScriptCmd_FaceTargetWithAnims, /* ScriptCmd_FaceTargetWithAnims */
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
    RecordPlayerStateFlags, /* RecordPlayerStateFlags */
    NULL,
    Actor_BroadcastCallback, /* Actor_BroadcastCallback */
    NULL,
    ScriptCmd_WaitMenuState, /* ScriptCmd_WaitMenuState */
    NULL,
    func_ov001_0208efd4, /* FS_UnloadOverlayImage */
    NULL,
    func_ov001_0208efe0, /* thumbStep */
    NULL,
};
