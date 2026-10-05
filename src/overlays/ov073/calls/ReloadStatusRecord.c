#include "nitro/types.h"

typedef struct Record Record;

typedef struct StatusRecordHolder {
    u8 pad_000[0x144];
    Record *record;
} StatusRecordHolder;

extern void ReleaseResourceWithBuffers(Record **handle, int heapTag);
extern Record *CloneRecord(Record **out, u32 id, int useTailAlloc, int heapTag);

void ReloadStatusRecord(StatusRecordHolder *holder, u32 id)
{
    if (holder->record != NULL) {
        ReleaseResourceWithBuffers(&holder->record, 0xe);
    }
    CloneRecord(&holder->record, id, 1, 0xe);
}
