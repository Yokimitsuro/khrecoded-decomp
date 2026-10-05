extern int WMi_InitCore(int a0, int a1, int a2);
extern int data_020597fc;

int WmInit(int a0, int a1) {
    int result = WMi_InitCore(a0, a1, 0xf00);
    if (result != 0) {
        return result;
    }
    *(unsigned short *)(*(char **)((char *)&data_020597fc + 4) + 0x16) = 0;
    return result;
}
