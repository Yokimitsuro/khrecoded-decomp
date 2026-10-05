#include "nitro/types.h"

typedef struct RewardEntry {
    union {
        u32 kind;
        u16 eventId;
    } id;
    int type;
} RewardEntry;

typedef struct RewardQueue {
    u8 pad_000[0x60];
    RewardEntry entries[16];
    u32 timers[8];
    u32 flags[8];
    u8 count;
    u8 capacity;
    u8 pad_122[2];
    int uniqueCount;
} RewardQueue;

extern int EntryList_FindByKeyFirst(RewardQueue *queue, RewardEntry *entry);
extern u32 func_ov031_020bc730(u32 eventId);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void PlaySoundChecked(int seqArcNo, int index);

void RewardQueue_Push(RewardQueue *queue, RewardEntry *entry) {
    if (queue->count == 0) {
        queue->uniqueCount = 1;
    } else if (EntryList_FindByKeyFirst(queue, entry) == -1) {
        queue->uniqueCount++;
    }
    queue->entries[queue->count] = *entry;
    queue->timers[queue->count] = 0;
    queue->flags[queue->count] = 0;
    queue->count++;
    if (entry->type == 2) {
        func_ov031_020bc730(entry->id.eventId);
    }
    PlaySoundEffect(0x19d, 4);
    if (queue->count == queue->capacity) {
        PlaySoundChecked(0x19d, 5);
    }
}
