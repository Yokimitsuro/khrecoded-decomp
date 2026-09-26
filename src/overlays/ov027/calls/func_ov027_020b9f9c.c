extern void MI_CpuCopy8(void *src, void *dst, int size);
extern int data_ov027_020ba3e0;
int func_ov027_020b9f9c(int param_1) {
    int src = data_ov027_020ba3e0;
    if (src == 0) return 0;
    MI_CpuCopy8((void *)src, (void *)param_1, 8);
    return param_1;
}
