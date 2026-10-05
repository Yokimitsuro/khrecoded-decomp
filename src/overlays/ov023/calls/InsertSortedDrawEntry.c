#include "nitro/types.h"

typedef struct DrawEntry {
    u8 pad_00[0x14];
    s32 priority;
    u8 pad_18[0x4];
    u8 subPriority;
} DrawEntry;

extern DrawEntry *NNS_FndGetNextListObject(void *list, DrawEntry *obj);
extern void NNS_FndInsertListObject(void *list, DrawEntry *before, DrawEntry *obj);
extern void NNS_FndAppendListObject(void *list, DrawEntry *obj);

void InsertSortedDrawEntry(u8 *owner, DrawEntry *entry, s32 priority, int subPriority)
{
    DrawEntry *obj = NNS_FndGetNextListObject(owner + 0x6874, NULL);

    while (obj != NULL) {
        if (obj->priority >= priority && (obj->priority != priority || obj->subPriority >= subPriority)) {
            NNS_FndInsertListObject(owner + 0x6874, obj, entry);
            break;
        }
        obj = NNS_FndGetNextListObject(owner + 0x6874, obj);
    }
    if (obj == NULL) {
        NNS_FndAppendListObject(owner + 0x6874, entry);
    }
}
