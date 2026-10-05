#include "nitro/types.h"

extern void ScriptCmd_ResetAndDispatch(void); /* ScriptCmd_ResetAndDispatch */
extern void func_ov036_020bdd08(void); /* PXI_Init */
extern void func_ov036_020bdd10(void);
extern void func_ov036_020bdd50(void);
extern void func_ov036_020bdd74(void); /* ScriptCmd_EnterPhase */
extern void func_ov036_020bdd84(void);
extern void func_ov036_020bddb4(void); /* IsSceneState0 */
extern void ScriptCmd_OpenActorTextWindow(void); /* ScriptCmd_OpenActorTextWindow */
extern void ScriptCmd_OpenTextWindowAtCursor(void); /* ScriptCmd_OpenTextWindowAtCursor */
extern void ScriptCmd_OpenWindowAtPoint(void); /* ScriptCmd_OpenWindowAtPoint */
extern void ScriptCmd_WaitWindowChoice(void); /* ScriptCmd_WaitWindowChoice */
extern void func_ov036_020be098(void); /* FS_UnloadOverlayImage */
extern void func_ov036_020be0a4(void); /* DefaultStepDone */
extern void func_ov036_020be0a8(void);
extern void ScriptCmd_WaitScreenLayerIdle(void); /* ScriptCmd_WaitScreenLayerIdle */
extern void ScriptCmd_ResetScreenLayer(void); /* ScriptCmd_ResetScreenLayer */
extern void ScriptCmd_WaitScreenLayerIdle_020be118(void); /* ScriptCmd_WaitScreenLayerIdle */
extern void IsPxiResourceReadyOrInitialize(void); /* IsPxiResourceReadyOrInitialize */
extern void func_ov036_020be14c(void);
extern void func_ov036_020be170(void);
extern void func_ov036_020be1b0(void); /* ScriptCmd_EnterPhase */
extern void func_ov036_020be1c0(void);
extern void ScriptCmd_ShowJoinedMessage(void); /* ScriptCmd_ShowJoinedMessage */
extern void ScriptCmd_ShowMessageWindow_020be284(void); /* ScriptCmd_ShowMessageWindow */
extern void func_ov036_020be344(void);
extern void func_ov036_020be3cc(void);
extern void ScriptCmd_WaitWindowAnswer(void); /* ScriptCmd_WaitWindowAnswer */
extern void func_ov036_020be4ec(void);
extern void ScriptCmd_ResetAndDispatch_020be55c(void); /* ScriptCmd_ResetAndDispatch */
extern void func_ov036_020be57c(void); /* PXI_Init */
extern void ScriptCmd_PlaceEntityAndMove(void); /* ScriptCmd_PlaceEntityAndMove */
extern void ScriptCmd_SetEntityMotion(void); /* ScriptCmd_SetEntityMotion */
extern void func_ov036_020be628(void);
extern void ScriptCmd_StartBrightnessFade(void); /* ScriptCmd_StartBrightnessFade */
extern void func_ov036_020be67c(void);
extern void ScriptCmd_OpenFormattedTextWindow(void); /* ScriptCmd_OpenFormattedTextWindow */
extern void func_ov036_020be78c(void); /* FSi_CloseFileCommand */
extern void IsResourceReadyOrInitialize_020be790(void); /* IsResourceReadyOrInitialize */
extern void ScriptCmd_StartMosaicTransition(void); /* ScriptCmd_StartMosaicTransition */
extern void func_ov036_020be7e0(void); /* IsSceneState0 */
extern void ScriptCmd_SetCursorOverride(void); /* ScriptCmd_SetCursorOverride */

void (*gTextScriptCommandHandlers[64])(void) = {
    ScriptCmd_ResetAndDispatch, /* ScriptCmd_ResetAndDispatch */
    func_ov036_020bdd08, /* PXI_Init */
    func_ov036_020bdd10,
    NULL,
    func_ov036_020bdd50,
    NULL,
    func_ov036_020bdd74, /* ScriptCmd_EnterPhase */
    NULL,
    func_ov036_020bdd84,
    func_ov036_020bddb4, /* IsSceneState0 */
    ScriptCmd_OpenActorTextWindow, /* ScriptCmd_OpenActorTextWindow */
    NULL,
    ScriptCmd_OpenTextWindowAtCursor, /* ScriptCmd_OpenTextWindowAtCursor */
    NULL,
    ScriptCmd_OpenWindowAtPoint, /* ScriptCmd_OpenWindowAtPoint */
    NULL,
    ScriptCmd_WaitWindowChoice, /* ScriptCmd_WaitWindowChoice */
    NULL,
    func_ov036_020be098, /* FS_UnloadOverlayImage */
    func_ov036_020be0a4, /* DefaultStepDone */
    func_ov036_020be0a8,
    ScriptCmd_WaitScreenLayerIdle, /* ScriptCmd_WaitScreenLayerIdle */
    ScriptCmd_ResetScreenLayer, /* ScriptCmd_ResetScreenLayer */
    ScriptCmd_WaitScreenLayerIdle_020be118, /* ScriptCmd_WaitScreenLayerIdle */
    IsPxiResourceReadyOrInitialize, /* IsPxiResourceReadyOrInitialize */
    NULL,
    func_ov036_020be14c,
    NULL,
    func_ov036_020be170,
    NULL,
    func_ov036_020be1b0, /* ScriptCmd_EnterPhase */
    NULL,
    func_ov036_020be1c0,
    NULL,
    ScriptCmd_ShowJoinedMessage, /* ScriptCmd_ShowJoinedMessage */
    NULL,
    ScriptCmd_ShowMessageWindow_020be284, /* ScriptCmd_ShowMessageWindow */
    NULL,
    func_ov036_020be344,
    NULL,
    func_ov036_020be3cc,
    ScriptCmd_WaitWindowAnswer, /* ScriptCmd_WaitWindowAnswer */
    func_ov036_020be4ec,
    NULL,
    ScriptCmd_ResetAndDispatch_020be55c, /* ScriptCmd_ResetAndDispatch */
    func_ov036_020be57c, /* PXI_Init */
    ScriptCmd_PlaceEntityAndMove, /* ScriptCmd_PlaceEntityAndMove */
    NULL,
    ScriptCmd_SetEntityMotion, /* ScriptCmd_SetEntityMotion */
    NULL,
    func_ov036_020be628,
    NULL,
    ScriptCmd_StartBrightnessFade, /* ScriptCmd_StartBrightnessFade */
    NULL,
    func_ov036_020be67c,
    NULL,
    ScriptCmd_OpenFormattedTextWindow, /* ScriptCmd_OpenFormattedTextWindow */
    NULL,
    func_ov036_020be78c, /* FSi_CloseFileCommand */
    IsResourceReadyOrInitialize_020be790, /* IsResourceReadyOrInitialize */
    ScriptCmd_StartMosaicTransition, /* ScriptCmd_StartMosaicTransition */
    func_ov036_020be7e0, /* IsSceneState0 */
    ScriptCmd_SetCursorOverride, /* ScriptCmd_SetCursorOverride */
    NULL,
};
