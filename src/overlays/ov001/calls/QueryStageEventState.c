#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 state;
    u8 pad_04[2];
    u16 unk_06;
    u8 unk_08;
    u8 unk_09_0 : 4;
    u8 isEnabled : 1;
    u8 unk_09_5 : 3;
    u8 pad_0A[6];
    u16 groupId;
    u8 pad_12[0x16];
} StageEvent;

typedef struct {
    u8 pad_00[0x208];
    StageEvent *events;
    u8 pad_20C[0x18de8 - 0x20c];
    u16 eventCount;
    u8 pad_18DEA[0x18f40 - 0x18dea];
    u32 busy;
} StageManager;

extern StageManager *data_ov001_020a0528;

BOOL QueryStageEventState(int mode, int groupId)
{
    u16 index;

    switch (mode) {
    case 0:
        if (data_ov001_020a0528->busy != 0) {
            return FALSE;
        }
        for (index = 0; index < data_ov001_020a0528->eventCount; index++) {
            if (data_ov001_020a0528->events[index].isEnabled &&
                data_ov001_020a0528->events[index].state != 0 &&
                (groupId < 0 || groupId == data_ov001_020a0528->events[index].groupId) &&
                data_ov001_020a0528->events[index].state == 2 &&
                data_ov001_020a0528->events[index].unk_06 != 0) {
                return TRUE;
            }
        }
        return FALSE;
    case 1:
        for (index = 0; index < data_ov001_020a0528->eventCount; index++) {
            if (data_ov001_020a0528->events[index].isEnabled &&
                (groupId < 0 || groupId == data_ov001_020a0528->events[index].groupId) &&
                data_ov001_020a0528->events[index].state != 0 &&
                data_ov001_020a0528->events[index].state != 6 &&
                data_ov001_020a0528->events[index].state != 7) {
                return FALSE;
            }
        }
        return TRUE;
    case 2:
        for (index = 0; index < data_ov001_020a0528->eventCount; index++) {
            if (data_ov001_020a0528->events[index].isEnabled &&
                (groupId < 0 || groupId == data_ov001_020a0528->events[index].groupId) &&
                data_ov001_020a0528->events[index].state != 0 &&
                data_ov001_020a0528->events[index].state != 7) {
                return FALSE;
            }
        }
        return TRUE;
    }
    return TRUE;
}
