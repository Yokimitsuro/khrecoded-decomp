#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa8];
    VecFx32 position;
    u8 pad_0b4[0x119 - 0xb4];
    u8 boxInitialized;
    u8 pad_11a[0x130 - 0x11a];
    u8 point[4];
    u8 bounds[0x18];
    u8 pad_14c[4];
    u8 delta[0xc];
    u8 movedBounds[0x18];
} FieldActor;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x77 - 0x44];
    u8 mode;
    u8 pad_78[0x84 - 0x78];
    VecFx32 lastPosition;
    u8 pad_90[0xbe - 0x90];
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
    u8 pad_c4[4];
    s32 timer;
} FieldObject;

extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void SetShapePosition(void *point, VecFx32 *position);
extern void OffsetBoxByDelta(void *src, void *dst, void *delta);
extern void TickFieldObjectRespawn(FieldObject *obj);
extern int UpdateFieldUnitAnimPhase(FieldObject *obj);
extern void func_ov016_020a3210(FieldObject *obj);
extern BOOL func_ov016_020a2b98(FieldObject *obj);
extern int UpdateSlidingFieldObject(FieldObject *obj);
extern int SweepFieldObjectBounce(FieldObject *obj);
extern void UpdateFloorSwitch(FieldObject *obj);
extern void ApplyFieldObjectForceToPlayer(FieldObject *obj);
extern void UpdateKickedFieldObject(FieldObject *obj);
extern void AnimateLaunchedFieldObject(FieldObject *obj);
extern void ClearFieldUnitPending(FieldObject *obj);
extern void DispatchFieldObjectPhase(FieldObject *obj);
extern void MoveFieldObjectWithCollision(FieldObject *obj, int arg);
extern void SnapFieldObjectToGround(FieldObject *obj);

int UpdateFieldObject(FieldObject *obj)
{
    u32 flags = obj->flags;
    FieldActor *actor;
    BOOL finished;

    if (flags & 0x10) {
        return 0;
    }
    if (obj->state == 6) {
        TickFieldObjectRespawn(obj);
        return 0;
    }
    if (!(flags & 0x100000)) {
        if (!(flags & 0x200000)) {
            actor = ActorRegistry_GetEntityByIndex(obj->actorId);
            if (actor->boxInitialized == 0) {
                actor->boxInitialized = 1;
                obj->position = actor->position;
                SetShapePosition(actor->point, &obj->position);
                OffsetBoxByDelta(actor->bounds, actor->movedBounds, actor->delta);
            }
            obj->lastPosition = obj->position;
            flags = obj->flags | 0x100000;
            obj->flags = flags;
            if (flags & 0x400000) {
                func_ov016_020a3210(obj);
            }
            if (obj->timer != 0) {
                obj->timer -= 0x89;
                if (obj->timer < 0) {
                    obj->timer = 0;
                }
            }
            func_ov016_020a2b98(obj);
            switch (obj->state) {
            case 5:
                TickFieldObjectRespawn(obj);
                return UpdateFieldUnitAnimPhase(obj);
            case 1:
            case 2:
            case 3:
                return UpdateSlidingFieldObject(obj);
            case 4:
                return SweepFieldObjectBounce(obj);
            }
            switch (obj->mode) {
            case 5:
                UpdateFloorSwitch(obj);
                break;
            case 6:
                ApplyFieldObjectForceToPlayer(obj);
                break;
            case 7:
                UpdateKickedFieldObject(obj);
                break;
            case 11:
                AnimateLaunchedFieldObject(obj);
                break;
            case 3:
                ClearFieldUnitPending(obj);
                break;
            }
            DispatchFieldObjectPhase(obj);
            if (obj->mode == 9 || (u8)(obj->mode + 0xf4) <= 3) {
                finished = TRUE;
            } else {
                finished = FALSE;
            }
            if (finished) {
                MoveFieldObjectWithCollision(obj, 0);
            }
        }
        SnapFieldObjectToGround(obj);
    }
    return 0;
}
