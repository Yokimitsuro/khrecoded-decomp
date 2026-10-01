/* Records which banks had to be released for the sub BG extended palette upload. */
extern int GX_ResetBankForSubBGExtPltt(void);
extern int data_02056f0c[];

void GXS_BeginLoadBGExtPltt(void) {
    data_02056f0c[0] = GX_ResetBankForSubBGExtPltt();
}
