extern void ReleaseResourceAndDetach(int);

void func_020353b8(int *param_1) {
    if ((*param_1 & 0x20) == 0) {
        ReleaseResourceAndDetach((int)param_1 + 4);
    }
    *param_1 |= 0x20;
}
