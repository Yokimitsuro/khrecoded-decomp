extern void PanelState_NoOpB(void *p);
extern int func_ov022_020a9450(int *ctx, int cursor, unsigned int a);

int initializeMovieStreamWrapper(int *ctx, int cursor, unsigned int a) {
    PanelState_NoOpB((void *)0x02000bc4);
    return func_ov022_020a9450(ctx, cursor, a);
}
