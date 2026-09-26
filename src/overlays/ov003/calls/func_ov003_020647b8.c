extern int func_02025df8(int owner, void *entry);
extern int func_02025e2c(int owner, int handle);
extern int func_ov003_02063fe4(int handle);
extern int func_ov022_020a8938(void);

int func_ov003_020647b8(int owner, void *entry) {
    int len;
    int pos;

    len = func_02025df8(owner, entry);
    if (func_ov003_02063fe4(func_02025e2c(owner, len)) == 0) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }

    pos = func_ov022_020a8938();
    if (pos < len) {
        return 0;
    }
    if (pos >= len) {
        return 1;
    }
    return 1;
}
