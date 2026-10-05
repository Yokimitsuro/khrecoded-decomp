#include "nitro/types.h"

typedef struct ItemDef {
    s32 handle;
    u32 category;
    u8 pad_08[0x10];
    u16 count;
} ItemDef;

typedef struct ItemSlot {
    u16 id;
    u16 used;
    s16 index;
    u8 pad_06[2];
    ItemDef *def;
} ItemSlot;

typedef struct RecordEntry {
    u16 unk_00;
    u16 unk_02 : 8;
    u16 owner : 8;
} RecordEntry;

typedef struct ItemListView {
    ItemSlot slots[0x200];
    ItemSlot records[600];
    ItemSlot *visible[0x458];
    u16 visibleCount;
    u8 initialized;
    u8 pad_4583;
    u32 categoryMask;
} ItemListView;

typedef struct SaveState {
    u8 pad_0000[0x28d4];
    s8 chapter;
    u8 pad_28d5[3];
    u8 owned[0x2c6d - 0x28d8];
    s8 equipSlots[0x2d84 - 0x2c6d];
    u16 slotHandles[16];
    u8 pad_2da4[0x2db4 - 0x2da4];
    u16 partySlots[2];
    u16 extraSlots[4];
    s32 pairStock[8];
} SaveState;

extern SaveState *data_0205fe0c;
extern ItemDef *GetRecordSlotPair0Entry(s32 index);
extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);

static inline BOOL IsKeyItemListed(int index, s8 chapter, int progress)
{
    switch (index) {
    case 0x160:
    case 0x161:
    case 0x178: case 0x179: case 0x17a: case 0x17b: case 0x17c:
    case 0x17d: case 0x17e: case 0x17f: case 0x180: case 0x181:
    case 0x182: case 0x183: case 0x184: case 0x185: case 0x186:
    case 0x19c: case 0x19d: case 0x19e: case 0x19f: case 0x1a0:
    case 0x1a1: case 0x1a2: case 0x1a3: case 0x1a4: case 0x1a5:
    case 0x1a6: case 0x1a7: case 0x1a8: case 0x1a9: case 0x1aa:
    case 0x1ab: case 0x1ac: case 0x1ad:
        return TRUE;
    case 0x164:
        return chapter == 1 && progress < 2;
    case 0x168: case 0x169: case 0x16a: case 0x16b: case 0x16c:
    case 0x16d: case 0x16e: case 0x16f: case 0x170: case 0x171:
    case 0x172: case 0x173: case 0x174: case 0x175: case 0x176:
    case 0x177:
        return chapter == 2 && progress < 2;
    case 0x188:
        return chapter == 5 && progress < 2;
    case 0x18c: case 0x18d: case 0x18e: case 0x18f: case 0x190:
    case 0x191: case 0x192: case 0x194:
        return chapter == 7 && progress < 2;
    default:
        return FALSE;
    }
}

void InitItemListEntries(ItemListView *view)
{
    SaveState *save = data_0205fe0c;
    u8 *owned = save->owned;
    s8 *equip = save->equipSlots;
    ItemSlot *slot = view->slots;
    s16 i;
    s16 j;
    int k;
    u16 handle;

    for (i = 0; i < 0x200; i++, slot++, owned++) {
        slot->def = GetRecordSlotPair0Entry(i);
        if ((i < 0 || i > 0x7f) && *owned != 0 && slot->def->count < 9999) {
            if (slot->def->category == 10) {
                s8 chapter = data_0205fe0c->chapter;
                int progress = ReadGlobalPackedBits(0x1a00, 2);
                if (!IsKeyItemListed(i, chapter, progress)) {
                    goto next;
                }
            }
            view->categoryMask |= 1 << slot->def->category;
            slot->id = *owned;
            slot->used = 0;
        }
    next:
        slot->index = -1;
    }
    for (i = 0; i < 600; i++, slot++) {
        RecordEntry *rec = GetActiveRecordEntryOrNull((u16)i);
        slot->id = 1;
        slot->used = 0;
        slot->index = i;
        if (rec != NULL) {
            slot->def = GetRecordSlotPair0Entry((u8)rec->owner);
        } else {
            slot->def = NULL;
        }
        if (rec != NULL && slot->def->count < 9999) {
            view->categoryMask |= 1 << slot->def->category;
            view->slots[slot->def->handle].id++;
        }
    }
    for (i = 0; i < 200; i++, equip++) {
        if (*equip >= 0) {
            view->slots[*equip + 0x90].used++;
        }
    }
    for (j = 0; j < 8; j++) {
        for (k = 0; k < 2; k++) {
            handle = data_0205fe0c->slotHandles[j * 2 + k];
            if (handle != 0xffff) {
                if (handle < 0x200) {
                    view->slots[handle].used += (u16)data_0205fe0c->pairStock[j];
                } else {
                    s32 owner = view->slots[handle].def->handle;
                    view->slots[handle].used++;
                    view->slots[owner].used++;
                }
            }
        }
    }
    handle = data_0205fe0c->partySlots[0];
    if (handle != 0xffff) {
        view->slots[handle].used++;
    }
    handle = data_0205fe0c->partySlots[1];
    if (handle != 0xffff) {
        view->slots[handle].used++;
    }
    for (i = 0; i < 4; i++) {
        handle = data_0205fe0c->extraSlots[i];
        if (handle != 0xffff) {
            view->slots[handle].used++;
        }
    }
    view->categoryMask |= (view->categoryMask != 0) << 11;
    view->initialized = TRUE;
}
