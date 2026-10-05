#include "nitro/types.h"

typedef struct {
    u8 data[0x104];
} ResourceSlot;

typedef struct {
    u8 pad_00[0x48];
    ResourceSlot slots[6];
} EffectSet;

typedef struct {
    s32 kind;
    u8 pad_04[0x1c];
    s32 frame;
} AnimRequest;

typedef struct {
    u8 pad_000[2];
    s8 id;
    u8 pad_003[0x14d];
    AnimRequest *request;
} SlotEntry;

extern int MapStateToOddIndex(AnimRequest *request);
extern int func_0202f4cc(ResourceSlot *slot, int channel);

BOOL SlotEntry_AdvanceAnim(EffectSet *set, SlotEntry *entry, int step)
{
    AnimRequest *request = entry->request;
    int slot = MapStateToOddIndex(request);
    int length;
    int other;

    request->frame += step;
    length = func_0202f4cc(&set->slots[slot], 2);
    other = func_0202f4cc(&set->slots[slot], 0);
    if (other < length) {
        other = length;
    }
    if (request->frame > other) {
        entry->id = -1;
    }
    if (entry->id == -1) {
        return TRUE;
    }
    return FALSE;
}
