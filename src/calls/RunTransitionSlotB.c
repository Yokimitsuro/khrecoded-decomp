extern int WMi_CheckStateEx(int a, int b);
extern void SetCommandArg(int slot, int arg);
extern int WMi_SendCommand(int slot, int flag);

int RunTransitionSlotB(int arg) {
    int r = WMi_CheckStateEx(1, 5);
    if (r != 0) {
        return r;
    }
    SetCommandArg(0xb, arg);
    r = WMi_SendCommand(0xb, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
