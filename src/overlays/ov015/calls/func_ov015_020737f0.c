extern void func_ov015_020737c4(int state);
extern int WM_SetParentParameter(void *fn, void *arg);
extern void func_ov015_020737d4(void);
extern void func_ov015_02073830(void);
extern int data_ov015_0207ea20;

int func_ov015_020737f0(void) {
    func_ov015_020737c4(3);
    if (WM_SetParentParameter((void *)&func_ov015_02073830, &data_ov015_0207ea20) == 2) {
        return 1;
    }
    func_ov015_020737d4();
    func_ov015_020737c4(9);
    return 0;
}
