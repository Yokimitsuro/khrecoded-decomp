extern void WH_SetError(unsigned int id);
extern void SetPanelTransitionMode(int state);
extern int WH_StartScanStep(void);

void func_ov015_020738f8(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        WH_SetError(*(unsigned short *)(req + 2));
        SetPanelTransitionMode(9);
        return;
    }
    if (WH_StartScanStep() != 0) {
        return;
    }
    SetPanelTransitionMode(9);
}
