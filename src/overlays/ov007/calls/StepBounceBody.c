#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 unk_00;
    VecFx32 position;
    VecFx32 velocity;
} BounceBody;

extern const VecFx32 data_0205344c;

extern BOOL func_ov007_020a09ac(void *owner, const VecFx32 *position, const VecFx32 *velocity, VecFx32 *hit);
extern BOOL DampBounceVelocity(void *owner, BounceBody *body);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

BOOL StepBounceBody(void *owner, BounceBody *body) {
    VecFx32 hit;

    if (func_ov007_020a09ac(owner, &body->position, &body->velocity, &hit)) {
        body->position = hit;
        if (!DampBounceVelocity(owner, body)) {
            body->velocity = data_0205344c;
            return FALSE;
        }
    } else {
        VEC_Add(&body->position, &body->velocity, &body->position);
    }
    return TRUE;
}
