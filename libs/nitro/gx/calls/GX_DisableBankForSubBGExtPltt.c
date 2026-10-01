extern void *disableBankForX_();
extern unsigned short sGXSubBgExtPlttBank;

void *GX_DisableBankForSubBGExtPltt(void)
{
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x04001000;
    *dispcnt = *dispcnt & ~0x40000000u;
    return disableBankForX_(&sGXSubBgExtPlttBank);
}
