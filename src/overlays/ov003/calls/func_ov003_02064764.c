extern int ByteCode_ResolveOperand(void *a, void *b);
extern void MovieScene_StartStream(int x);

int func_ov003_02064764(void *arg1, char *arg2) {
    int v = 0;
    if (*(short *)(arg2 + 0) == 2) {
        v = ByteCode_ResolveOperand(arg1, arg2);
    }
    if (*(short *)(arg2 + 8) == 2) {
        ByteCode_ResolveOperand(arg1, arg2 + 8);
    }
    if (*(short *)(arg2 + 0x10) == 2) {
        ByteCode_ResolveOperand(arg1, arg2 + 0x10);
    }
    MovieScene_StartStream(v);
    return 1;
}
