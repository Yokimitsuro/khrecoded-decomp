typedef unsigned short u16;

extern u16 data_02056f48;
extern void GX_VRAMCNT_SetLCDC_(int banks);

int resetBankForX_(u16 *assignment)
{
    int banks = *assignment;

    *assignment = 0;
    data_02056f48 |= (u16)banks;
    GX_VRAMCNT_SetLCDC_(banks);
    return banks;
}