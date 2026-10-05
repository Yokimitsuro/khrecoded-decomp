extern void SetPanelTransitionMode(int state);
extern int WM_SetParentParameter(void *fn, void *arg);
extern void WH_SetError(void);
extern void WH_StateOutSetParentParam(void);
extern int data_ov015_0207ea20;

int func_ov015_020737f0(void) {
    SetPanelTransitionMode(3);
    if (WM_SetParentParameter((void *)&WH_StateOutSetParentParam, &data_ov015_0207ea20) == 2) {
        return 1;
    }
    WH_SetError();
    SetPanelTransitionMode(9);
    return 0;
}
