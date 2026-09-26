extern int func_02009114(void);
extern void OS_Terminate(void);

void func_02009120(void) {
    if (func_02009114() == 0) {
        OS_Terminate();
    }
}
