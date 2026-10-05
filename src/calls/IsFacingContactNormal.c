#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Contact {
    u8 pad_00[0x14];
    fx16 normalX;
    fx16 normalY;
    fx16 normalZ;
} Contact;

typedef struct ContactRef {
    Contact *contact;
    s32 kind;
} ContactRef;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

static inline VecFx32 GetContactNormal(const Contact *contact) {
    VecFx32 normal;
    normal.x = contact->normalX;
    normal.y = contact->normalY;
    normal.z = contact->normalZ;
    return normal;
}

BOOL IsFacingContactNormal(ContactRef *ref, const VecFx32 *direction) {
    VecFx32 normal;

    switch (ref->kind) {
    case 0:
        break;
    case 1:
        normal = GetContactNormal(ref->contact);
        break;
    case 2:
        normal = GetContactNormal(ref->contact);
        break;
    case 3:
        normal = GetContactNormal(ref->contact);
        break;
    case 4:
        return TRUE;
    }
    return VEC_DotProduct(direction, &normal) > 0;
}
