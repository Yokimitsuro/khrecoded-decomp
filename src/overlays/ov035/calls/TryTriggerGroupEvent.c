#include "nitro/types.h"

typedef struct EventGroup {
    u8 groupId;
    u8 unknown_01[6];
    u8 eventCount;
    u8 unknown_08[0x0c];
    u16 *eventIds;
    u8 unknown_18[4];
} EventGroup;

typedef struct EventTable {
    u8 unknown_00[2];
    u8 groupCount;
    u8 unknown_03[0x0d];
    EventGroup *groups;
    u8 unknown_14[0x0e];
    s8 activeGroup;
} EventTable;

typedef struct SceneWork {
    u8 unknown_00[0x40];
    EventTable table;
} SceneWork;

extern SceneWork *data_ov035_020bc500;
extern int StageEvents_CheckEvent(u16 eventId);
extern void StageEvent_ReleaseHoldBit2(u16 eventId);
extern void func_ov001_02087e44(u16 eventId);
extern void StageEvent_SetHoldBit2(u16 eventId);

BOOL TryTriggerGroupEvent(u16 eventId) {
    SceneWork *work = data_ov035_020bc500;
    EventTable *table = &work->table;
    int i;
    int j;

    for (i = 0; i < work->table.groupCount; i++) {
        EventGroup *group = &work->table.groups[i];
        for (j = 0; j < group->eventCount; j++) {
            if (eventId == group->eventIds[j]) {
                if (StageEvents_CheckEvent(group->eventIds[j]) == 0) {
                    if (group->groupId == table->activeGroup) {
                        StageEvent_ReleaseHoldBit2(group->eventIds[j]);
                        func_ov001_02087e44(group->eventIds[j]);
                        return TRUE;
                    }
                    StageEvent_SetHoldBit2(group->eventIds[j]);
                }
                return FALSE;
            }
        }
    }
    return TRUE;
}
