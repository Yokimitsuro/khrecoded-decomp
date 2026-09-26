extern void func_ov015_020737c4(int);
extern void OS_Terminate(void);
void func_ov015_02074ce0(char *scene) {
    if (*(unsigned short *)(scene + 2) == 8) {
        func_ov015_020737c4(9);
        OS_Terminate();
    }
}
