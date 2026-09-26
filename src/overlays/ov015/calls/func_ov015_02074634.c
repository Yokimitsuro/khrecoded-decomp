extern void func_ov015_020737c4(int mode);
extern int func_02011c8c(void *cb);
extern void func_ov015_020737d4(int result);
extern void func_ov015_02074664(void);

int func_ov015_02074634(void) {
    int r;

    func_ov015_020737c4(3);
    r = func_02011c8c(&func_ov015_02074664);
    if (r == 2) {
        return 1;
    }
    func_ov015_020737d4(r);
    return 0;
}
