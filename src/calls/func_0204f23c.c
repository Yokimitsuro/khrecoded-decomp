extern int func_020151ac(void *p);

int func_0204f23c(char *arg0, int arg1) {
    if (arg1 < 0) {
        return 0;
    }
    return func_020151ac(arg0 + 0x18 + arg1 * 0x8c);
}
