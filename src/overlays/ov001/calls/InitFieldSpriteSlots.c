#include "nitro/types.h"

typedef struct SlotOrder {
    int index[4];
} SlotOrder;

typedef struct SlotPair {
    u32 first;
    u32 second;
} SlotPair;

typedef struct SlotBlock {
    u8 pad[0x10];
    SlotPair pair;
} SlotBlock;

typedef struct SlotEntry {
    u32 value;
    u8 pad[0x10];
} SlotEntry;

typedef struct SlotSet {
    u32 unk0;
    u32 blocks[4];
    SlotBlock *extra;
    u8 pad18[0xc];
    SlotEntry entries[6];
    u32 unk9c;
    u32 unkA0;
    u32 scale;
    u16 selection;
} SlotSet;

extern SlotOrder data_ov001_0209e068;
extern SlotPair data_ov001_0209e048;
extern u32 func_ov001_0206dc20(void);

void InitFieldSpriteSlots(SlotSet *set, BOOL useBlocks)
{
    u32 base = func_ov001_0206dc20();
    SlotOrder order = data_ov001_0209e068;
    SlotPair pair = data_ov001_0209e048;
    int i;

    if (base != 0) {
        i = 0;
        set->unk9c = 0;
        set->selection = 0xffff;
        set->scale = 0x3000;
        if (useBlocks) {
            do {
                set->blocks[i] = base + order.index[i] * 0x30;
                i++;
            } while (i < 4);
            set->extra = (SlotBlock *)(base + 0xc0);
        } else {
            do {
                set->entries[i].value = 0;
                i++;
            } while (i < 6);
        }
        set->extra->pair = pair;
    }
}
