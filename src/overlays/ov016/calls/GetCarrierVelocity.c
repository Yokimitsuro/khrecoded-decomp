#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldUnit FieldUnit;

typedef struct {
    u8 pad_00[0x30];
    BOOL (*isBusy)(FieldUnit *unit);
} FieldUnitClass;

struct FieldUnit {
    u8 pad_00[4];
    FieldUnitClass *klass;
    u8 pad_08[4];
    void (*update)(FieldUnit *unit);
    u8 pad_10[0x32 - 0x10];
    u8 actorId;
};

typedef struct {
    u8 pad_000[0x150];
    VecFx32 delta;
} FieldActor;

typedef struct {
    u8 pad_00[0xc0];
    u32 flags;
    u8 pad_c4[0xe8 - 0xc4];
    s16 carrierGroup;
    s16 carrierIndex;
} FieldObject;

extern const VecFx32 data_0205344c;
extern FieldUnit *func_ov001_0208724c(int group, int index);
extern BOOL IsFieldUnitAction5Mode1(FieldUnit *unit);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);

VecFx32 GetCarrierVelocity(FieldObject *obj)
{
    VecFx32 velocity = data_0205344c;
    FieldUnit *carrier;
    BOOL busy;

    if (obj->carrierGroup != -1 && obj->carrierIndex != -1) {
        carrier = func_ov001_0208724c(obj->carrierGroup, obj->carrierIndex);
        carrier->update(carrier);
        if (carrier->klass->isBusy != NULL) {
            busy = carrier->klass->isBusy(carrier);
        } else {
            busy = FALSE;
        }
        if (!busy && !IsFieldUnitAction5Mode1(carrier)) {
            velocity = ActorRegistry_GetEntityByIndex(carrier->actorId)->delta;
            if (velocity.x != 0 || velocity.y != 0 || velocity.z != 0) {
                obj->flags &= ~0x800;
            }
        } else {
            obj->carrierGroup = -1;
            obj->carrierIndex = -1;
            obj->flags &= ~0x800;
        }
    }
    return velocity;
}
