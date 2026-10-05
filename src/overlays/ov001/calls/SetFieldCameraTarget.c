#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldCamera {
    u8 pad_00[0x14];
    VecFx32 eye;
    VecFx32 target;
    u8 pad_2c[0x0c];
    VecFx32 focus;
    VecFx32 offset;
    VecFx32 curFocus;
    VecFx32 curOffset;
    VecFx32 prevEye;
    VecFx32 prevTarget;
    fx32 speed;
    s32 roll;
    fx32 curSpeed;
    s32 curRoll;
    s32 timer;
    s32 duration;
    s32 state;
    s32 actorId;
} FieldCamera;

typedef struct CameraManager {
    FieldCamera main;
    FieldCamera alt;
    u8 pad_140[0x1e8 - 0x140];
    s32 useAlt;
    s32 prevUseAlt;
} CameraManager;

typedef struct CameraActor {
    u8 pad_00[0xa8];
    VecFx32 position;
} CameraActor;

extern CameraManager *data_ov001_020a0514;
extern const VecFx32 data_0205344c;

extern void func_01ff8ad8(const void *src, void *dst, u32 size);
extern void InterpolateFieldCamera(VecFx32 *focus, VecFx32 *offset, fx32 *speed, s32 *roll);
extern CameraActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void DispatchModeUpdate(FieldCamera *camera);

void SetFieldCameraTarget(int actorId, int duration, fx32 speed, int roll, const VecFx32 *focus, const VecFx32 *offset)
{
    CameraManager *manager = data_ov001_020a0514;
    BOOL interpolating = FALSE;
    FieldCamera *camera;
    VecFx32 zero;
    VecFx32 from;
    VecFx32 delta;

    if (manager->useAlt != 0) {
        func_01ff8ad8(manager, &manager->alt, 0x38);
        camera = &manager->alt;
    } else {
        camera = &manager->main;
    }
    camera->prevTarget = camera->target;
    camera->prevEye = camera->eye;
    if (manager->useAlt == 0 && camera->duration > 0 && camera->timer > 0) {
        InterpolateFieldCamera(&camera->curFocus, &camera->curOffset, &camera->curSpeed, &camera->curRoll);
        interpolating = TRUE;
    } else {
        camera->curFocus = camera->focus;
        camera->curSpeed = camera->speed;
        camera->curOffset = camera->offset;
        camera->curRoll = camera->roll;
    }
    if (camera->actorId != actorId) {
        zero = data_0205344c;
        from = zero;
        delta = zero;
        if (camera->actorId != -1) {
            from = ActorRegistry_GetEntityByIndex((u16)camera->actorId)->position;
        }
        if (actorId != -1) {
            delta = ActorRegistry_GetEntityByIndex((u16)actorId)->position;
        }
        VEC_Subtract(&from, &delta, &delta);
        VEC_Add(&camera->curFocus, &delta, &camera->curFocus);
    }
    if (roll > 0) {
        camera->roll = roll;
    }
    camera->speed = speed;
    camera->focus = *focus;
    camera->offset = *offset;
    camera->actorId = actorId;
    manager->prevUseAlt = manager->useAlt;
    if (manager->useAlt != 0) {
        InterpolateFieldCamera(NULL, NULL, NULL, NULL);
        manager->useAlt = 0;
    } else {
        camera->timer = duration;
        camera->duration = camera->timer;
        if (duration == 0 || interpolating) {
            InterpolateFieldCamera(NULL, NULL, NULL, NULL);
            if (duration == 0) {
                DispatchModeUpdate(camera);
            }
        }
    }
    if ((u32)(manager->main.state + 1) <= 1) {
        manager->main.state = 3;
    }
}
