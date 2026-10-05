extern void WM_MeasureChannel(int target, int prio, int id, int arg, int ttl);
void func_ov015_02074b04(int target, int arg) {
    WM_MeasureChannel(target, 3, 0x11, arg, 0x1e);
}
