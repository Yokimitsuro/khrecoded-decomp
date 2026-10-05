#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotEntry {
    u32 inUse;
    VecFx32 position;
} SlotEntry;

typedef struct SlotTable {
    u32 count;
    SlotEntry *entries;
} SlotTable;

extern void SyncStageEntryPosition(int index, VecFx32 *out);
extern SlotEntry *SlotTable_GetEntry(SlotTable *table, int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);

int SlotTable_FindNearestFree(SlotTable *table, fx32 height, int heightSign, int distanceSign)
{
    fx32 bestDistance = 0;
    int best = -1;
    VecFx32 origin;
    VecFx32 delta;
    u32 i;

    SyncStageEntryPosition(1, &origin);
    for (i = 0; i < table->count; i++) {
        SlotEntry *entry = SlotTable_GetEntry(table, i);
        fx32 distance;

        if (entry == NULL) {
            break;
        }
        if (entry->inUse) {
            continue;
        }
        if (heightSign > 0 && entry->position.y < height) {
            continue;
        }
        if (heightSign < 0 && entry->position.y > height) {
            continue;
        }
        VEC_Subtract(&origin, &entry->position, &delta);
        delta.y = 0;
        distance = VEC_Mag(&delta);
        if (best >= 0) {
            if (distanceSign > 0 && distance < bestDistance) {
                continue;
            }
            if (distanceSign < 0 && distance > bestDistance) {
                continue;
            }
        }
        best = i;
        bestDistance = distance;
    }
    return best;
}
