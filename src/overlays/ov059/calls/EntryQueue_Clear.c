#include "nitro/types.h"

typedef struct EntryQueue {
    u8 pad_000[0x120];
    u8 count;
    u8 capacity;
} EntryQueue;

void EntryQueue_Clear(EntryQueue *queue)
{
    queue->count = 0;
}
