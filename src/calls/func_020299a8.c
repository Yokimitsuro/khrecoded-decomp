extern void GX_SetBankForSubBG(int banks);
extern void GX_SetBankForSubOBJ(int banks);

void func_020299a8(void) {
    volatile unsigned int *p;

    GX_SetBankForSubBG(0x180);
    GX_SetBankForSubOBJ(8);
    p = (volatile unsigned int *)0x04001000;
    *p = (*p & 0xffcfffefu) | 0x10u | 0x200000u;
}
