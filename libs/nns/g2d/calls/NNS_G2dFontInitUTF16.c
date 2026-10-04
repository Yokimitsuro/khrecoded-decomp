typedef unsigned short u16;
typedef u16 (*NNSiG2dSplitCharCallback)(const void **ppChar);

typedef struct NNSG2dFont {
    void *pRes;
    NNSiG2dSplitCharCallback cbCharSpliter;
} NNSG2dFont;

extern void NNSi_G2dGetUnpackedFont(void *pNftrFile, void *ppFont);
extern u16 NNSi_G2dSplitCharUTF16(const void **ppChar);

void NNS_G2dFontInitUTF16(NNSG2dFont *pFont, void *pNftrFile)
{
    NNSi_G2dGetUnpackedFont(pNftrFile, &pFont->pRes);
    pFont->cbCharSpliter = NNSi_G2dSplitCharUTF16;
}
