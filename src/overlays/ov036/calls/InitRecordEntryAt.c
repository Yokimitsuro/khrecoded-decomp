#include "nitro/types.h"

typedef struct RecordPoint {
    s32 x;
    s32 y;
} RecordPoint;

typedef struct RecordEntry {
    s32 recordIndex;
    RecordPoint position;
    u32 flags;
} RecordEntry;

extern u8 *gTextWindowResourceTable;
extern int PXI_Init_0204f0c8(void *list, void *resource, int arg);
extern void func_0204f218(void *list, int index, int value);
extern void Slot_SetMode2Bit(void *list, int index, int value);
extern void IndexedRecords_SetFlag2(void *list, int index, int value);
extern void IndexedRecord_SetActive(void *list, int index);
extern void IndexedRecord_SetPair(void *list, int index, RecordPoint *position);

void InitRecordEntryAt(RecordEntry *entry, void *resource, RecordPoint *position, RecordPoint *offset)
{
    int index = PXI_Init_0204f0c8(gTextWindowResourceTable + 0x18, resource, 0);

    func_0204f218(gTextWindowResourceTable + 0x18, index, 0);
    Slot_SetMode2Bit(gTextWindowResourceTable + 0x18, index, 0);
    IndexedRecords_SetFlag2(gTextWindowResourceTable + 0x18, index, 0);
    IndexedRecord_SetActive(gTextWindowResourceTable + 0x18, index);
    entry->flags = 0;
    entry->recordIndex = index;
    entry->position.x = position->x;
    entry->position.y = position->y;
    if (offset != NULL) {
        entry->position.x += offset->x;
        entry->position.y += offset->y;
    }
    IndexedRecord_SetPair(gTextWindowResourceTable + 0x18, index, &entry->position);
}
