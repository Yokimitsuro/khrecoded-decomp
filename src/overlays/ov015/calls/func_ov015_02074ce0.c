extern void SetPanelTransitionMode(int);
extern void OS_Terminate(void);
void func_ov015_02074ce0(char *scene) {
    if (*(unsigned short *)(scene + 2) == 8) {
        SetPanelTransitionMode(9);
        OS_Terminate();
    }
}
