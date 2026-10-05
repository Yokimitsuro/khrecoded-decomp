#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapPoint {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct DrawEntry {
    u8 link[0xc];
    MapPoint pos;
    s32 priority;
    u8 pad_18[0x4];
    u8 subPriority;
    u8 pad_1D[0x3];
} DrawEntry;

typedef struct DrawList {
    u8 pad_0000[0x686c];
    s32 scratchCount;
    s32 maxLevel;
    u8 list[0xc];
    DrawEntry pool[64];
    s32 poolCapacity;
    s32 poolUsed;
    DrawEntry scratch[1];
} DrawList;

extern s32 SqrtResultRounded(void);
extern DrawEntry *NNS_FndGetNextListObject(void *list, DrawEntry *obj);
extern void NNS_FndRemoveListObject(void *list, DrawEntry *obj);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void InsertSortedDrawEntry(DrawList *owner, DrawEntry *entry, s32 priority, int subPriority);

DrawEntry *AllocDrawEntry(DrawList *owner, int unused, const MapPoint *pos, u8 subPriority)
{
    s32 distance;
    DrawEntry *entry;

    if (owner->poolCapacity == 0) {
        entry = &owner->scratch[owner->scratchCount];
        owner->scratchCount++;
    } else {
        if (owner->poolUsed < owner->poolCapacity) {
            entry = &owner->pool[owner->poolUsed];
            owner->poolUsed++;
            distance = SqrtResultRounded();
        } else {
            entry = NNS_FndGetNextListObject(owner->list, NULL);
            distance = SqrtResultRounded();
            if (distance < entry->priority) {
                entry = &owner->scratch[owner->scratchCount];
        owner->scratchCount++;
                goto fill;
            }
            NNS_FndRemoveListObject(owner->list, entry);
            MI_CpuCopy8(entry, &owner->scratch[owner->scratchCount], sizeof(DrawEntry));
            owner->scratchCount++;
        }
        InsertSortedDrawEntry(owner, entry, distance, subPriority);
    }
fill:
    entry->priority = distance;
    entry->subPriority = subPriority;
    MI_CpuCopy8(pos, &entry->pos, sizeof(MapPoint));
    return entry;
}
