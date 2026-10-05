#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
} FieldObject;

typedef struct ActorBody {
    u8 pad_000[0x150];
    VecFx32 velocity;
} ActorBody;

typedef struct PartyEntry {
    u8 pad_000[0x9c8];
    VecFx32 velocity;
} PartyEntry;

extern PartyEntry *func_ov001_0206db5c(int index);
extern ActorBody *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Vec3MulScalar(VecFx32 *v, fx32 factor);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL IsMovingAgainstDirection(FieldObject *object, int entryIndex, VecFx32 *direction)
{
    BOOL result = FALSE;

    if (direction->y != 0) {
        result = TRUE;
    } else {
        PartyEntry *entry = func_ov001_0206db5c(entryIndex);
        VecFx32 velocity = ActorRegistry_GetEntityByIndex(object->actorId)->velocity;
        VecFx32 relative;
        VecFx32 unit;
        VecFx32 normalized;
        fx32 dot = 1;

        Vec3MulScalar(&velocity, -1);
        func_01ff9e0c(&velocity, &entry->velocity, &relative);
        if (relative.x != 0 || relative.y != 0 || relative.z != 0) {
            VEC_Normalize(&relative, &normalized);
            unit = normalized;
            dot = VEC_DotProduct(&unit, direction);
        }
        if (dot < -0x20) {
            result = TRUE;
        }
    }
    return result;
}
