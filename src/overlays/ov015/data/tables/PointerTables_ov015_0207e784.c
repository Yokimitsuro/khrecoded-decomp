#include "nitro/types.h"

extern void func_ov015_02070c54(void);
extern void func_ov015_02070c58(void); /* ResetPanelSelection */
extern void func_ov015_02070c80(void); /* UpdatePanelMenuState */
extern void func_ov015_02070fa8(void); /* PXI_Init */
extern void func_ov015_02070fb4(void);
extern void func_ov015_02070fe8(void); /* UpdatePanelPendingAction */
extern void func_ov015_02071060(void);
extern void func_ov015_02071064(void); /* StartPlayerCardSharing */
extern void func_ov015_02071100(void);
extern void func_ov015_020716ec(void); /* PXI_Init */
extern void func_ov015_02071a78(void); /* OSi_IrqDma0 */
extern void func_ov015_02071a88(void);
extern void func_ov015_02071ab0(void);
extern void func_ov015_02071ab4(void); /* OpenResultPanel */
extern void func_ov015_02071bec(void);
extern void func_ov015_02071c60(void); /* RequestPanelConfirm */
extern void func_ov015_02071ca8(void); /* ResetPanelEntry9 */
extern void func_ov015_02071d0c(void); /* UpdatePanelResultPhase */
extern void func_ov015_02071e2c(void);
extern void func_ov015_02071e48(void);
extern void func_ov015_02071fdc(void); /* UpdatePanelConfirmSequence */
extern void func_ov015_020720e4(void); /* ResetPanelMenuElements */
extern void func_ov015_02070b8c(void); /* UpdatePanelExitSequence */

void (*gLinkPanelStateHandlers[22])(void) = {
    func_ov015_02070c54,
    func_ov015_02070c58, /* ResetPanelSelection */
    func_ov015_02070c80, /* UpdatePanelMenuState */
    func_ov015_02070fa8, /* PXI_Init */
    func_ov015_02070fb4,
    func_ov015_02070fe8, /* UpdatePanelPendingAction */
    func_ov015_02071060,
    func_ov015_02071064, /* StartPlayerCardSharing */
    func_ov015_02071100,
    func_ov015_020716ec, /* PXI_Init */
    func_ov015_02071a78, /* OSi_IrqDma0 */
    func_ov015_02071a88,
    func_ov015_02071ab0,
    func_ov015_02071ab4, /* OpenResultPanel */
    func_ov015_02071bec,
    func_ov015_02071c60, /* RequestPanelConfirm */
    func_ov015_02071ca8, /* ResetPanelEntry9 */
    func_ov015_02071d0c, /* UpdatePanelResultPhase */
    func_ov015_02071e2c,
    func_ov015_02071e48,
    func_ov015_02071fdc, /* UpdatePanelConfirmSequence */
    func_ov015_020720e4, /* ResetPanelMenuElements */
};

void (*gLinkPanelExitHandler[1])(void) = {
    func_ov015_02070b8c, /* UpdatePanelExitSequence */
};
