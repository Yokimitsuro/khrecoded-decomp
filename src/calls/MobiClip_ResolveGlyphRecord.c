extern unsigned short NNS_G2dFontFindGlyphIndex(void *ptr, unsigned int value);
extern void *NNS_G2dFontGetCharWidthsFromIndex(void *ptr, int value);

void MobiClip_ResolveGlyphRecord(int *ptr, int *out, unsigned int value) {
    int *inner = (int *)ptr[0];
    int index = NNS_G2dFontFindGlyphIndex(inner, value);
    unsigned char *data;

    if (index == 0xffff) {
        index = *(unsigned short *)(inner[0] + 2);
    }

    out[0] = (int)NNS_G2dFontGetCharWidthsFromIndex(inner, index);
    data = *(unsigned char **)(inner[0] + 8);
    out[1] = (int)(data + 8 + index * *(unsigned short *)(data + 2));
}
