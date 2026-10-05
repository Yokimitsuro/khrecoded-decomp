extern void WH_SetError(unsigned int id);
extern int func_ov015_02073d1c(void);
extern void func_ov015_02074e80(void);

void func_ov015_02073cec(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        WH_SetError(*(unsigned short *)(req + 2));
        func_ov015_02074e80();
        return;
    }
    if (func_ov015_02073d1c() != 0) {
        return;
    }
    func_ov015_02074e80();
}
