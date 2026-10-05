#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TextLayer TextLayer;

typedef struct {
    u8 align;
    u8 highlight;
    u16 pad_02;
    u16 *text;
} EntryTableItem;

typedef struct {
    u32 count;
    EntryTableItem entries[1];
} EntryTable;

typedef struct {
    u8 pad_00[0x1c];
    u8 textLayer[0x84 - 0x1c];
    u8 tileBuffer[0x10938 - 0x84];
    fx32 lineAccum;
    u32 lineIndex;
} ScrollScreen;

typedef struct {
    u8 pad_00[0x14];
    ScrollScreen screens[2];
    u8 pad_21294[0x23aac - 0x21294];
    fx32 rollPosition;
    fx32 lastRollPosition;
    u8 pad_23ab4[0x3033c - 0x23ab4];
    EntryTable *table;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;

extern int RoundFx32ToInt(fx32 value);
extern void ClearTextArea(void *layer, int color, int x, int y, int width, int height);
extern int func_ov004_02062d78(u16 *text, int mode);
extern void func_ov004_02062b70(const u16 *text, int align, int y, int screenIndex, int fontIndex,
                                        int highlight);
extern void Text_UploadTileBuffer(void *layer);
extern int NNS_GfdRegisterNewVramTransferTask(u32 command, u32 offset, void *data, u32 size);

void FeedScrollTextLine(int screenIndex)
{
    ScrollScreen *screen = &data_ov004_020645a0.work->screens[screenIndex];
    EntryTableItem *entries = data_ov004_020645a0.work->table->entries;
    int top = RoundFx32ToInt(data_ov004_020645a0.work->rollPosition) + 0xd0;
    u16 *text;
    int bracket;
    int highlight;
    int y;
    int align;
    int height;
    int wrap;

    if (top < 0) {
        return;
    }
    if (screen->lineIndex == data_ov004_020645a0.work->table->count) {
        return;
    }
    screen->lineAccum -= 0x1a10;
    y = (top - (RoundFx32ToInt(data_ov004_020645a0.work->rollPosition) -
                RoundFx32ToInt(data_ov004_020645a0.work->lastRollPosition)) - 1) & 0xff;
    if (screen->lineAccum > 0) {
        return;
    }
    align = entries[screen->lineIndex].align;
    text = entries[screen->lineIndex].text;
    highlight = entries[screen->lineIndex].highlight;
    if (y <= 0xf1) {
        ClearTextArea(screen->textLayer, 0, 0, y, 0xb8, 15);
    } else {
        ClearTextArea(screen->textLayer, 0, 0, y, 0xb8, 0x100 - y);
        ClearTextArea(screen->textLayer, 0, 0, 0, 0xb8, 15 - (0x100 - y));
    }
    bracket = func_ov004_02062d78(text, align);
    if (text != NULL) {
        height = 11;
        if (bracket == 0) {
            height = 14;
        }
    } else {
        height = 8;
    }
    if (y <= 0x100 - height) {
        if (text != NULL) {
            func_ov004_02062b70(text, align, y, screenIndex, bracket, highlight);
        }
    } else {
        wrap = 0x100 - y;
        if (text != NULL) {
            func_ov004_02062b70(text, align, y, screenIndex, bracket, highlight);
            if (text[0] != 0x3e) {
                func_ov004_02062b70(text, align, -wrap, screenIndex, bracket, highlight);
            }
        }
    }
    screen->lineAccum += height << 12;
    screen->lineIndex++;
    Text_UploadTileBuffer(screen->textLayer);
    NNS_GfdRegisterNewVramTransferTask(screenIndex == 0 ? 9 : 0x19, 0, screen->tileBuffer, 0x800);
}
