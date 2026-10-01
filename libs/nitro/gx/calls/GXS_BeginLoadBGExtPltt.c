/* Records which banks had to be released for the sub BG extended palette upload. */
extern int GX_ResetBankForSubBGExtPltt(void);
extern int gGXExtPlttLoadState[];

void GXS_BeginLoadBGExtPltt(void) {
    gGXExtPlttLoadState[0] = GX_ResetBankForSubBGExtPltt();
}
