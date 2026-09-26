extern int data_ov001_020a0528;
extern int func_ov001_0206dc98();

void func_ov001_020992f4(void) {
    int p = *(int *)&data_ov001_020a0528;
    if (p != 0) {
        func_ov001_0206dc98(p);
    }
}
