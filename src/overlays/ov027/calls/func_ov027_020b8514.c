extern void func_ov027_020b8208(int owner, int entry, unsigned short a, unsigned short b);
extern void func_ov027_020b8230(int owner, int entry);

void func_ov027_020b8514(int param_1, int param_2, unsigned short param_3, unsigned short param_4) {
    int i = 0;
    int n = *(unsigned short *)(param_2 + 2);
    if (n > 0) {
        do {
            func_ov027_020b8208(param_1, (*(int **)(param_2 + 0x2c))[i], param_3, param_4);
            i = i + 1;
        } while (i < (int)*(unsigned short *)(param_2 + 2));
    }
    func_ov027_020b8230(param_1,
        *(int *)(*(int *)(param_2 + 0x2c) + *(unsigned short *)(param_2 + 4) * 4));
}
