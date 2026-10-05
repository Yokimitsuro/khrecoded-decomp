extern void MI_CpuFill8(void *dst, int val, unsigned int n);
extern int _s32_div_f(int a, int b);
extern void func_020524fc(void *p);
extern void NNS_FndInitList(void *list, int a);
extern void InitObjManagerAndMark(char *obj, int *tmpl);
extern void func_ov027_020b8fb8(char *obj, char *data, int count);
extern unsigned char gTaskManager;
int InitializeResourceContainer(char *param_1, int *param_2, int param_3, int param_4) {
    int budget;
    MI_CpuFill8(param_1, 0, 0x647c);
    *(unsigned short *)(param_1 + 0x6474) = 0xf0;
    switch (gTaskManager) {
        case 1: budget = 0x14; break;
        case 0: budget = 0x1e; break;
        case 2: budget = 0x3c; break;
    }
    *(int *)(param_1 + 0x6470) = _s32_div_f(0x3c000, budget);
    func_020524fc(param_1 + 0x6450);
    NNS_FndInitList(param_1 + 0x6434, 0);
    if (param_2 != 0) {
        InitObjManagerAndMark(param_1, param_2);
        if (param_2[5] != 0 && param_2[4] > 0) {
            func_ov027_020b8fb8(param_1, (char *)param_2[5], param_2[4]);
        }
    }
    return 1;
}
