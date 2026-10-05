#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionObject {
    u8 pad_00[0x10];
    s32 handle;
} CollisionObject;

typedef struct PlaneBody {
    u8 pad_00[0xb0];
    VecFx32 normal;
    u8 pad_bc[4];
    VecFx32 origin;
} PlaneBody;

typedef struct PlaneContact {
    u8 pad_00[0x14];
    fx16 normalX;
    fx16 normalY;
    fx16 normalZ;
    u8 pad_1a[2];
    fx32 distance;
    u8 pad_20[0x60];
    s32 handle;
} PlaneContact;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void InitPlaneContact(CollisionObject *object, PlaneBody *body, PlaneContact *contact) {
    contact->normalX = body->normal.x;
    contact->normalY = body->normal.y;
    contact->normalZ = body->normal.z;
    contact->distance = VEC_DotProduct(&body->origin, &body->normal);
    contact->handle = object->handle;
}
