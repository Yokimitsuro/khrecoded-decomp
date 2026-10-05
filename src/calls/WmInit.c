extern int func_02010d94(int a0, int a1, int a2);
extern int data_020597fc;

int WmInit(int a0, int a1) {
    int result = func_02010d94(a0, a1, 0xf00);
    if (result != 0) {
        return result;
    }
    *(unsigned short *)(*(char **)((char *)&data_020597fc + 4) + 0x16) = 0;
    return result;
}
