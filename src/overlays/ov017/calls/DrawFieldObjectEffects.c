#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldManager {
    u8 pad_00[0x6c];
    u8 breakAnim[0xa4];
    VecFx32 breakPosition;
} FieldManager;

typedef struct ActorModel {
    u8 pad_00[0x80];
    u8 shadow[4];
} ActorModel;

typedef struct FieldActor {
    u8 pad_00[4];
    ActorModel model;
} FieldActor;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldManager *manager;
    u8 pad_08[0x2a];
    u8 slot;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[6];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    u8 pad_4C[0x1c];
    s32 timer;
} FieldObject;

extern void func_01ffb2f8(void *anim, u16 track, int frame);
extern void func_01ffb12c(void *node);
extern FieldActor *ActorRegistry_GetEntityByIndex(int slot);
extern fx32 EaseProgress(fx32 time, fx32 duration, int easing);
extern s8 func_ov001_02068084(void);
extern void DrawTexturedGridQuads(void *model, fx32 size, int rows, int cols, void *node, int alpha, BOOL lit);

void DrawFieldObjectEffects(FieldObject *object)
{
    FieldManager *manager = object->manager;
    FieldActor *actor;
    fx32 fade;
    BOOL lit;

    if (object->flags & 8) {
        manager->breakPosition = object->position;
        func_01ffb2f8(manager->breakAnim, 0, object->timer);
        func_01ffb2f8(manager->breakAnim, 2, object->timer);
        func_01ffb12c(manager->breakAnim);
    }
    if (object->state != 0 && !(object->flags & 4)) {
        return;
    }
    actor = ActorRegistry_GetEntityByIndex(object->slot);
    if (!(object->flags & 8) && object->timer != -1) {
        lit = FALSE;
        fade = EaseProgress(object->timer, 0x5000, 0);
        if (fade != 0) {
            if (func_ov001_02068084() != 6) {
                lit = TRUE;
            }
            DrawTexturedGridQuads(&actor->model, 0x1800, 1, 1, (u8 *)&actor->model + 0x80, (fade * 0x1f) >> 12, lit);
        }
    } else if (object->flags & 4) {
        func_01ffb12c(&actor->model);
    } else {
        DrawTexturedGridQuads(&actor->model, 0x1800, 1, 1, (u8 *)&actor->model + 0x80, 0x1f, func_ov001_02068084() != 6);
    }
}
