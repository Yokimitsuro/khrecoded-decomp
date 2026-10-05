extern int func_0201109c(int a, int b);
extern void SetCommandArg(int slot, int arg);
extern int func_02010f94(int slot, int flag);

int RunTransitionSlot9(int arg) {
    int r = func_0201109c(1, 7);
    if (r != 0) {
        return r;
    }
    SetCommandArg(9, arg);
    r = func_02010f94(9, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
