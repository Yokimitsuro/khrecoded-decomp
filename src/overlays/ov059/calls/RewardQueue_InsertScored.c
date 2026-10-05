#include "nitro/types.h"

typedef struct {
    union {
        u32 kind;
        u16 eventId;
    } id;
    int type;
} RewardEntry;

typedef struct {
    u8 pad_000[0x60];
    RewardEntry entries[16];
    u32 timers[8];
    u32 flags[8];
    u8 count;
    u8 capacity;
} RewardQueue;

typedef struct {
    u8 pad_00[0x90];
    RewardQueue queue;
} RewardOwner;

extern void RewardQueue_Push(RewardQueue *queue, const RewardEntry *entry);
extern BOOL func_ov059_020cf3b4(RewardQueue *queue, const RewardEntry *entry);

void RewardQueue_InsertScored(const RewardEntry *entry, int score, RewardOwner *owner, RewardEntry *entries, int *scores, int *count)
{
    int slot;

    if (owner->queue.count == owner->queue.capacity) {
        int i;
        int lowest = score;
        for (i = 0; i < *count; i++) {
            if (lowest > scores[i]) {
                lowest = scores[i];
                slot = i;
            }
        }
        if (lowest == score) {
            return;
        }
        func_ov059_020cf3b4(&owner->queue, &entries[slot]);
    } else {
        slot = (*count)++;
    }
    RewardQueue_Push(&owner->queue, entry);
    entries[slot] = *entry;
    scores[slot] = score;
}
