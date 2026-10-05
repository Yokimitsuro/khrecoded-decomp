#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactTarget {
    void *object;
    int kind;
} ContactTarget;

typedef struct ShortVec {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

typedef struct ContactSurface {
    u8 pad_00[0x14];
    ShortVec normal;
} ContactSurface;

typedef struct Mover {
    u8 pad_00[0x20];
    VecFx32 direction;
} Mover;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

static inline VecFx32 ShortVecToFx32(const ShortVec *src)
{
    VecFx32 out;

    out.x = src->x;
    out.y = src->y;
    out.z = src->z;
    return out;
}

BOOL IsFacingContact(ContactTarget *contact, int unused1, int unused2, Mover *mover)
{
    VecFx32 normal;

    if (contact->kind != 4) {
        normal = ShortVecToFx32(&((ContactSurface *)contact->object)->normal);
        if (VEC_DotProduct(&normal, &mover->direction) >= 0) {
            return FALSE;
        }
    }
    return TRUE;
}
