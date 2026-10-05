#include "nitro/types.h"

extern void StopTouchPanelSampling(void); /* StopTouchPanelSampling */
extern void ApplyPanelSelection(void); /* ApplyPanelSelection */
extern void func_ov000_02062318(void);
extern void InitPanelSceneAndClearBg1(void); /* InitPanelSceneAndClearBg1 */
extern void WaitForAnimationFinish(void); /* WaitForAnimationFinish */
extern void ForceReleaseEmbedded(void); /* ForceReleaseEmbedded */
extern void ResetPanelStateAndLoadSlot0(void); /* ResetPanelStateAndLoadSlot0 */
extern void ScanSaveSlots(void); /* ScanSaveSlots */
extern void func_ov000_0206276c(void);
extern void EnterPanelMenuScreen(void); /* EnterPanelMenuScreen */
extern void UpdatePanelInputWithTimeout(void); /* UpdatePanelInputWithTimeout */
extern void func_ov000_02062908(void); /* NNS_G2dSetCellAnimationSequence */
extern void func_ov000_02062920(void);
extern void TryEnterPanelState(void); /* TryEnterPanelState */
extern void func_ov000_02062a58(void); /* PXI_Init */
extern void SetupPanelField(void); /* SetupPanelField */
extern void func_ov000_02062a98(void);
extern void ReleaseFieldAndReset(void); /* ReleaseFieldAndReset */
extern void UpdatePanelLookup(void); /* UpdatePanelLookup */
extern void HandleSessionModeTransition(void); /* HandleSessionModeTransition */
extern void ReleaseHandleAndResetDisplay(void); /* ReleaseHandleAndResetDisplay */
extern void func_ov000_02062d38(void); /* LoadOverlay22AndClearFlag */
extern void UpdatePanelRequest(void); /* UpdatePanelRequest */
extern void func_ov000_02062e00(void);
extern void func_ov000_02062e3c(void);
extern void func_ov000_02062e64(void);
extern void func_ov000_02062f0c(void);
extern void func_ov000_02062f44(void);
extern void func_ov000_02062f74(void);
extern void func_ov000_0206300c(void); /* PXI_Init */
extern void func_ov000_02063018(void);
extern void func_ov000_02063038(void);
extern void func_ov000_02063040(void);

void (*gPanelStateHandlers[43])(void) = {
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    ApplyPanelSelection, /* ApplyPanelSelection */
    func_ov000_02062318,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    ApplyPanelSelection, /* ApplyPanelSelection */
    func_ov000_02062318,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    ApplyPanelSelection, /* ApplyPanelSelection */
    func_ov000_02062318,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    InitPanelSceneAndClearBg1, /* InitPanelSceneAndClearBg1 */
    WaitForAnimationFinish, /* WaitForAnimationFinish */
    ForceReleaseEmbedded, /* ForceReleaseEmbedded */
    ResetPanelStateAndLoadSlot0, /* ResetPanelStateAndLoadSlot0 */
    ScanSaveSlots, /* ScanSaveSlots */
    func_ov000_0206276c,
    EnterPanelMenuScreen, /* EnterPanelMenuScreen */
    UpdatePanelInputWithTimeout, /* UpdatePanelInputWithTimeout */
    func_ov000_02062908, /* NNS_G2dSetCellAnimationSequence */
    func_ov000_02062920,
    TryEnterPanelState, /* TryEnterPanelState */
    func_ov000_02062a58, /* PXI_Init */
    SetupPanelField, /* SetupPanelField */
    func_ov000_02062a98,
    ReleaseFieldAndReset, /* ReleaseFieldAndReset */
    SetupPanelField, /* SetupPanelField */
    func_ov000_02062a98,
    ReleaseFieldAndReset, /* ReleaseFieldAndReset */
    UpdatePanelLookup, /* UpdatePanelLookup */
    HandleSessionModeTransition, /* HandleSessionModeTransition */
    ReleaseHandleAndResetDisplay, /* ReleaseHandleAndResetDisplay */
    func_ov000_02062d38, /* LoadOverlay22AndClearFlag */
    UpdatePanelRequest, /* UpdatePanelRequest */
    func_ov000_02062e00,
    func_ov000_02062e3c,
    func_ov000_02062e64,
    func_ov000_02062f0c,
    func_ov000_02062f44,
    func_ov000_02062f74,
    func_ov000_0206300c, /* PXI_Init */
    func_ov000_02063018,
    func_ov000_02063038,
    func_ov000_02063040,
};

void (*gPanelInitialStateHandler[1])(void) = {
    func_ov000_02062318,
};
