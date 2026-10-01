extern void *resetBankForX_();
extern unsigned short sGXObjExtPlttBank;

void *GX_ResetBankForOBJExtPltt(void)
{
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x04000000;
    *dispcnt = *dispcnt & ~0x80000000u;
    return resetBankForX_(&sGXObjExtPlttBank);
}
