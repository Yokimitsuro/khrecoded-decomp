extern unsigned char *func_0204cf6c(int arg);
extern void func_0204ce98(int arg0, int arg1, int arg2);

void func_0204d808(int arg) {
    unsigned char *ptr = func_0204cf6c(0);

    if (ptr == 0 || ptr[0] != 3) {
        func_0204ce98(3, 0, (unsigned short)arg);
        return;
    }

    *(unsigned short *)(ptr + 2) = arg;
}
