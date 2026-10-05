#include "nitro/types.h"

extern void ScriptCmd_ResetAndDispatch(void); /* ScriptCmd_ResetAndDispatch */
extern void func_ov036_020bdd08(void); /* PXI_Init */
extern void func_ov036_020bdd10(void);
extern void func_ov036_020bdd50(void);
extern void func_ov036_020bdd74(void); /* ScriptCmd_EnterPhase */
extern void func_ov036_020bdd84(void);
extern void func_ov036_020bddb4(void); /* IsSceneState0 */
extern void func_ov036_020bde28(void); /* ScriptCmd_OpenActorTextWindow */
extern void func_ov036_020bdeec(void); /* ScriptCmd_OpenTextWindowAtCursor */
extern void func_ov036_020bdfa8(void); /* ScriptCmd_OpenWindowAtPoint */
extern void func_ov036_020be050(void); /* ScriptCmd_WaitWindowChoice */
extern void func_ov036_020be098(void); /* FS_UnloadOverlayImage */
extern void func_ov036_020be0a4(void); /* DefaultStepDone */
extern void func_ov036_020be0a8(void);
extern void ScriptCmd_WaitScreenLayerIdle(void); /* ScriptCmd_WaitScreenLayerIdle */
extern void func_ov036_020be0e4(void); /* ScriptCmd_ResetScreenLayer */
extern void ScriptCmd_WaitScreenLayerIdle_020be118(void); /* ScriptCmd_WaitScreenLayerIdle */
extern void IsPxiResourceReadyOrInitialize(void); /* IsPxiResourceReadyOrInitialize */
extern void func_ov036_020be14c(void);
extern void func_ov036_020be170(void);
extern void func_ov036_020be1b0(void); /* ScriptCmd_EnterPhase */
extern void func_ov036_020be1c0(void);
extern void func_ov036_020be200(void); /* ScriptCmd_ShowJoinedMessage */
extern void func_ov036_020be284(void); /* ScriptCmd_ShowMessageWindow */
extern void func_ov036_020be344(void);
extern void func_ov036_020be3cc(void);
extern void func_ov036_020be488(void); /* ScriptCmd_WaitWindowAnswer */
extern void func_ov036_020be4ec(void);
extern void ScriptCmd_ResetAndDispatch_020be55c(void); /* ScriptCmd_ResetAndDispatch */
extern void func_ov036_020be57c(void); /* PXI_Init */
extern void func_ov036_020be584(void); /* ScriptCmd_PlaceEntityAndMove */
extern void func_ov036_020be5f4(void); /* ScriptCmd_SetEntityMotion */
extern void func_ov036_020be628(void);
extern void func_ov036_020be64c(void); /* ScriptCmd_StartBrightnessFade */
extern void func_ov036_020be67c(void);
extern void func_ov036_020be6bc(void); /* ScriptCmd_OpenFormattedTextWindow */
extern void func_ov036_020be78c(void); /* FSi_CloseFileCommand */
extern void IsResourceReadyOrInitialize_020be790(void); /* IsResourceReadyOrInitialize */
extern void ScriptCmd_StartMosaicTransition(void); /* ScriptCmd_StartMosaicTransition */
extern void func_ov036_020be7e0(void); /* IsSceneState0 */
extern void func_ov036_020be7f4(void); /* ScriptCmd_SetCursorOverride */

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
    func_ov036_020bde28, /* ScriptCmd_OpenActorTextWindow */
    NULL,
    func_ov036_020bdeec, /* ScriptCmd_OpenTextWindowAtCursor */
    NULL,
    func_ov036_020bdfa8, /* ScriptCmd_OpenWindowAtPoint */
    NULL,
    func_ov036_020be050, /* ScriptCmd_WaitWindowChoice */
    NULL,
    func_ov036_020be098, /* FS_UnloadOverlayImage */
    func_ov036_020be0a4, /* DefaultStepDone */
    func_ov036_020be0a8,
    ScriptCmd_WaitScreenLayerIdle, /* ScriptCmd_WaitScreenLayerIdle */
    func_ov036_020be0e4, /* ScriptCmd_ResetScreenLayer */
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
    func_ov036_020be200, /* ScriptCmd_ShowJoinedMessage */
    NULL,
    func_ov036_020be284, /* ScriptCmd_ShowMessageWindow */
    NULL,
    func_ov036_020be344,
    NULL,
    func_ov036_020be3cc,
    func_ov036_020be488, /* ScriptCmd_WaitWindowAnswer */
    func_ov036_020be4ec,
    NULL,
    ScriptCmd_ResetAndDispatch_020be55c, /* ScriptCmd_ResetAndDispatch */
    func_ov036_020be57c, /* PXI_Init */
    func_ov036_020be584, /* ScriptCmd_PlaceEntityAndMove */
    NULL,
    func_ov036_020be5f4, /* ScriptCmd_SetEntityMotion */
    NULL,
    func_ov036_020be628,
    NULL,
    func_ov036_020be64c, /* ScriptCmd_StartBrightnessFade */
    NULL,
    func_ov036_020be67c,
    NULL,
    func_ov036_020be6bc, /* ScriptCmd_OpenFormattedTextWindow */
    NULL,
    func_ov036_020be78c, /* FSi_CloseFileCommand */
    IsResourceReadyOrInitialize_020be790, /* IsResourceReadyOrInitialize */
    ScriptCmd_StartMosaicTransition, /* ScriptCmd_StartMosaicTransition */
    func_ov036_020be7e0, /* IsSceneState0 */
    func_ov036_020be7f4, /* ScriptCmd_SetCursorOverride */
    NULL,
};
