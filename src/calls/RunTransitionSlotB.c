extern int func_0201109c(int a, int b);
extern void SetCommandArg(int slot, int arg);
extern int func_02010f94(int slot, int flag);

int RunTransitionSlotB(int arg) {
    int r = func_0201109c(1, 5);
    if (r != 0) {
        return r;
    }
    SetCommandArg(0xb, arg);
    r = func_02010f94(0xb, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
