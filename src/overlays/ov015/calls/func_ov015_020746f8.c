extern void SetPanelTransitionMode(int mode);
extern int RunTransitionSlot1(void *cb);
extern void WH_SetError(int result);
extern void func_ov015_02074728(void);

int func_ov015_020746f8(void) {
    int r;

    SetPanelTransitionMode(3);
    r = RunTransitionSlot1(&func_ov015_02074728);
    if (r == 2) {
        return 1;
    }
    WH_SetError(r);
    return 0;
}
