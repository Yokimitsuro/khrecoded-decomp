#include "nitro/types.h"

extern void func_ov015_02070c54(void);
extern void ResetPanelSelection(void); /* ResetPanelSelection */
extern void UpdatePanelMenuState_02070c80(void); /* UpdatePanelMenuState */
extern void func_ov015_02070fa8(void); /* PXI_Init */
extern void func_ov015_02070fb4(void);
extern void UpdatePanelPendingAction(void); /* UpdatePanelPendingAction */
extern void func_ov015_02071060(void);
extern void StartPlayerCardSharing(void); /* StartPlayerCardSharing */
extern void UpdatePanelShareState(void);
extern void func_ov015_020716ec(void); /* PXI_Init */
extern void func_ov015_02071a78(void); /* OSi_IrqDma0 */
extern void func_ov015_02071a88(void);
extern void func_ov015_02071ab0(void);
extern void OpenResultPanel(void); /* OpenResultPanel */
extern void func_ov015_02071bec(void);
extern void RequestPanelConfirm(void); /* RequestPanelConfirm */
extern void ResetPanelEntry9(void); /* ResetPanelEntry9 */
extern void UpdatePanelResultPhase(void); /* UpdatePanelResultPhase */
extern void func_ov015_02071e2c(void);
extern void func_ov015_02071e48(void);
extern void UpdatePanelConfirmSequence(void); /* UpdatePanelConfirmSequence */
extern void ResetPanelMenuElements(void); /* ResetPanelMenuElements */
extern void UpdatePanelExitSequence(void); /* UpdatePanelExitSequence */

void (*gLinkPanelStateHandlers[22])(void) = {
    func_ov015_02070c54,
    ResetPanelSelection, /* ResetPanelSelection */
    UpdatePanelMenuState_02070c80, /* UpdatePanelMenuState */
    func_ov015_02070fa8, /* PXI_Init */
    func_ov015_02070fb4,
    UpdatePanelPendingAction, /* UpdatePanelPendingAction */
    func_ov015_02071060,
    StartPlayerCardSharing, /* StartPlayerCardSharing */
    UpdatePanelShareState,
    func_ov015_020716ec, /* PXI_Init */
    func_ov015_02071a78, /* OSi_IrqDma0 */
    func_ov015_02071a88,
    func_ov015_02071ab0,
    OpenResultPanel, /* OpenResultPanel */
    func_ov015_02071bec,
    RequestPanelConfirm, /* RequestPanelConfirm */
    ResetPanelEntry9, /* ResetPanelEntry9 */
    UpdatePanelResultPhase, /* UpdatePanelResultPhase */
    func_ov015_02071e2c,
    func_ov015_02071e48,
    UpdatePanelConfirmSequence, /* UpdatePanelConfirmSequence */
    ResetPanelMenuElements, /* ResetPanelMenuElements */
};

void (*gLinkPanelExitHandler[1])(void) = {
    UpdatePanelExitSequence, /* UpdatePanelExitSequence */
};
