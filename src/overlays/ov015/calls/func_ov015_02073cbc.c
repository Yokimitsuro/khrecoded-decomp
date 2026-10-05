extern void func_ov015_020737c4(int mode);
extern int WM_EndMP(void *cb);
extern void func_ov015_020737d4(int result);
extern void func_ov015_02073cec(void);

int func_ov015_02073cbc(void) {
    int r;

    func_ov015_020737c4(3);
    r = WM_EndMP(&func_ov015_02073cec);
    if (r == 2) {
        return 1;
    }
    func_ov015_020737d4(r);
    return 0;
}
