#include "nitro/types.h"

typedef struct StageEntry {
    u8 pad_00[4];
    void *resource;
} StageEntry;

typedef struct SectionElement {
    u8 pad_00[4];
    int nodeIndex;
    u8 isLarge;
    u8 pad_09[2];
    u8 isHidden;
    u8 pad_0c[0xc];
    u8 variant;
} SectionElement;

typedef struct StageActor {
    u8 pad_000[0x288];
    u16 role : 2;
    u16 roleFlags : 14;
    u8 pad_28a[0x126];
    s16 parentId;
    u16 nextId;
} StageActor;

typedef struct StageManager {
    u8 pad_00000[0x18da0];
    u8 spawnCounts[0x40];
} StageManager;

typedef struct Spawner {
    s32 state;
    u16 active : 1;
    u16 flag1 : 3;
    u16 hidden : 1;
    u16 flag5 : 1;
    u16 large : 1;
    u16 flag7 : 9;
    u8 pad_06[3];
    u8 variant;
    u8 pad_0a[6];
    u16 busy;
    u8 pad_12[2];
    s16 entryId;
    u16 slotA;
    u16 slotB;
    u16 recordIndex;
    u8 pad_1c[0x184];
    u32 nextTime;
    u8 pad_1a4[0xc];
    s32 timer;
    u8 pad_1b4[8];
    s16 leaderId;
} Spawner;

extern StageEntry *GetStageEntry(int id);
extern void func_ov001_020931b0(Spawner *spawner);
extern void ScheduleSpawnerNextTime(Spawner *spawner, int delay);
extern u32 random_next_scaled(u32 range);
extern SectionElement *GetResourceSectionElement(StageEntry *entry, int section, int index);
extern u16 ReleaseStageSlot(int kind);
extern void *GetSmallTableEntry(int index);
extern int GetOwnerTableEntryValue(StageEntry *entry, int section);
extern int func_ov001_02095120(Spawner *spawner, StageEntry *entry, int index, int arg);
extern StageActor *GetStageActor(int id);
extern s32 func_ov001_0208f040(void *resource, int index);
extern void AttachActorToStageNode(StageActor *actor, int parentId, int node, int mode);
extern void func_ov001_02093358(Spawner *spawner);
extern void func_ov001_020925e4(Spawner *spawner, int state);
extern StageManager *func_ov001_0209c3e8(void);

void SpawnStageGroup(Spawner *spawner, int unused1, int unused2, int arg)
{
    StageEntry *entry;
    StageActor *actor;
    u16 count;
    SectionElement *header;
    SectionElement *element;
    StageActor *link;
    StageManager *manager;
    int parentId;
    int actorId;
    u16 i;
    int node;

    parentId = 0;
    if (spawner != NULL && spawner->state == 1) {
        entry = GetStageEntry(spawner->entryId);
        if (entry != NULL && spawner->busy == 0) {
            spawner->hidden = 0;
            func_ov001_020931b0(spawner);
            ScheduleSpawnerNextTime(spawner, 0);
            spawner->nextTime += random_next_scaled(0xa000);
            header = GetResourceSectionElement(entry, 0, 0);
            if (header != NULL) {
                spawner->slotA = ReleaseStageSlot(8);
                spawner->slotB = ReleaseStageSlot(9);
                spawner->variant = header->variant;
                if (header->isLarge) {
                    spawner->large = 1;
                }
                if (header->isHidden) {
                    spawner->hidden = 1;
                }
                if (spawner->recordIndex != 0xffff) {
                    GetSmallTableEntry(spawner->recordIndex);
                }
                count = GetOwnerTableEntryValue(entry, 4);
                i = 0;
                if (count != 0) {
                    do {
                        element = GetResourceSectionElement(entry, 4, i);
                        actorId = func_ov001_02095120(spawner, entry, i, arg);
                        if (actorId == 0) {
                            break;
                        }
                        actor = GetStageActor((s16)actorId);
                        if (i == 0) {
                            arg = 0;
                            parentId = actorId;
                        } else {
                            node = func_ov001_0208f040(entry->resource, element->nodeIndex);
                            if (node != 0) {
                                AttachActorToStageNode(actor, parentId, node, 0);
                            }
                            for (link = GetStageActor((s16)parentId); link != NULL; link = GetStageActor((s16)link->nextId)) {
                                if (link->nextId == 0) {
                                    link->nextId = actorId;
                                    break;
                                }
                            }
                        }
                        actor->parentId = parentId;
                        if (actor->role == 2) {
                            spawner->leaderId = actorId;
                        }
                        i++;
                    } while (i < count);
                }
                func_ov001_02093358(spawner);
                spawner->timer = 0xf000;
                func_ov001_020925e4(spawner, 2);
                spawner->active = 1;
                if (spawner->recordIndex != 0xffff) {
                    manager = func_ov001_0209c3e8();
                    if (spawner->recordIndex < 0x40) {
                        manager->spawnCounts[spawner->recordIndex]++;
                    }
                }
            }
        }
    }
}

