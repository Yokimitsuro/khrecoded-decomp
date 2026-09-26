extern int func_02025df8(int ctx, void *arg);
extern int func_02025e0c(int ctx, void *arg);
extern int func_02025974(int ctx, int arg);

extern char *func_02036254(int index);
extern void func_01ffb2f8(void *p, int slot, int value);

int func_ov001_0208df2c(int ctx, int args) {
    int entity = func_02025df8(ctx, (void *)args);
    int slot = func_02025df8(ctx, (void *)(args + 8));
    int value = func_02025e0c(ctx, (void *)(args + 0x10));
    func_01ffb2f8(func_02036254((unsigned short)func_02025974(ctx, entity)) + 4,
                  (unsigned short)slot, value);
    return 1;
}
