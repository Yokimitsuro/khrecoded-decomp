#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct ItemLabelInfo
{
    u8 pad_00[0x40];
    const void *text;
} ItemLabelInfo;

typedef struct ItemEntry
{
    u8 pad_00[4];
    s16 recordId;
    u8 pad_06[2];
    ItemLabelInfo *info;
} ItemEntry;

typedef struct ItemStatus
{
    int value;
    u8 pad_04[2];
    s8 rank;
} ItemStatus;

typedef struct ItemSlot
{
    u8 pad_00[8];
    ItemStatus *status;
} ItemSlot;

typedef struct ItemMenu
{
    u8 pad_00[2];
    u8 hideRank;
    u8 pad_03[0x165];
    NNSG2dTextCanvas canvas;
    u8 pad_178[0x5a4c - 0x178];
    ItemSlot *slots[1];
} ItemMenu;

typedef struct RecordEntry
{
    u16 rank : 2;
} RecordEntry;

extern ItemEntry *GetItemMenuEntry(ItemMenu *menu, int index);
extern NNSG2dFont *func_ov039_020bc9cc(void);
extern int NNSi_G2dFontGetTextWidth(const NNSG2dFont *pFont, int hSpace, const void *txt);
extern void NNSi_G2dTextCanvasDrawText(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);
extern int NNS_G2dCharCanvasDrawChar(const NNSG2dCharCanvas *pCC, const NNSG2dFont *pFont, int x, int y, int cl, u16 ccode);
extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern u16 data_02055fd4[];

static inline NNSiG2dTextDirection GetTextDirection(const NNSG2dFont *font)
{
    NNSiG2dTextDirection dir = {0, 0};

    switch (font->pRes->pGlyph->flags)
    {
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

void DrawItemNameWithRank(ItemMenu *menu, int index, int x, int y, int color)
{
    ItemEntry *entry = GetItemMenuEntry(menu, index);
    NNSG2dTextCanvas *canvas = &menu->canvas;
    u32 rank = 0;
    const void *text = entry->info->text;
    int width = NNSi_G2dFontGetTextWidth(canvas->pFont, canvas->hSpace, text);
    NNSG2dFont *savedFont = canvas->pFont;

    if (width >= 0x45)
    {
        canvas->pFont = func_ov039_020bc9cc();
        width = NNSi_G2dFontGetTextWidth(canvas->pFont, canvas->hSpace, text);
    }

    NNSi_G2dTextCanvasDrawText(canvas, x, y, color, 0, text, GetTextDirection(canvas->pFont));

    if (entry->recordId >= 0)
    {
        rank = GetActiveRecordEntryOrNull((u16)entry->recordId)->rank;
    }
    else if (menu->hideRank == 0)
    {
        ItemStatus *status = menu->slots[index]->status;
        if (status->value >= 0 && status->value <= 0x7f)
        {
            rank = status->rank + 1;
        }
    }

    if (rank != 0)
    {
        NNS_G2dCharCanvasDrawChar(canvas->pCanvas, canvas->pFont, x + width, y, color == 2 ? 10 : color, data_02055fd4[rank]);
    }
    canvas->pFont = savedFont;
}
