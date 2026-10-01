extern int CARDi_WaitAsync(void);

void CARD_WaitRomAsync(void)
{
    (void)CARDi_WaitAsync();
}
