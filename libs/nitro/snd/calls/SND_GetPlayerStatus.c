extern void DC_InvalidateRange(void *address, unsigned int size);
extern int *data_02059780;

int SND_GetPlayerStatus(void)
{
    DC_InvalidateRange(data_02059780 + 1, 4);
    return data_02059780[1];
}