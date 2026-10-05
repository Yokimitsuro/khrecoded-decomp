#include "nitro/types.h"

typedef struct ObjectClass {
    u8 pad_00[0x8];
    u16 flags;
} ObjectClass;

typedef struct FieldObject {
    u8 pad_00[0xc];
    ObjectClass *objectClass;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[0x1f];
    s32 active;
} FieldObject;

extern void func_ov011_020a0708(FieldObject *object, int state);
extern BOOL ActorSlot_GetByIndex(int actorId);
extern void *ActorRegistry_GetEntityByIndex(int actorId);
extern void func_ov001_0207f8f8(FieldObject *object, s8 track);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void TransitionRecordSlot(int index);
extern void func_ov001_0207f71c(FieldObject *object, BOOL enabled);

void FieldObject_ResetToIdle(FieldObject *object)
{
    if (object->active != 0) {
        func_ov011_020a0708(object, 0);
        if (ActorSlot_GetByIndex(object->actorId)) {
            ActorRegistry_GetEntityByIndex(object->actorId);
            func_ov001_0207f8f8(object, 0);
            ActorSlot_SetFlag8ByIndex(object->actorId, TRUE);
            if ((object->objectClass->flags & 0x100) == 0) {
                TransitionRecordSlot(object->actorId);
            }
        }
        func_ov001_0207f71c(object, TRUE);
    }
}
