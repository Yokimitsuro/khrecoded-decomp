extern void FX_DivAsync(int x);
extern int func_01ff9d54(void);

int FX_Inv(int x) {
    FX_DivAsync(x);
    return func_01ff9d54();
}
