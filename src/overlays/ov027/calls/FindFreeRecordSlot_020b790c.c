#include "nitro/types.h"

struct Record {
    u8 pad_00[0x14];
    s32 isActive;
    u8 pad_18[0x38 - 0x18];
};

struct RecordPool {
    u8 pad_00[0xc];
    struct Record *records;
    u8 pad_10[0x30 - 0x10];
    s32 recordCount;
};

struct Record *FindFreeRecordSlot_020b790c(struct RecordPool *pool) {
    int index = 0;
    if (pool->recordCount > 0) {
        do {
            if (pool->records[index].isActive == 0) break;
            index++;
        } while (index < pool->recordCount);
    }
    return &pool->records[index];
}
