#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u8 pad_00[0x10];
    NNSG2dTextCanvas txn;
} TextLayer;

extern int gTextTagColors[2];
extern u8 data_02056ae0[];

extern void HandleTextTag(u16 tag, NNSG2dTagCallbackInfo *info);
extern void NNSi_G2dTextCanvasDrawTaggedText(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *txt, NNSG2dTagCallback cbFunc, void *cbParam, NNSiG2dTextDirection d);

static inline NNSiG2dTextDirection GetTextDirection(const NNSG2dFont *font)
{
    NNSiG2dTextDirection dir = {0, 0};

    switch (font->pRes->pGlyph->flags) {
    case 0:
    case 7:
        dir.x = 1;
        break;
    case 1:
    case 2:
        dir.y = 1;
        break;
    case 3:
    case 4:
        dir.x = -1;
        break;
    case 5:
    case 6:
        dir.y = -1;
        break;
    }
    return dir;
}

void DrawTextColored(TextLayer *obj, int x, int y, int color, int altColor, const u16 *text)
{
    gTextTagColors[0] = color;
    gTextTagColors[1] = altColor;
    NNSi_G2dTextCanvasDrawTaggedText(&obj->txn, x, y, (u8)color, text, HandleTextTag, data_02056ae0, GetTextDirection(obj->txn.pFont));
}
