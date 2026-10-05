#include "nitro/types.h"

typedef struct TagRecord {
    u16 id;
    s16 tagCount;
    u16 frame;
    u8 pad_06[2];
    int userParam;
    u64 frameTicks;
    s64 elapsed;
    u8 pad_1C[8];
    u8 active : 1;
    u8 armed : 1;
    u8 pad_25[3];
    int nextFrame;
    void **tags;
} TagRecord;

extern TagRecord *func_ov027_020b7954(void *tracker);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *FindActiveRecordById(void *tracker, u32 recordId);

TagRecord *CreateTagRecord(void *tracker, u16 id, u16 *tagIds, int tagCount, int userParam, u64 frameMs)
{
    int i;
    TagRecord *record = func_ov027_020b7954(tracker);

    i = 0;
    MI_CpuFill8(record, 0, sizeof(TagRecord));
    record->id = id;
    record->tagCount = tagCount;
    record->frame = 0;
    record->userParam = userParam;
    record->frameTicks = (33514ULL * frameMs) / 64;
    record->elapsed = 0;
    record->tags = NNSi_FndAllocFromDefaultHeap(tagCount << 2);
    record->armed = 1;
    record->nextFrame = 0x7FFFFFFF;
    for (; i < tagCount; i++) {
        record->tags[i] = FindActiveRecordById(tracker, tagIds[i]);
    }
    return record;
}
