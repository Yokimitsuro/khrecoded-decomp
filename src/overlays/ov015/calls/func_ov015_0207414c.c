extern int RunTransitionSlotB(void *handler);
extern void WH_SetError(int id);
extern void func_ov015_02074174(int req);

int func_ov015_0207414c(void) {
    int r = RunTransitionSlotB(&func_ov015_02074174);
    if (r != 2) {
        WH_SetError(r);
        return 0;
    }
    return 1;
}
