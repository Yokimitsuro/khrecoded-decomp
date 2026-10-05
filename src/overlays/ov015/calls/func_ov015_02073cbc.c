extern void SetPanelTransitionMode(int mode);
extern int WM_EndMP(void *cb);
extern void WH_SetError(int result);
extern void func_ov015_02073cec(void);

int func_ov015_02073cbc(void) {
    int r;

    SetPanelTransitionMode(3);
    r = WM_EndMP(&func_ov015_02073cec);
    if (r == 2) {
        return 1;
    }
    WH_SetError(r);
    return 0;
}
