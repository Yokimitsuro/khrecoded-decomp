extern unsigned char *func_0204cf6c(int arg);
extern void func_0204ce98(int arg0, int arg1, int arg2);

int func_0204d7c4(int arg) {
    unsigned char *ptr = func_0204cf6c(0);

    if (ptr == 0 || ptr[0] != 1) {
        func_0204ce98(1, arg, 0);
    } else {
        ptr[1] = arg;
    }

    return 1;
}
