extern void func_02015808(int, int);

void func_0204f2ac(int param_1, int param_2, int param_3) {
    char *elem = (char *)(param_1 + 4) + param_2 * 0x8c;
    if (param_2 < 0) {
        return;
    }
    func_02015808((int)(elem + 0x14), param_3);
}
