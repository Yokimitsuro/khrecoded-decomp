#include "nitro/types.h"

struct Record {
    u16 recordId;
    u8 pad_02[0x12];
    s32 isActive;
    u8 pad_18[0x38 - 0x18];
};

struct RecordPool {
    u8 pad_00[0xc];
    struct Record *records;
    u8 pad_10[0x30 - 0x10];
    s32 recordCount;
};

struct Record *FindActiveRecordById(struct RecordPool *pool, u32 recordId) {
    int index = 0;
    if (pool->recordCount > 0) {
        do {
            if ((pool->records[index].isActive != 0) && (recordId == pool->records[index].recordId)) break;
            index++;
        } while (index < pool->recordCount);
    }
    return &pool->records[index];
}
