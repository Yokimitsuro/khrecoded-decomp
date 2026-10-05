#include "nitro/types.h"

typedef struct Record {
    u16 id;
    s16 originX;
    s16 originY;
    u16 width;
    u16 height;
    s16 offsetX;
    s16 offsetY;
    u8 pad_0E[2];
    int userData;
    int isActive;
    u32 attr;
    u8 pad_1C[0x1C];
} Record;

typedef struct RecordPool RecordPool;

extern Record *FindFreeRecordSlot_020b790c(RecordPool *pool);

void AddRecordFromTemplate(RecordPool *pool, const Record *source, u16 id, int userData)
{
    Record *record = FindFreeRecordSlot_020b790c(pool);

    record->id = id;
    record->originX = source->originX;
    record->originY = source->originY;
    record->width = source->width;
    record->height = source->height;
    record->offsetX = source->offsetX;
    record->offsetY = source->offsetY;
    record->userData = userData;
    record->attr = source->attr;
    record->isActive = 1;
}
