extern int func_02011070(void);
extern void SetCommandArg(int slot, int arg);
extern int func_02010f94(int slot, int flag);

int func_020116fc(int arg) {
    int r = func_02011070();
    if (r != 0) {
        return r;
    }
    SetCommandArg(1, arg);
    r = func_02010f94(1, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
