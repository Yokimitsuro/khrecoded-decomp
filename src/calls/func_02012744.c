extern void OS_Terminate(void);
extern void func_0201277c(void);
extern int data_0205a2a8[];

void func_02012744(int param_1, unsigned param_2) {
    if ((param_2 & 0x3f) == 0x11) {
        int result;
        int (*fn)(void);
        if (data_0205a2a8[3] != 0) return;
        result = 0;
        fn = (int (*)(void))data_0205a2a8[6];
        if (fn != 0) result = fn();
        if (result != 0) func_0201277c();
        data_0205a2a8[3] = 1;
    } else {
        OS_Terminate();
    }
}
