extern void MI_CpuCopy8(void *src, void *dst, int size);
extern int func_ov027_020b9f9c(int target);
extern void func_ov027_020b79dc(int self, int target);
struct f2c { unsigned char b0 : 1, b1 : 1, b2 : 1; };
int func_ov027_020b7a50(int param_1, int param_2) {
    struct f2c *fp = (struct f2c *)(param_1 + 0x2c);
    int r = 1;
    if (fp->b1) {
        if (fp->b2 == 0) {
            r = 0;
        } else {
            MI_CpuCopy8((void *)(param_1 + 0x24), (void *)param_2, 8);
            *(unsigned char *)(param_1 + 0x2c) &= ~4;
        }
    } else {
        if (func_ov027_020b9f9c(param_2) == 0)
            func_ov027_020b79dc(param_1, param_2);
    }
    return r;
}
