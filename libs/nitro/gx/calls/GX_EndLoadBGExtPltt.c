extern void MI_WaitDma(int channel);
extern void GX_SetBankForBGExtPltt(int banks);
extern int data_02055c1c[];
extern int data_02056f0c[];

void GX_EndLoadBGExtPltt(void)
{
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForBGExtPltt(data_02056f0c[5]);
    data_02056f0c[5] = 0;
    data_02056f0c[4] = 0;
    data_02056f0c[3] = 0;
}
