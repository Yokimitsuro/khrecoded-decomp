extern int func_02025df8(int owner, void *entry);
extern int func_02025e2c(int owner, int handle);
extern int func_ov022_020a73f8(int handle);
extern int func_ov022_020a8938(void);

int func_ov022_020a7978(int owner, void *entry) {
    int len;
    int pos;

    len = func_02025df8(owner, entry);
    if (func_ov022_020a73f8(func_02025e2c(owner, len)) == 0) {
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
