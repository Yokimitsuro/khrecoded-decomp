extern void MI_WaitDma(int channel);
extern void GX_SetBankForSubBGExtPltt(int banks);
extern int GXi_DmaId[];
extern int gGXExtPlttLoadState[];

void GXS_EndLoadBGExtPltt(void)
{
    if (GXi_DmaId[0] != -1) {
        MI_WaitDma(GXi_DmaId[0]);
    }
    GX_SetBankForSubBGExtPltt(gGXExtPlttLoadState[0]);
    gGXExtPlttLoadState[0] = 0;
}