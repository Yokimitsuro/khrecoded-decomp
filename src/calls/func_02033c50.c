extern void func_02033aa4(int, int, int);

void func_02033c50(int *param_1, int param_2) {
    if (param_1[0x27] == 0) {
        return;
    }
    func_02033aa4(param_1[0x27], (int)param_1 + 0x84, param_2);
}
