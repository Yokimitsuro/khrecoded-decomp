extern void MI_WaitDma(int channel);
extern void GX_SetBankForBGExtPltt(int banks);
extern int GXi_DmaId[];
extern int data_02056f0c[];

void GX_EndLoadBGExtPltt(void)
{
    if (GXi_DmaId[0] != -1) {
        MI_WaitDma(GXi_DmaId[0]);
    }
    GX_SetBankForBGExtPltt(data_02056f0c[5]);
    data_02056f0c[5] = 0;
    data_02056f0c[4] = 0;
    data_02056f0c[3] = 0;
}
