extern void FX_InvAsync(int x);
extern int func_01ff9d54(void);

int func_01ff9cc0(int x) {
    FX_InvAsync(x);
    return func_01ff9d54();
}
