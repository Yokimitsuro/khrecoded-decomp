extern void FX_InvAsync(int x);
extern int FX_GetDivResult(void);

int func_01ff9cc0(int x) {
    FX_InvAsync(x);
    return FX_GetDivResult();
}
