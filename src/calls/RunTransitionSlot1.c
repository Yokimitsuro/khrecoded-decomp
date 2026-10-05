extern int PollDeviceStatus(void);
extern void SetCommandArg(int slot, int arg);
extern int func_02010f94(int slot, int flag);

int RunTransitionSlot1(int arg) {
    int r = PollDeviceStatus();
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
