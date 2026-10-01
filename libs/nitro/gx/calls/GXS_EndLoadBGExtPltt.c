extern void MI_WaitDma(int channel);
extern void GX_SetBankForSubBGExtPltt(int banks);
extern int GXi_DmaId[];
extern int data_02056f0c[];

void GXS_EndLoadBGExtPltt(void)
{
    if (GXi_DmaId[0] != -1) {
        MI_WaitDma(GXi_DmaId[0]);
    }
    GX_SetBankForSubBGExtPltt(data_02056f0c[0]);
    data_02056f0c[0] = 0;
}