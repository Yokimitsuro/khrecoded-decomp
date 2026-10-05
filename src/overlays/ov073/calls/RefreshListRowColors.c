#include "nitro/types.h"

typedef struct RowEntry {
    u16 value;
    u16 y;
    u32 unk_4;
} RowEntry;

typedef struct RowTable {
    u8 pad_00[8];
    RowEntry entries[1];
} RowTable;

typedef struct RowList {
    u8 pad_00[4];
    RowTable *table;
} RowList;

typedef struct SlotRecord {
    u8 pad_00[0xc];
    u16 colorCount;
    u16 colorIndices[1];
} SlotRecord;

typedef struct SlotPanel {
    u8 pad_00[4];
    RowList *rows;
    int subScreen;
    u8 pad_0c[4];
    u16 palette[0x30];
    SlotRecord *slots[3];
    u8 pad_7c[0x28];
    int selectedIndex;
} SlotPanel;

extern void MIi_CpuClear16(u16 value, void *dest, u32 size);
extern void UploadListPalette(SlotPanel *panel, BOOL immediate);

void RefreshListRowColors(SlotPanel *panel)
{
    RowTable *table = panel->rows->table;
    int i;
    int j;
    int currentRow;
    SlotRecord *slot;

    MIi_CpuClear16(0x2d6b, panel->palette, sizeof(panel->palette));
    currentRow = (table->entries[panel->selectedIndex].y - 2) / 16;
    for (i = 0; i < 3; i++) {
        slot = panel->slots[i];
        if (slot == NULL) {
            break;
        }
        for (j = 0; j < slot->colorCount; j++) {
            panel->palette[slot->colorIndices[j] - 0x50] = (i < currentRow) ? 0x3bf : 0x628c;
        }
    }
    UploadListPalette(panel, panel->subScreen == 0);
}
