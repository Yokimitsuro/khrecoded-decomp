#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct ScreenState {
    u8 pad_000[0xb8];
    TextLayer textLayers[2];
    u8 pad_120[0x150 - 0x120];
    StringTable strings;
} ScreenState;

extern u16 *func_ov027_020ba2c8(StringTable *table, int index);
extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, int flags, const u16 *text);

void DrawTableString(ScreenState *screen, int x, int y, int stringIndex) {
    DrawTextAnchored(&screen->textLayers[0], x, y, 6, 8, func_ov027_020ba2c8(&screen->strings, stringIndex));
}
