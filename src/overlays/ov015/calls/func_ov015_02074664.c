extern void WH_SetError(unsigned int id);
extern void WH_Finalize(void);
extern int func_ov015_02074698(void);
extern void SetPanelTransitionMode(int state);

void func_ov015_02074664(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        WH_SetError(*(unsigned short *)(req + 2));
        WH_Finalize();
        return;
    }
    if (func_ov015_02074698() != 0) {
        return;
    }
    SetPanelTransitionMode(9);
}
