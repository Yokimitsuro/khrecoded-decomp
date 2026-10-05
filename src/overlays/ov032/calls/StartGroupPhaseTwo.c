#include "nitro/types.h"

typedef struct {
    u32 pad_bits : 18;
    u32 phase : 5;
    u32 targetPhase : 5;
    u32 high : 4;
    u8 pad_04[4];
    u32 active : 1;
} GroupEntry;

typedef struct {
    u8 pad_00[2];
    s8 slot;
    u8 pad_03;
    s16 target;
} MemberState;

typedef struct {
    u8 pad_00[0xc4];
    int busy;
} GroupOwner;

typedef struct {
    u8 pad_00[4];
    GroupOwner *owner;
} Group;

extern MemberState *func_ov032_020bbc98(void *group);
extern GroupEntry *func_ov032_020bbc80(void *group);
extern void QueueFieldObjectModeChange(GroupOwner *owner, int index, int arg);
extern void SetGroupFormation(void *group, int state);

void StartGroupPhaseTwo(Group *group)
{
    MemberState *state = func_ov032_020bbc98(group);
    GroupEntry *entry = func_ov032_020bbc80(group);

    if (state->target == -1 && group->owner->busy == 0) {
        entry->active = 1;
        QueueFieldObjectModeChange(group->owner, state->slot, 1);
        entry->targetPhase = 2;
        entry->phase = entry->targetPhase;
        SetGroupFormation(group, 5);
    }
}
