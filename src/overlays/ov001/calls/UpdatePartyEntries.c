#include "nitro/types.h"

typedef struct LevelInfo {
    u8 pad_00[2];
    u16 level;
    u16 nextLevel;
} LevelInfo;

typedef struct PartyActor {
    u8 pad_000[0x1d4];
    LevelInfo *levelInfo;
    u8 pad_1d8[0xc];
    void (*onIdle)(struct PartyActor *actor);
    u8 pad_1e8[4];
    void (*onFrozen)(struct PartyActor *actor, int arg);
} PartyActor;

typedef struct PartyEntry {
    u32 unk0;
    PartyActor *actor;
    u8 motion[0x1c];
    u16 flags;
    u8 pad_26[2];
} PartyEntry;

typedef struct PartyManager {
    u32 unk0;
    PartyEntry entries[3];
    int entryCount;
    u8 pad_80[0xc];
    void *active;
    u8 pad_90[0xc];
    int frameArg;
    u8 pad_a0[0x14];
    s16 groupId;
} PartyManager;

typedef struct GroupRequest {
    u8 kind;
    u8 pad_01[0x24];
    u8 enabled;
    u8 pad_26[6];
} GroupRequest;

typedef struct ItemSlots {
    u8 pad_000[0x100];
    int count;
} ItemSlots;

typedef struct SelectionRecord {
    u8 pad_00[0x2c];
    ItemSlots items;
} SelectionRecord;

extern PartyManager *data_ov001_020a04bc;
extern void UpdateFieldButton(void *motion);
extern void WakeNearbyIdleNodes(s8 target);
extern void UpdateAllTrackedProbes(int arg);
extern int ApplyPendingLevelUps(void);
extern void ResetAnimationTrackState(GroupRequest *request);
extern int IsGroupMemberActive(int groupId, int index);
extern int func_ov021_020a8cc0(GroupRequest *request, int groupId);
extern void RestartEntrySlot(int groupId, int index, int a, int b);
extern void FlushHudWidgetAndSetState(u8 value, u16 level, u16 nextLevel);
extern BOOL func_ov001_0206e2d0(void);
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern int AddSlotItemUses(int order);
extern void func_ov001_020784a4(u16 id, u16 uses);

void UpdatePartyEntries(int arg)
{
    PartyManager *manager = data_ov001_020a04bc;
    PartyManager *current;
    PartyEntry *entry;
    PartyActor *actor;
    GroupRequest request;
    ItemSlots *items;
    int amount;
    int i;

    if (manager == NULL || manager->active == NULL) {
        return;
    }
    manager->frameArg = arg;
    for (i = 0; i < manager->entryCount; i++) {
        entry = &data_ov001_020a04bc->entries[i];
        if ((entry->flags & 4) > 0) {
            actor = entry->actor;
            if (actor != NULL && actor->onFrozen != NULL) {
                actor->onFrozen(actor, arg);
            }
        } else {
            if ((entry->flags & 0x10) <= 0 && (entry->flags & 0x20) <= 0) {
                UpdateFieldButton(entry->motion);
            }
            WakeNearbyIdleNodes(i);
            actor = entry->actor;
            if (actor != NULL && actor->onIdle != NULL) {
                actor->onIdle(actor);
            }
        }
    }
    UpdateAllTrackedProbes(arg);
    current = data_ov001_020a04bc;
    if ((current->entries[0].flags & 0x14) > 0) {
        return;
    }
    if (current->entries[0].actor != NULL && (amount = ApplyPendingLevelUps()) > 0) {
        ResetAnimationTrackState(&request);
        request.kind = 0;
        request.enabled = 1;
        if (IsGroupMemberActive(manager->groupId, 0) == 0) {
            func_ov021_020a8cc0(&request, manager->groupId);
        } else {
            RestartEntrySlot(manager->groupId, 0, -1, -1);
        }
        FlushHudWidgetAndSetState(amount, current->entries[0].actor->levelInfo->nextLevel,
                                           current->entries[0].actor->levelInfo->level);
    }
    if (func_ov001_0206e2d0()) {
        i = 0;
        items = &GetOverlaySelectionRecord(0)->items;
        for (; i < items->count; i++) {
            amount = AddSlotItemUses(i);
            if (amount > 0) {
                func_ov001_020784a4(i, amount);
            }
        }
    }
}
