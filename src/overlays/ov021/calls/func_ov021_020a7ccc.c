extern void ZeroHalfThenFree();
extern int data_ov021_020b5624;

void func_ov021_020a7ccc(void) {
    if (data_ov021_020b5624 != 0) {
        ZeroHalfThenFree(data_ov021_020b5624);
    }
    data_ov021_020b5624 = 0;
}
