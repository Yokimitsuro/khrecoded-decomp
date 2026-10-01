extern int resetBankForX_(unsigned short *state);
extern unsigned short data_02056f50;

int GX_ResetBankForTex(void)
{
    return resetBankForX_(&data_02056f50);
}