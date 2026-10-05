#include "nitro/types.h"

typedef struct ColliderOwner {
    u8 pad_00[0x6c];
    s32 kind;
} ColliderOwner;

typedef struct Collider {
    ColliderOwner *owner;
} Collider;

BOOL Collider_IsOwnerKind11(Collider *collider)
{
    if (collider->owner->kind == 11) {
        return TRUE;
    }
    return FALSE;
}
