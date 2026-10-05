#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x150];
    fx32 deltaX;
    u8 pad_154[4];
    fx32 deltaZ;
} FieldActor;

typedef struct {
    u8 pad_00[0x2c];
    fx32 distance;
} RayHit;

typedef struct {
    const VecFx32 *origin;
    const VecFx32 *direction;
    fx32 length;
    u16 mode;
    u16 mask;
    void *context;
    u8 pad_14[0x60 - 0x14];
} RayQuery;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x70 - 0x44];
    u16 unk_70_0 : 1;
    u16 grounded : 1;
    u16 unk_70_2 : 1;
    u16 fixedHeight : 1;
    u16 unk_70_4 : 1;
    u16 needsGround : 1;
    u16 unk_70_6 : 10;
    u8 pad_72[0x98 - 0x72];
    fx32 dropOffset;
    fx32 groundY;
} FieldObject;

extern const VecFx32 data_ov016_020a6e30;
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern int GetActorRegistry(void);
extern RayHit *func_020351cc(int handle, RayQuery *query);
extern void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);
extern int func_ov001_020644b0(void);

void SnapFieldObjectToGround(FieldObject *obj)
{
    VecFx32 down;
    VecFx32 hitPos;
    RayQuery query;
    FieldActor *actor;
    RayHit *hit;
    BOOL check;
    BOOL doSweep;
    fx32 diff;

    if (!obj->needsGround) {
        return;
    }
    check = FALSE;
    if (obj->fixedHeight) {
        obj->dropOffset = 0;
    } else {
        doSweep = TRUE;
        obj->dropOffset = 0;
        if (obj->grounded && (actor = ActorRegistry_GetEntityByIndex(obj->actorId), actor->deltaX == 0) && actor->deltaZ == 0) {
            doSweep = FALSE;
            check = TRUE;
        }
        if (doSweep) {
            down = data_ov016_020a6e30;
            obj->groundY = 0;
            obj->grounded = 0;
            query.origin = &obj->position;
            query.length = 0x1800;
            query.direction = &down;
            query.mode = 1;
            query.mask = 0;
            query.context = obj;
            hit = func_020351cc(GetActorRegistry(), &query);
            if (hit != NULL) {
                AddScaledVector(hit->distance, &down, &obj->position, &hitPos);
                obj->groundY = hitPos.y;
                check = TRUE;
                obj->grounded = 1;
            }
        }
        obj->needsGround = 0;
    }
    if (check) {
        check = (func_ov001_020644b0() == 900);
        diff = obj->position.y - obj->groundY;
        if (diff >= 0x19a && (diff <= 0x7800 || check)) {
            obj->dropOffset = obj->groundY - obj->position.y + 0x1e0;
        }
    }
}
