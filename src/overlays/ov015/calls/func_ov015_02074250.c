extern void func_ov015_020737d4(unsigned int id);
extern void func_ov015_020737c4(int state);
extern int func_ov015_02074288(void);

void func_ov015_02074250(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_ov015_020737d4(*(unsigned short *)(req + 2));
        func_ov015_020737c4(9);
        return;
    }
    if (func_ov015_02074288() != 0) {
        return;
    }
    func_ov015_020737c4(9);
}
