extern void MI_WaitDma(int channel);
extern void GX_SetBankForBGExtPltt(int banks);
extern int GXi_DmaId[];
extern int gGXExtPlttLoadState[];

void GX_EndLoadBGExtPltt(void)
{
    if (GXi_DmaId[0] != -1) {
        MI_WaitDma(GXi_DmaId[0]);
    }
    GX_SetBankForBGExtPltt(gGXExtPlttLoadState[5]);
    gGXExtPlttLoadState[5] = 0;
    gGXExtPlttLoadState[4] = 0;
    gGXExtPlttLoadState[3] = 0;
}
