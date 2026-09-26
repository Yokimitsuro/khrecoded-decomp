extern void OS_Terminate(void);
extern unsigned short data_0205a2a4;

void func_02012728(int unused, int status) {
    if ((status & 0x3f) == 1) {
        data_0205a2a4 = 1;
        return;
    }
    OS_Terminate();
}
