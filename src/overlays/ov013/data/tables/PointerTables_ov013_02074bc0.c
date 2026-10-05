#include "nitro/types.h"

extern void func_ov013_02071a90(void); /* PXI_Init */
extern void func_ov013_02071a9c(void); /* ResetPanelStepAndNotify */
extern void func_ov013_02071b6c(void);
extern void func_ov013_02072228(void); /* ApplyPanelSubitem5 */
extern void func_ov013_0207225c(void);
extern void func_ov013_020724c0(void); /* UpdatePanelResultState */
extern void func_ov013_02072674(void); /* ResetPanelLayoutClearFlag */
extern void func_ov013_02072c18(void); /* RefreshSelectedSlotFlags */
extern void func_ov013_02072d0c(void); /* UpdateSlotRemovalPhase */
extern void func_ov013_020731a4(void); /* CancelPanelConfirm */
extern void func_ov013_020727b4(void);
extern void func_ov013_020729e4(void); /* UpdatePanelResultPrompt */
extern void func_ov013_02072ae8(void); /* ResetPanelLayout */
extern void func_ov013_02073234(void);
extern void func_ov013_0207324c(void); /* PollPanelSaveStep */
extern void func_ov013_020732a4(void);
extern void func_ov013_020732a8(void); /* CloseRecordPanelMenu */
extern void func_ov013_020733f0(void); /* UpdatePanelMenuState */
extern void func_ov013_02073548(void); /* RefreshPanelSlotLinks */
extern void func_ov013_020735d0(void); /* ClosePanelMenu */
extern void func_ov013_0207370c(void); /* UpdatePanelBrowseState */
extern void ClearPanelListCallback(void); /* ClearPanelListCallback */
extern void func_ov013_0207390c(void);
extern void func_ov013_02073944(void); /* AdvancePanelCloseStep */
extern void func_ov013_020739a0(void);
extern void func_ov013_020739a4(void);
extern void func_ov013_020739bc(void);
extern void func_ov013_02073a98(void);
extern void func_ov013_02073a9c(void);
extern void func_ov013_02073ab4(void);
extern void func_ov013_02073b90(void);
extern void func_ov013_02073b94(void); /* OpenPanelConfirmPrompt */
extern void func_ov013_02073d14(void); /* UpdatePanelDismissPrompt */
extern void func_ov013_02073e38(void); /* RestorePanelBgPriorities */
extern void func_ov013_020718e0(void); /* UpdatePanelEntryState */

void (*gPanelMenuStateHandlers[34])(void) = {
    func_ov013_02071a90, /* PXI_Init */
    func_ov013_02071a9c, /* ResetPanelStepAndNotify */
    func_ov013_02071b6c,
    func_ov013_02072228, /* ApplyPanelSubitem5 */
    func_ov013_0207225c,
    func_ov013_020724c0, /* UpdatePanelResultState */
    func_ov013_02072674, /* ResetPanelLayoutClearFlag */
    func_ov013_02072c18, /* RefreshSelectedSlotFlags */
    func_ov013_02072d0c, /* UpdateSlotRemovalPhase */
    func_ov013_020731a4, /* CancelPanelConfirm */
    func_ov013_020727b4,
    func_ov013_020729e4, /* UpdatePanelResultPrompt */
    func_ov013_02072ae8, /* ResetPanelLayout */
    func_ov013_02073234,
    func_ov013_0207324c, /* PollPanelSaveStep */
    func_ov013_020732a4,
    func_ov013_020732a8, /* CloseRecordPanelMenu */
    func_ov013_020733f0, /* UpdatePanelMenuState */
    func_ov013_02073548, /* RefreshPanelSlotLinks */
    func_ov013_020735d0, /* ClosePanelMenu */
    func_ov013_0207370c, /* UpdatePanelBrowseState */
    ClearPanelListCallback, /* ClearPanelListCallback */
    func_ov013_0207390c,
    func_ov013_02073944, /* AdvancePanelCloseStep */
    func_ov013_020739a0,
    func_ov013_020739a4,
    func_ov013_020739bc,
    func_ov013_02073a98,
    func_ov013_02073a9c,
    func_ov013_02073ab4,
    func_ov013_02073b90,
    func_ov013_02073b94, /* OpenPanelConfirmPrompt */
    func_ov013_02073d14, /* UpdatePanelDismissPrompt */
    func_ov013_02073e38, /* RestorePanelBgPriorities */
};

void (*gPanelEntryStateHandler[1])(void) = {
    func_ov013_020718e0, /* UpdatePanelEntryState */
};
