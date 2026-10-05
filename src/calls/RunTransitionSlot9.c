extern int WMi_CheckStateEx(int a, int b);
extern void SetCommandArg(int slot, int arg);
extern int WMi_SendCommand(int slot, int flag);

int RunTransitionSlot9(int arg) {
    int r = WMi_CheckStateEx(1, 7);
    if (r != 0) {
        return r;
    }
    SetCommandArg(9, arg);
    r = WMi_SendCommand(9, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
