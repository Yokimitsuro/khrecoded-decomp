extern void WH_SetError(unsigned int id);
extern void func_ov015_02074ec8(void);
extern int func_ov015_02074698(void);
extern void SetPanelTransitionMode(int state);

void func_ov015_02074664(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        WH_SetError(*(unsigned short *)(req + 2));
        func_ov015_02074ec8();
        return;
    }
    if (func_ov015_02074698() != 0) {
        return;
    }
    SetPanelTransitionMode(9);
}
