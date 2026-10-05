#include "nitro/types.h"

extern void StopTouchPanelSampling(void); /* StopTouchPanelSampling */
extern void func_ov000_020622b8(void); /* ApplyPanelSelection */
extern void func_ov000_02062318(void);
extern void func_ov000_0206243c(void); /* InitPanelSceneAndClearBg1 */
extern void func_ov000_02062568(void); /* WaitForAnimationFinish */
extern void func_ov000_02062598(void); /* ForceReleaseEmbedded */
extern void ResetPanelStateAndLoadSlot0(void); /* ResetPanelStateAndLoadSlot0 */
extern void func_ov000_020625d4(void); /* ScanSaveSlots */
extern void func_ov000_0206276c(void);
extern void func_ov000_02062794(void); /* EnterPanelMenuScreen */
extern void func_ov000_02062838(void); /* UpdatePanelInputWithTimeout */
extern void func_ov000_02062908(void); /* NNS_G2dSetCellAnimationSequence */
extern void func_ov000_02062920(void);
extern void func_ov000_02062a10(void); /* TryEnterPanelState */
extern void func_ov000_02062a58(void); /* PXI_Init */
extern void func_ov000_02062a64(void); /* SetupPanelField */
extern void func_ov000_02062a98(void);
extern void ReleaseFieldAndReset(void); /* ReleaseFieldAndReset */
extern void func_ov000_02062c08(void); /* UpdatePanelLookup */
extern void func_ov000_02062c64(void); /* HandleSessionModeTransition */
extern void func_ov000_02062cf4(void); /* ReleaseHandleAndResetDisplay */
extern void func_ov000_02062d38(void); /* LoadOverlay22AndClearFlag */
extern void func_ov000_02062d60(void); /* UpdatePanelRequest */
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
    func_ov000_020622b8, /* ApplyPanelSelection */
    func_ov000_02062318,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    func_ov000_020622b8, /* ApplyPanelSelection */
    func_ov000_02062318,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    func_ov000_020622b8, /* ApplyPanelSelection */
    func_ov000_02062318,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    func_ov000_0206243c, /* InitPanelSceneAndClearBg1 */
    func_ov000_02062568, /* WaitForAnimationFinish */
    func_ov000_02062598, /* ForceReleaseEmbedded */
    ResetPanelStateAndLoadSlot0, /* ResetPanelStateAndLoadSlot0 */
    func_ov000_020625d4, /* ScanSaveSlots */
    func_ov000_0206276c,
    func_ov000_02062794, /* EnterPanelMenuScreen */
    func_ov000_02062838, /* UpdatePanelInputWithTimeout */
    func_ov000_02062908, /* NNS_G2dSetCellAnimationSequence */
    func_ov000_02062920,
    func_ov000_02062a10, /* TryEnterPanelState */
    func_ov000_02062a58, /* PXI_Init */
    func_ov000_02062a64, /* SetupPanelField */
    func_ov000_02062a98,
    ReleaseFieldAndReset, /* ReleaseFieldAndReset */
    func_ov000_02062a64, /* SetupPanelField */
    func_ov000_02062a98,
    ReleaseFieldAndReset, /* ReleaseFieldAndReset */
    func_ov000_02062c08, /* UpdatePanelLookup */
    func_ov000_02062c64, /* HandleSessionModeTransition */
    func_ov000_02062cf4, /* ReleaseHandleAndResetDisplay */
    func_ov000_02062d38, /* LoadOverlay22AndClearFlag */
    func_ov000_02062d60, /* UpdatePanelRequest */
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
