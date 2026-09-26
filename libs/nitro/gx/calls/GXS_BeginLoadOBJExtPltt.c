/* Records which banks had to be released for the sub OBJ extended palette upload. */
extern int GX_DisableBankForSubOBJExtPltt(void);
extern int data_02056f0c[];

void GXS_BeginLoadOBJExtPltt(void) {
    data_02056f0c[6] = GX_DisableBankForSubOBJExtPltt();
}
