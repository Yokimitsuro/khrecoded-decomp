extern void *disableBankForX_();
extern unsigned short sGXObjExtPlttBank;

void *GX_DisableBankForOBJExtPltt(void)
{
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x04000000;
    *dispcnt = *dispcnt & ~0x80000000u;
    return disableBankForX_(&sGXObjExtPlttBank);
}
