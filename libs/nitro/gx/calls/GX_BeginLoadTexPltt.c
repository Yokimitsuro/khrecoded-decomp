/* Releases the texture-palette banks and records both the released mask and the base
 * address the slot table maps it to. */
extern int func_02008d4c(void);
extern int data_02056f28[];
extern unsigned short data_02052908[];

void GX_BeginLoadTexPltt(void) {
    int mask = func_02008d4c();
    data_02056f28[3] = mask;
    data_02056f28[2] = data_02052908[mask >> 4] << 12;
}
