#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactNormal {
    fx16 x;
    fx16 y;
    fx16 z;
} ContactNormal;

typedef struct Contact {
    u8 pad_00[0x14];
    ContactNormal normal;
} Contact;

typedef struct ContactRef {
    Contact *contact;
    s32 kind;
} ContactRef;

typedef struct ContactQuery {
    u8 pad_00[4];
    VecFx32 direction;
    fx32 distance;
} ContactQuery;

typedef struct CameraWork {
    u8 pad_00[0x20];
    VecFx32 forward;
} CameraWork;

extern BOOL IsFacingContactNormal(ContactRef *ref, const VecFx32 *direction);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

static inline VecFx32 GetNormalized(const VecFx32 *src)
{
    VecFx32 result;
    func_01ffaff4(src, &result);
    return result;
}

static inline VecFx32 GetContactNormal(const ContactNormal *src)
{
    VecFx32 normal;
    normal.x = src->x;
    normal.y = src->y;
    normal.z = src->z;
    return normal;
}

BOOL CameraCollision_CheckContact(ContactRef *ref, ContactQuery *query, void *unused, CameraWork *work)
{
    VecFx32 forward;
    VecFx32 normal;

    if (!IsFacingContactNormal(ref, &query->direction)) {
        return FALSE;
    }
    forward = GetNormalized(&work->forward);
    if (VEC_DotProduct(&forward, &query->direction) >= -0x80) {
        return FALSE;
    }
    if (ref->kind != 4) {
        normal = GetContactNormal(&ref->contact->normal);
        if (VEC_DotProduct(&normal, &work->forward) >= 0) {
            return FALSE;
        }
    }
    if (query->distance <= 0x400000) {
        query->distance = 0x400000;
    }
    return TRUE;
}


