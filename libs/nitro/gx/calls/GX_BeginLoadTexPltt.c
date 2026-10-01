/* Releases the texture-palette banks and records both the released mask and the base
 * address the slot table maps it to. */
extern int GX_ResetBankForTexPltt(void);
extern int gGXTextureLoadState[];
extern unsigned short data_02052908[];

void GX_BeginLoadTexPltt(void) {
    int mask = GX_ResetBankForTexPltt();
    gGXTextureLoadState[3] = mask;
    gGXTextureLoadState[2] = data_02052908[mask >> 4] << 12;
}
