extern int func_02011950(void *handler);
extern void func_ov015_020737d4(int id);
extern void func_ov015_02074174(int req);

int func_ov015_0207414c(void) {
    int r = func_02011950(&func_ov015_02074174);
    if (r != 2) {
        func_ov015_020737d4(r);
        return 0;
    }
    return 1;
}
