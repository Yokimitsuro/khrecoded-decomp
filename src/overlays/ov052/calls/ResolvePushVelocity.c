#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *surface;
    int kind;
    int pad_08;
} ContactHit;

typedef struct {
    ContactHit hits[16];
    VecFx32 normals[16];
    u8 count;
} ContactList;

typedef struct {
    u8 pad_000[0x234];
    u32 modelFlags;
    u8 pad_238[0x344 - 0x238];
    ContactList contacts;
    u8 pad_4c8[0x9e0 - 0x4c8];
    VecFx32 push;
} PushActor;

extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void func_01ffafb4(fx32 scale, const VecFx32 *v, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void ResolvePushVelocity(PushActor *actor, VecFx32 *out)
{
    VecFx32 horizontal;
    VecFx32 dir;
    VecFx32 normal;
    fx32 savedY;
    BOOL blocked;
    int i;
    ContactList *contacts;

    if (VEC_Mag(&actor->push) <= 0x200) {
        out->x = out->y = out->z = actor->push.x = actor->push.y = actor->push.z = 0;
        return;
    }
    horizontal = actor->push;
    savedY = horizontal.y;
    horizontal.y = 0;
    if (VEC_Mag(&horizontal) > 0x900) {
        VEC_Normalize(&horizontal, &horizontal);
        func_01ffafb4(0x900, &horizontal, &horizontal);
    }
    if ((actor->modelFlags & 2) && (horizontal.x != 0 || horizontal.y != 0 || horizontal.z != 0)) {
        contacts = &actor->contacts;
        dir = horizontal;
        blocked = FALSE;
        VEC_Normalize(&dir, &dir);
        for (i = 0; i < contacts->count; i++) {
            normal = contacts->normals[i];
            if ((normal.x != 0 || normal.z != 0) && VEC_DotProduct(&dir, &normal) <= -0xccd) {
                blocked = TRUE;
                break;
            }
        }
        if (blocked) {
            func_01ffafb4(0x333, &horizontal, &horizontal);
            func_01ffafb4(0x333, &actor->push, &actor->push);
        }
    }
    horizontal.y = savedY;
    *out = horizontal;
    actor->push.y = 0;
    func_01ffafb4(0xc80, &actor->push, &actor->push);
}
