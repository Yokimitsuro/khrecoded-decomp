extern int func_02025dc0(void *a, void *b);
extern void func_ov003_02063e94(int x);

int func_ov003_02064764(void *arg1, char *arg2) {
    int v = 0;
    if (*(short *)(arg2 + 0) == 2) {
        v = func_02025dc0(arg1, arg2);
    }
    if (*(short *)(arg2 + 8) == 2) {
        func_02025dc0(arg1, arg2 + 8);
    }
    if (*(short *)(arg2 + 0x10) == 2) {
        func_02025dc0(arg1, arg2 + 0x10);
    }
    func_ov003_02063e94(v);
    return 1;
}
