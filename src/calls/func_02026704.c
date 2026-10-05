extern int IsCachedSeqPlaying(void);
extern void SetSelectionIfChanged(unsigned a);
extern unsigned char data_02055e00;

int func_02026704(int param_1, int param_2) {
    if (IsCachedSeqPlaying() == 0) {
        data_02055e00 = param_2;
        SetSelectionIfChanged(param_2 & 0xff);
        return 1;
    }
    return 0;
}
