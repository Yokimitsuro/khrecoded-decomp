extern void WH_SetError(unsigned int id);
extern void SetPanelTransitionMode(int state);
extern int func_ov015_02073930(void);

void func_ov015_020738f8(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        WH_SetError(*(unsigned short *)(req + 2));
        SetPanelTransitionMode(9);
        return;
    }
    if (func_ov015_02073930() != 0) {
        return;
    }
    SetPanelTransitionMode(9);
}
