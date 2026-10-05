#include "nitro/types.h"

typedef struct SpriteSlot {
    u8 pad_00[4];
    u16 width;
    u16 height;
    u32 flags;
    u8 pad_0c[0x18];
    u8 priority;
    u8 pad_25[3];
    s16 offsetX;
    u8 pad_2a[2];
    int key;
} SpriteSlot;

typedef struct ButtonPanel {
    SpriteSlot buttons[4];
    SpriteSlot frame;
    SpriteSlot cursor;
    u8 pad_120[4];
    s32 selected;
    s32 timer;
} ButtonPanel;

typedef struct OffsetTable {
    s32 values[4];
} OffsetTable;

extern const OffsetTable data_ov001_0209dab4;
extern int NestedPointer_GetFirstWord(void *objectBase, int recordIndex, int entryIndex);
extern void SetSlotKeyAndRebind(SpriteSlot *slot, int key, int flags);

void InitButtonPanelSprites(ButtonPanel *panel, void *cells)
{
    OffsetTable offsets;
    int i;
    SpriteSlot *slot;

    offsets = data_ov001_0209dab4;
    for (i = 0; i < 4; i++) {
        slot = &panel->buttons[i];
        SetSlotKeyAndRebind(slot, NestedPointer_GetFirstWord(cells, 7, 2), 0);
        slot->width = 0x10;
        slot->priority = 0x3e;
        slot->offsetX = offsets.values[i];
    }
    SetSlotKeyAndRebind(&panel->frame, NestedPointer_GetFirstWord(cells, 7, 3), 0);
    panel->frame.width = 0x10;
    panel->frame.height = 0x10;
    panel->frame.flags |= 0xf0000;
    panel->frame.priority = 0x3d;
    SetSlotKeyAndRebind(&panel->cursor, NestedPointer_GetFirstWord(cells, 7, 4), 0);
    panel->cursor.priority = 0x3d;
    panel->selected = 0;
    panel->timer = 0;
}
