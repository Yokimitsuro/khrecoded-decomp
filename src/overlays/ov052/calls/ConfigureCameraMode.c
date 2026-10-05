#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int scale;
    fx32 speed;
    fx32 accel;
} CameraSpeedEntry;

typedef struct {
    CameraSpeedEntry entries[2];
} CameraSpeedTable;

typedef struct {
    u8 pad_00[4];
    fx32 speed;
    fx32 lift;
    fx32 accel;
    VecFx32 focus;
    s16 scale;
    u8 pad_1e[2];
    fx32 offsetX;
    fx32 offsetY;
    int timer;
    u8 pad_2c[4];
    fx32 pitch;
    fx32 shakeX;
    fx32 shakeY;
    s8 mode;
    s8 shake;
    s8 lock;
    s8 bounce;
    u8 zoomed;
} CameraState;

typedef struct {
    u8 pad_000[0x75c];
    int linkMode;
    u8 pad_760[0x9ac - 0x760];
    u64 stateFlags;
} CameraActor;

extern const CameraSpeedTable data_ov052_020d211c;
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL func_ov001_0206e2b0(void);
extern void AddSessionCounter(int index, int amount);
extern int GetPlayerEntryCount(int player, u32 id);
extern VecFx32 *func_ov052_020ceb90(CameraActor *actor);

void ConfigureCameraMode(CameraState *camera, CameraActor *actor, int previous, u32 kind)
{
    fx32 speed;
    CameraSpeedTable table;
    int level;

    camera->lock = -1;
    camera->mode = -1;
    speed = 0x266;
    if (IsPlayerEntryFlagSet(0, 0xc) && !func_ov001_0206e2b0()) {
        speed = 0x2cd;
    }
    switch (kind) {
    case 1:
        camera->speed = 0x333;
        camera->accel = 0x80;
        camera->scale = 0xc00;
        camera->bounce = 0;
        camera->shakeX = 0;
        camera->shakeY = 0;
        return;
    case 6:
    case 0x10:
        camera->bounce = 0;
        camera->lift = 0;
        camera->shakeX = 0;
        camera->shakeY = 0;
        return;
    case 2:
    case 0xd:
    case 0x12:
        camera->speed = speed;
        camera->accel = speed;
        camera->scale = 0x1000;
        camera->mode = 0;
        camera->offsetX = camera->offsetY = 0;
        camera->pitch = 0;
        camera->bounce = 0;
        camera->focus.x = camera->focus.y = camera->focus.z = 0;
        if (kind == 0xd) {
            actor->stateFlags |= 0x1000;
            camera->lock = 1;
        } else {
            AddSessionCounter(9, 1);
        }
        if (kind != 0x12) {
            camera->timer = 0;
            return;
        }
        if (camera->timer == 0) {
            actor->stateFlags |= 0x1000;
            return;
        }
        break;
    case 3:
        camera->scale = 0x1000;
        camera->mode = 1;
        camera->speed = speed;
        camera->accel = speed;
        camera->offsetY = 0;
        camera->offsetX = 0;
        if (previous == 0x10) {
            camera->focus.z = 0;
            camera->focus.y = 0;
            camera->focus.x = 0;
            return;
        }
        break;
    case 4:
        camera->scale = 0x1000;
        camera->mode = 2;
        camera->offsetY = 0;
        camera->offsetX = 0;
        camera->speed = speed;
        camera->accel = speed;
        camera->focus = *func_ov052_020ceb90(actor);
        return;
    case 5:
        camera->accel = 0x80;
        camera->speed = 0x333;
        camera->scale = 0xc00;
        camera->lift = 0x333;
        camera->bounce = 0;
        camera->shakeX = 0;
        camera->shakeY = 0;
        camera->focus.z = 0;
        camera->focus.y = 0;
        camera->focus.x = 0;
        camera->mode = 3;
        return;
    case 0xc:
        camera->scale = 0x1800;
        camera->lock = 0;
        return;
    case 0x11:
        table = data_ov052_020d211c;
        level = GetPlayerEntryCount(0, 0xe);
        if (level > 0) {
            level--;
        }
        if (actor->linkMode == 0xe) {
            camera->lift = 0;
        }
        camera->scale = table.entries[level].scale;
        camera->speed = table.entries[level].speed;
        camera->accel = table.entries[level].accel;
        return;
    case 0x13:
        camera->speed = 0xa00;
        camera->lift = 0xa00;
        camera->bounce++;
        return;
    case 0x15:
    case 0x18:
        camera->zoomed = 0;
        if (actor->stateFlags & 0x1000000000ULL) {
            camera->mode = 0;
            return;
        }
        break;
    case 9:
        camera->shake = 0;
        break;
    }
}
