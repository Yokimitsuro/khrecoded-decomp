extern int NNS_G2dGetAnimCtrlCurrentFrame(void *p);

int func_0204f23c(char *arg0, int arg1) {
    if (arg1 < 0) {
        return 0;
    }
    return NNS_G2dGetAnimCtrlCurrentFrame(arg0 + 0x18 + arg1 * 0x8c);
}
