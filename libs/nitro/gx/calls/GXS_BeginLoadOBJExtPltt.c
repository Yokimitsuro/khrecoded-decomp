/* Records which banks had to be released for the sub OBJ extended palette upload. */
extern int GX_ResetBankForSubOBJExtPltt(void);
extern int gGXExtPlttLoadState[];

void GXS_BeginLoadOBJExtPltt(void) {
    gGXExtPlttLoadState[6] = GX_ResetBankForSubOBJExtPltt();
}
