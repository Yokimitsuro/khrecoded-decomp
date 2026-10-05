#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    const u16 *name;
    u8 pad_44[4];
} RecordEntry;

typedef struct {
    u8 pad_000[0xc];
    u8 textLayer[0x160];
    BOOL goalReached;
} Ov086Menu;

extern void *func_ov027_020ba2c8(Ov086Menu *menu, int messageId);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const void *text);
extern int ReadSessionPackedBits(int bitIndex, int bitCount);
extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);
extern RecordEntry *GetRecordSlotPair0Entry(s32 index);
extern const u16 sOv086_Empty_020c2fe4[];
extern const char data_ov086_020c2fe8[];

void DrawCounterGoalText(Ov086Menu *menu)
{
    char buffer[0x20];
    int value;
    const u16 *name;
    int color;

    DrawTextAnchored(menu->textLayer, 0x38, 0x12, 6, 0x209, func_ov027_020ba2c8(menu, 0x16));
    DrawTextAnchored(menu->textLayer, 0x6f, 0x12, 4, 0x209, sOv086_Empty_020c2fe4);
    value = ReadSessionPackedBits(0xe2a, 0x14);
    OS_SNPrintf_0202e094(buffer, 0x10, data_ov086_020c2fe8, value);
    DrawTextAnchored(menu->textLayer, 0xa0, 0x12, 2, 0x821, buffer);
    color = 2;
    name = GetRecordSlotPair0Entry(0x161)->name;
    DrawTextAnchored(menu->textLayer, 0x27, 0x33, 1, 0x209, name);
    if (value < 40000) {
        color = 4;
    }
    DrawTextAnchored(menu->textLayer, 0x26, 0x32, color, 0x209, name);
    if (value >= 40000) {
        menu->goalReached = TRUE;
    }
}
