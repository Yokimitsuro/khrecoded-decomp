/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void MI_CpuFill8(void *dst, int value, int size);
extern char data_020603d8[];
extern char gTaskManager[];

void func_0202a438(void) {
    MI_CpuFill8(data_020603d8, 0, 0x100);
    *(int *)(gTaskManager + 0xc) = 0;
    *(int *)(gTaskManager + 4) = 0;
    *(int *)(gTaskManager + 8) = 0;
}
