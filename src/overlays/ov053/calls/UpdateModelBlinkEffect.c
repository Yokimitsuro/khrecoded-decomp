#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EffectRequest {
    u8 selection;
    u8 pad_01[3];
    VecFx32 position;
    u16 scale;
    u16 rotation;
    u8 pad_14[4];
    void *partData;
    u8 pad_1c[8];
    u8 layer;
    u8 mode;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} EffectRequest;

typedef struct WorkData {
    u8 pad_0000[0x1258];
    s16 effectGroupId;
    u8 pad_125a[2];
    int blinkTimer;
} WorkData;

typedef struct Entity {
    u8 pad_000[0x6cc];
    u8 partData[0x9ac - 0x6cc];
    u64 stateFlags;
    u8 selection;
    u8 pad_9b5[0x9ec - 0x9b5];
    int frameStep;
    u8 pad_9f0[0xb68 - 0x9f0];
    u32 modelFlags;
} Entity;

extern WorkData *data_ov053_020d2c40;
extern VecFx32 data_0205344c;
extern BOOL func_ov001_0206e31c(void);
extern void Entity_UpdateEventEffect(Entity *entity, int step);
extern BOOL func_ov021_020a9d24(u32 *flags);
extern BOOL IsBit0Set(u32 *flags);
extern BOOL func_ov001_020645c8(u32 value);
extern void ResetAnimationTrackState(EffectRequest *request);
extern int func_ov021_020a8cc0(EffectRequest *request, int groupId);
extern void SetBit1WhenBit0Set(u32 *flags, int enable);

void UpdateModelBlinkEffect(Entity *entity)
{
    EffectRequest request;
    WorkData *work = data_ov053_020d2c40;
    BOOL toggle = FALSE;

    if (func_ov001_0206e31c()) {
        Entity_UpdateEventEffect(entity, entity->frameStep);
    }
    if ((entity->stateFlags & 0x20800) != 0) {
        return;
    }
    if (!func_ov021_020a9d24(&entity->modelFlags) && (entity->stateFlags & 0x40) != 0) {
        toggle = TRUE;
    } else if (func_ov021_020a9d24(&entity->modelFlags) && (entity->stateFlags & 0x40) == 0) {
        toggle = TRUE;
    }
    if (IsBit0Set(&entity->modelFlags) && !func_ov001_020645c8(0x3520) && toggle) {
        if (work->blinkTimer == 0) {
            ResetAnimationTrackState(&request);
            request.selection = entity->selection;
            request.mode = 2;
            request.layer = 0;
            request.position = data_0205344c;
            request.rotation = 0;
            request.scale = 0x1000;
            request.partData = entity->partData;
            request.prevIndex = request.index = -1;
            func_ov021_020a8cc0(&request, work->effectGroupId);
            work->blinkTimer += entity->frameStep;
            return;
        }
        work->blinkTimer += entity->frameStep;
        if (work->blinkTimer >= 0x3800) {
            SetBit1WhenBit0Set(&entity->modelFlags, !func_ov021_020a9d24(&entity->modelFlags));
            work->blinkTimer = 0;
        }
    }
}
