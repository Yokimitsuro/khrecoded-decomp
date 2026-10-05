#include "nitro/types.h"

typedef struct PendingPair {
    int first;
    int second;
} PendingPair;

typedef struct PendingQueue {
    u8 pad_00[3];
    u8 count;
    u8 pad_04[0xc];
    PendingPair entries[1];
} PendingQueue;

extern PendingQueue *func_ov039_020bc650(void);

void PushPendingPair(int first, int second)
{
    PendingQueue *queue = func_ov039_020bc650();

    queue->entries[queue->count].first = first;
    queue->entries[queue->count].second = second;
    queue->count++;
}