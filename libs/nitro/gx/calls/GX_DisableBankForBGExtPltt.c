extern void *disableBankForX_();
extern unsigned short sGXBgExtPlttBank;

void *GX_DisableBankForBGExtPltt(void)
{
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x04000000;
    *dispcnt = *dispcnt & ~0x40000000u;
    return disableBankForX_(&sGXBgExtPlttBank);
}
