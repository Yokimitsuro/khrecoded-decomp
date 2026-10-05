extern int RunTransitionSlot9(void *handler);
extern void func_ov015_020737d4(int id);
extern void func_ov015_02073d44(int req);

int func_ov015_02073d1c(void) {
    int r = RunTransitionSlot9(&func_ov015_02073d44);
    if (r != 2) {
        func_ov015_020737d4(r);
        return 0;
    }
    return 1;
}
