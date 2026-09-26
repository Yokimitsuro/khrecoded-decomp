extern int func_02008aac();
extern int GX_SetBankForSubOBJ();

void func_020299a8(void) {
    volatile unsigned int *p;

    func_02008aac(0x180);
    GX_SetBankForSubOBJ(8);
    p = (volatile unsigned int *)0x04001000;
    *p = (*p & 0xffcfffefu) | 0x10u | 0x200000u;
}
