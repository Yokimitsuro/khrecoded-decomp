extern int RunTransitionSlotB(void *handler);
extern void WH_SetError(int id);
extern void OnWirelessScanEnded(int req);

int func_ov015_0207414c(void) {
    int r = RunTransitionSlotB(&OnWirelessScanEnded);
    if (r != 2) {
        WH_SetError(r);
        return 0;
    }
    return 1;
}
