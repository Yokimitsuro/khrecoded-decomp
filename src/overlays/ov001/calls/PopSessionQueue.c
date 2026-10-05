#include "nitro/types.h"

typedef struct SessionTask SessionTask;

struct SessionTask {
    void (*run)(SessionTask *task);
};

typedef struct SessionEntry {
    u8 pad_00[0x38];
    SessionTask task;
    u8 pad_3C[5];
    s8 silent;
} SessionEntry;

typedef struct SessionQueue {
    u16 ids[8];
    s8 count;
} SessionQueue;

extern SessionQueue *data_ov001_020a0498;
extern SessionEntry *FindSceneNodeById(SessionQueue *queue, u32 id);
extern void MI_CpuMove16(const void *source, void *dest, u32 size);
extern void func_ov001_020645dc(u32 bitOffset);

void PopSessionQueue(u32 *outId)
{
    SessionQueue *queue = data_ov001_020a0498;
    u32 id = queue->ids[0];
    SessionEntry *entry;

    *outId = id;
    entry = FindSceneNodeById(queue, id);
    MI_CpuMove16(&queue->ids[1], queue->ids, 0xe);
    queue->ids[7] = 0xffff;
    queue->count--;
    if (entry->silent == 0) {
        func_ov001_020645dc(id * 2 + 0x331f);
    }
    entry->task.run(&entry->task);
}
