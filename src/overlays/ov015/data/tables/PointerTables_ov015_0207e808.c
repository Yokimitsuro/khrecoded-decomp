#include "nitro/types.h"

extern void func_ov015_02072f98(void);
extern void func_ov015_02072f9c(void);
extern void func_ov015_02072fa0(void);
extern void func_ov015_02072fa4(void);
extern void func_ov015_02072fa8(void); /* PXI_Init */
extern void DispatchPanelTransition(void); /* DispatchPanelTransition */
extern void func_ov015_02073018(void);
extern void func_ov015_02073030(void);
extern void HandleMatchTransition(void); /* HandleMatchTransition */
extern void func_ov015_020730a4(void);
extern void func_ov015_020730a8(void);
extern void UpdateWirelessParentState(void); /* UpdateWirelessParentState */
extern void func_ov015_02073148(void);
extern void func_ov015_0207314c(void);
extern void HandleConnectTransition(void); /* HandleConnectTransition */
extern void func_ov015_020731b8(void);
extern void func_ov015_020731bc(void);
extern void func_ov015_020731d4(void);
extern void func_ov015_0207321c(void);
extern void func_ov015_02073220(void);
extern void func_ov015_02073238(void);
extern void func_ov015_02073280(void);
extern void func_ov015_02072f7c(void);

void (*gWirelessStateHandlers[22])(void) = {
    func_ov015_02072f98,
    func_ov015_02072f9c,
    func_ov015_02072fa0,
    func_ov015_02072fa4,
    func_ov015_02072fa8, /* PXI_Init */
    DispatchPanelTransition, /* DispatchPanelTransition */
    func_ov015_02073018,
    func_ov015_02073030,
    HandleMatchTransition, /* HandleMatchTransition */
    func_ov015_020730a4,
    func_ov015_020730a8,
    UpdateWirelessParentState, /* UpdateWirelessParentState */
    func_ov015_02073148,
    func_ov015_0207314c,
    HandleConnectTransition, /* HandleConnectTransition */
    func_ov015_020731b8,
    func_ov015_020731bc,
    func_ov015_020731d4,
    func_ov015_0207321c,
    func_ov015_02073220,
    func_ov015_02073238,
    func_ov015_02073280,
};

void (*gWirelessStateUpdateCallback[1])(void) = {
    func_ov015_02072f7c,
};
