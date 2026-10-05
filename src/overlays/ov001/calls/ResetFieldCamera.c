#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xc];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    u8 pad_2c[0xc];
    VecFx32 velocity;
    s32 yaw;
    s32 pitch;
    s32 roll;
    VecFx32 shake;
    u8 pad_5c[0xc];
    VecFx32 basePosition;
    VecFx32 baseTarget;
    fx32 distance;
    s32 fovy;
    u8 pad_88[8];
    s32 followMode;
    s32 followTarget;
    u8 pad_98[4];
    s32 lockedActor;
} FieldCamera;

extern FieldCamera *data_ov001_020a0514;
extern const VecFx32 data_0205344c;
extern s16 data_02053580[];
extern void ActorChannel_ResetFields(void);
extern void LoadDefaultProjectionValues(FieldCamera *camera);
extern fx32 FX_Mul(fx32 a, fx32 b);

void ResetFieldCamera(void)
{
    FieldCamera *camera = data_ov001_020a0514;

    ActorChannel_ResetFields();
    camera->followTarget = 0;
    camera->followMode = camera->followTarget;
    camera->lockedActor = -1;
    LoadDefaultProjectionValues(camera);
    camera->distance = 0x1800;
    camera->yaw = 0;
    camera->pitch = 0x1554;
    camera->roll = 0;
    camera->fovy = 0xe38;
    camera->position = data_0205344c;
    camera->target.x = camera->position.x;
    camera->target.y = camera->position.y + FX_Mul(camera->distance, data_02053580[camera->pitch >> 4]);
    camera->target.z = camera->position.z + FX_Mul(camera->distance, data_02053580[(0x400 - (camera->pitch >> 4)) & 0xfff]);
    camera->position = camera->basePosition;
    camera->baseTarget = camera->target;
    camera->shake.z = 0;
    camera->shake.y = 0;
    camera->shake.x = 0;
    camera->velocity.z = 0;
    camera->velocity.y = 0;
    camera->velocity.x = 0;
    camera->farClip = 0x6a4000;
    camera->nearClip = 0x19a;
}
