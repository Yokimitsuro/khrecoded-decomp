extern void *resetBankForX_();
extern unsigned short sGXSubObjExtPlttBank;

void *GX_ResetBankForSubOBJExtPltt(void)
{
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x04001000;
    *dispcnt = *dispcnt & ~0x80000000u;
    return resetBankForX_(&sGXSubObjExtPlttBank);
}
