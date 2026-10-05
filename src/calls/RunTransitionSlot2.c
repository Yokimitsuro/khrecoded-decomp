extern int WMi_CheckStateEx(int a, int b);
extern void SetCommandArg(int slot, int arg);
extern int WMi_SendCommand(int slot, int flag);

int RunTransitionSlot2(int arg) {
    int r = WMi_CheckStateEx(1, 2);
    if (r != 0) {
        return r;
    }
    SetCommandArg(2, arg);
    r = WMi_SendCommand(2, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
