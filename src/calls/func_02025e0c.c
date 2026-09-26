extern short *func_02025d1c(void);

int func_02025e0c(void) {
    short *ptr = func_02025d1c();
    int value = 0;

    if (ptr[0] == 1) {
        return *(int *)(ptr + 2) << 12;
    }

    if (ptr[0] == 0x10) {
        value = *(int *)(ptr + 2);
    }

    return value;
}
