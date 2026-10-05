#include "nitro/types.h"

extern void func_ov013_02071a90(void); /* PXI_Init */
extern void ResetPanelStepAndNotify(void); /* ResetPanelStepAndNotify */
extern void func_ov013_02071b6c(void);
extern void ApplyPanelSubitem5(void); /* ApplyPanelSubitem5 */
extern void func_ov013_0207225c(void);
extern void UpdatePanelResultState(void); /* UpdatePanelResultState */
extern void ResetPanelLayoutClearFlag(void); /* ResetPanelLayoutClearFlag */
extern void RefreshSelectedSlotFlags(void); /* RefreshSelectedSlotFlags */
extern void UpdateSlotRemovalPhase(void); /* UpdateSlotRemovalPhase */
extern void CancelPanelConfirm(void); /* CancelPanelConfirm */
extern void func_ov013_020727b4(void);
extern void UpdatePanelResultPrompt(void); /* UpdatePanelResultPrompt */
extern void ResetPanelLayout(void); /* ResetPanelLayout */
extern void func_ov013_02073234(void);
extern void PollPanelSaveStep(void); /* PollPanelSaveStep */
extern void func_ov013_020732a4(void);
extern void CloseRecordPanelMenu(void); /* CloseRecordPanelMenu */
extern void UpdatePanelMenuState(void); /* UpdatePanelMenuState */
extern void RefreshPanelSlotLinks(void); /* RefreshPanelSlotLinks */
extern void ClosePanelMenu(void); /* ClosePanelMenu */
extern void UpdatePanelBrowseState(void); /* UpdatePanelBrowseState */
extern void ClearPanelListCallback(void); /* ClearPanelListCallback */
extern void func_ov013_0207390c(void);
extern void AdvancePanelCloseStep(void); /* AdvancePanelCloseStep */
extern void func_ov013_020739a0(void);
extern void func_ov013_020739a4(void);
extern void func_ov013_020739bc(void);
extern void func_ov013_02073a98(void);
extern void func_ov013_02073a9c(void);
extern void func_ov013_02073ab4(void);
extern void func_ov013_02073b90(void);
extern void OpenPanelConfirmPrompt(void); /* OpenPanelConfirmPrompt */
extern void UpdatePanelDismissPrompt(void); /* UpdatePanelDismissPrompt */
extern void RestorePanelBgPriorities(void); /* RestorePanelBgPriorities */
extern void UpdatePanelEntryState(void); /* UpdatePanelEntryState */

void (*gPanelMenuStateHandlers[34])(void) = {
    func_ov013_02071a90, /* PXI_Init */
    ResetPanelStepAndNotify, /* ResetPanelStepAndNotify */
    func_ov013_02071b6c,
    ApplyPanelSubitem5, /* ApplyPanelSubitem5 */
    func_ov013_0207225c,
    UpdatePanelResultState, /* UpdatePanelResultState */
    ResetPanelLayoutClearFlag, /* ResetPanelLayoutClearFlag */
    RefreshSelectedSlotFlags, /* RefreshSelectedSlotFlags */
    UpdateSlotRemovalPhase, /* UpdateSlotRemovalPhase */
    CancelPanelConfirm, /* CancelPanelConfirm */
    func_ov013_020727b4,
    UpdatePanelResultPrompt, /* UpdatePanelResultPrompt */
    ResetPanelLayout, /* ResetPanelLayout */
    func_ov013_02073234,
    PollPanelSaveStep, /* PollPanelSaveStep */
    func_ov013_020732a4,
    CloseRecordPanelMenu, /* CloseRecordPanelMenu */
    UpdatePanelMenuState, /* UpdatePanelMenuState */
    RefreshPanelSlotLinks, /* RefreshPanelSlotLinks */
    ClosePanelMenu, /* ClosePanelMenu */
    UpdatePanelBrowseState, /* UpdatePanelBrowseState */
    ClearPanelListCallback, /* ClearPanelListCallback */
    func_ov013_0207390c,
    AdvancePanelCloseStep, /* AdvancePanelCloseStep */
    func_ov013_020739a0,
    func_ov013_020739a4,
    func_ov013_020739bc,
    func_ov013_02073a98,
    func_ov013_02073a9c,
    func_ov013_02073ab4,
    func_ov013_02073b90,
    OpenPanelConfirmPrompt, /* OpenPanelConfirmPrompt */
    UpdatePanelDismissPrompt, /* UpdatePanelDismissPrompt */
    RestorePanelBgPriorities, /* RestorePanelBgPriorities */
};

void (*gPanelEntryStateHandler[1])(void) = {
    UpdatePanelEntryState, /* UpdatePanelEntryState */
};
