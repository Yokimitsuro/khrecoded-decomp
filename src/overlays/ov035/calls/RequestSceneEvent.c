#include "nitro/types.h"

typedef struct SceneWork {
    u8 unknown_00[6];
    u16 flags;
    u8 unknown_08[0x15];
    u8 eventMode;
    u8 unknown_1e[8];
    s16 eventId;
    s16 lockedEventId;
    u8 unknown_2a[8];
    s16 lockCount;
} SceneWork;

typedef struct SystemState {
    u8 unknown_00[0x20];
    u32 flags;
} SystemState;

extern SceneWork *data_ov035_020bc500;
extern SystemState *data_ov001_020a0480;
extern int func_ov001_02063620(void);
extern int StageEvents_CheckEvent(u16 eventId);
extern int func_ov001_020645c8(int flagId);
extern void func_ov001_02078680(void);

void RequestSceneEvent(int eventId, u8 mode, int forced) {
    SceneWork *work = data_ov035_020bc500;

    if (forced == 0) {
        if (func_ov001_02063620() != 0) {
            return;
        }
        if (data_ov001_020a0480->flags & 0x10) {
            return;
        }
    } else {
        work->flags |= 0x80;
    }
    if (work->flags & 0x10) {
        return;
    }
    if (work->lockCount > 0 && eventId == work->lockedEventId) {
        return;
    }
    if (StageEvents_CheckEvent(eventId) != 0) {
        return;
    }
    work->eventMode = mode;
    work->eventId = eventId;
    if (func_ov001_020645c8(0x3723) != 0 && work->eventMode == 3) {
        work->eventMode = 1;
    }
    if (func_ov001_020645c8(0x3724) != 0) {
        work->eventMode = 2;
    }
    func_ov001_02078680();
}
