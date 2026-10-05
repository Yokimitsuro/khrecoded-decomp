#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x8c];
    s16 waitTime;
    u8 pad_8E[6];
    s8 riders;
} ElevatorClassData;

typedef struct {
    u8 pad_00[8];
    ElevatorClassData *classData;
    u8 pad_0C[0x2c];
    u8 actorSlot;
    u8 pad_39[0x15];
    u16 flags;
    u8 pad_50[3];
    s8 state;
    u8 pad_54[0x14];
    fx32 frame;
    s8 cooldown;
    u8 pad_6D;
    s8 load;
    s8 count;
    s16 timer;
} ElevatorObject;

typedef struct {
    u8 pad_00[4];
    u8 anim[4];
} ActorNode;

extern const s8 data_ov006_020a1854[];

extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern BOOL func_ov001_020645c8(int bitId);
extern BOOL ActorSlot_IsFlag8SetByIndex(int index);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern BOOL AdvanceAnimFrame_02080a60(void *anim, fx32 step, BOOL loop, fx32 length, fx32 *frame);
extern BOOL func_ov001_02063838(void);
extern void func_ov006_020a0708(ElevatorObject *object);
extern u16 FieldObject_GetSavedValue(ElevatorObject *object);
extern void FieldObject_SetSavedValue(ElevatorObject *object, u16 value);

int UpdateStaticElevator(ElevatorObject *object) {
    ElevatorClassData *data;
    ActorNode *actor;
    BOOL done;

    data = object->classData;
    done = FALSE;
    actor = ActorRegistry_GetEntityByIndex(object->actorSlot);

    if (func_ov001_020645c8(0x3717)) {
        return done;
    }
    if (object->cooldown > 0) {
        object->cooldown--;
    }
    if (ActorSlot_IsFlag8SetByIndex(object->actorSlot)) {
        fx32 length = data_ov006_020a1854[object->state] << 12;

        done = length <= object->frame + FX32_ONE;
        AdvanceAnimFrame_02080a60(actor->anim, 0x1000, FALSE, length, &object->frame);
    } else if (data->riders < 12 && object->timer > 0) {
        if (!func_ov001_02063838() && --object->timer == 0) {
            object->state = 3;
            func_ov006_020a0708(object);
            object->load = 6;
            data->riders -= object->load;
            ActorSlot_SetFlag8ByIndex(object->actorSlot, TRUE);
            FieldObject_SetSavedValue(object, FieldObject_GetSavedValue(object) & ~4);
        }
        return 0;
    }
    switch (object->state) {
    case 0:
        break;
    case 1:
        if (done) {
            if (--object->count == 0) {
                if (object->load == 0) {
                    object->state = 2;
                } else {
                    object->state = 0;
                }
            }
            func_ov006_020a0708(object);
        }
        break;
    case 2:
        if (done) {
            object->timer = data->waitTime;
            ActorSlot_SetFlag8ByIndex(object->actorSlot, FALSE);
        }
        break;
    case 3:
        if (done) {
            object->state = 0;
            func_ov006_020a0708(object);
            object->flags |= 0x10;
        }
        break;
    }
    return 0;
}



