extern int resetBankForX_(unsigned short *state);
extern unsigned short data_02056f52;

int GX_ResetBankForTexPltt(void)
{
    return resetBankForX_(&data_02056f52);
}