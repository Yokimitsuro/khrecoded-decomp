#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x68];
    s32 current;
    s32 reset;
} StageActor;

typedef struct {
    u8 pad_00[0x368];
    VecFx32 offset;
} StageCamera;

typedef struct {
    StageActor *actor;
    u32 pad_04;
    StageCamera *camera;
} StageGlobals;

typedef struct {
    u32 pad_00;
    s32 id;
} StageEvent;

extern StageGlobals data_ov021_020b56c4;
extern VecFx32 data_0205344c;
extern void ScheduleSpawnerNextTime(StageActor *actor, int delay);
extern u8 *func_ov001_0209c3e8(void);

int HandleStageEvent(void *self, StageEvent *event)
{
    StageActor *actor = data_ov021_020b56c4.actor;
    StageCamera *camera = data_ov021_020b56c4.camera;

    switch (event->id) {
    case 0x5a:
        actor->flags |= 0x1000;
        break;
    case 4:
        if (camera != NULL) {
            camera->offset = data_0205344c;
        }
        break;
    case 3:
        if (actor != NULL) {
            ScheduleSpawnerNextTime(actor, 0);
        }
        break;
    case 0x40:
        *(u16 *)(func_ov001_0209c3e8() + 0x18ed2) = 0;
        break;
    case 0x16:
        if (actor != NULL) {
            actor->current = actor->reset;
        }
        break;
    }
    return 0;
}
