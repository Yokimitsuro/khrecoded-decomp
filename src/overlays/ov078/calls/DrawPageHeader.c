#include "nitro/types.h"

typedef struct PageMenu {
    u8 pad_00[0xc];
    int imageA[3];
    int imageB[3];
    u8 pad_24[0x5d0 - 0x24];
    int cursor;
    int page;
} PageMenu;

typedef struct PageSlot {
    s16 recordId;
    u8 level;
    u8 colorIndex;
} PageSlot;

typedef struct PageTableEntry {
    u8 pad_00;
    u8 titleIndex;
    u8 pad_02[0xc];
    PageSlot slots[4];
} PageTableEntry;

typedef struct HeaderStyle {
    u8 pad_00[0x18];
    int titleWidth;
    u8 pad_1c[0x20];
    int labelWidth;
} HeaderStyle;

typedef struct RecordEntry {
    u8 pad_00[0x40];
    const char *name;
} RecordEntry;

extern HeaderStyle data_ov078_020c5124;
extern char data_ov078_020c51bc[];
extern char data_ov078_020c51c8[];
extern u16 data_02055fd4[];

extern PageTableEntry *GetPageTableEntry(u32 index);
extern BOOL IsGlobalPackedBitSet(int bit);
extern int ReadGlobalPackedBits(int bit, int width);
extern void *func_ov027_020ba2c8(int *view, int index);
extern RecordEntry *GetRecordSlotPair0Entry(s32 index);
extern void *OS_SNPrintf_0202e094(void *dst, unsigned int len, const char *fmt, ...);
extern void func_ov078_020c4c4c(PageMenu *menu, int line, const void *text, const void *suffix);

void DrawPageHeader(PageMenu *menu)
{
    PageTableEntry *entry = GetPageTableEntry(menu->cursor);
    int cursor = menu->cursor;
    int extra = IsGlobalPackedBitSet(cursor + 0xa01);
    int count = ReadGlobalPackedBits(cursor * 2 + 0x9f7, 2);
    u16 suffix[4];
    u16 text[50];
    PageSlot *slot;
    RecordEntry *record;

    if ((u32)(extra != 0) + count != 0) {
        int limit = ReadGlobalPackedBits(0xf38, 4);
        if (limit > 5) {
            limit = 5;
        }
        if (menu->cursor < limit) {
            goto draw;
        }
    }
    data_ov078_020c5124.titleWidth = 4;
    data_ov078_020c5124.labelWidth = 4;
    func_ov078_020c4c4c(menu, 7, func_ov027_020ba2c8(menu->imageA, 2), NULL);
    func_ov078_020c4c4c(menu, 8, func_ov027_020ba2c8(menu->imageA, 2), NULL);
    data_ov078_020c5124.titleWidth = 2;
    data_ov078_020c5124.labelWidth = 2;
    return;

draw:
    func_ov078_020c4c4c(menu, 7, func_ov027_020ba2c8(menu->imageB, entry->titleIndex), NULL);
    slot = &entry->slots[menu->page];
    record = GetRecordSlotPair0Entry(slot->recordId);
    OS_SNPrintf_0202e094(text, 0x32, data_ov078_020c51bc, record->name, data_02055fd4[slot->colorIndex]);
    text[49] = 0;
    if (slot->level != 0) {
        OS_SNPrintf_0202e094(suffix, 4, data_ov078_020c51c8, slot->level);
        suffix[3] = 0;
    } else {
        suffix[0] = 0;
    }
    func_ov078_020c4c4c(menu, 8, text, suffix);
}
