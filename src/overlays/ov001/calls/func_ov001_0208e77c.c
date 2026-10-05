extern int func_02025df8(void *p);
extern void ScriptCmd_ReturnValue(void *p, int x);
extern void func_ov001_02088a6c(void);

int func_ov001_0208e77c(void *arg0) {
    int r = func_02025df8(arg0);
    ScriptCmd_ReturnValue(arg0, r);
    func_ov001_02088a6c();
    return 1;
}
