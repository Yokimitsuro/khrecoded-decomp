#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollSweep {
    u8 pad_00[0x20];
    VecFx32 delta;
} CollSweep;

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 time;
    u8 surfaceType;
    u8 pad_15[3];
} ContactPlane;

struct CollObject;
struct ContactEntry;
struct Mover;

typedef s32 (*ObjectContactFn)(struct CollObject *object, void *owner, ContactPlane *plane, void *userData, CollSweep *sweep, BOOL moving, ContactPlane *planes, struct ContactEntry *entries, s32 index);
typedef s32 (*MoverContactFn)(struct ContactEntry *entry, ContactPlane *plane, void *userData, CollSweep *sweep, BOOL moving, ContactPlane *planes, struct ContactEntry *entries, s32 index);

typedef struct CollObject {
    u8 pad_00[0x78];
    ObjectContactFn onContact;
    void *userData;
} CollObject;

typedef struct ContactEntry {
    CollObject *object;
    s32 type;
    s32 unk_08;
} ContactEntry;

typedef struct Mover {
    u8 pad_00[0x7c];
    u8 tracksMotion;
    u8 pad_7d[0x17];
    void *owner;
    u8 pad_98[0x18];
    CollSweep *sweep;
    void *contacts;
    u8 pad_b8[4];
    MoverContactFn onContact;
    void *userData;
} Mover;

static inline BOOL IsNonZeroVec(const VecFx32 *vec)
{
    return vec->x != 0 || vec->y != 0 || vec->z != 0;
}

s32 DispatchContactCallbacks(Mover *mover, ContactEntry *entry, s32 index, BOOL *moving, ContactPlane *planes, ContactEntry *entries)
{
    s32 result = 1;

    if (entry->type == 4) {
        CollObject *object = entry->object;
        if (object->onContact != NULL) {
            result = object->onContact(object, mover->owner, &planes[index], object->userData, mover->sweep, *moving, planes, entries, index);
            if (mover->tracksMotion) {
                *moving = IsNonZeroVec(&mover->sweep->delta);
            }
            if (result != 1) {
                return result;
            }
        }
    }
    if (mover->onContact != NULL) {
        result = mover->onContact(entry, &planes[index], mover->userData, mover->sweep, *moving, planes, entries, index);
        if (mover->tracksMotion) {
            *moving = IsNonZeroVec(&mover->sweep->delta);
        }
    }
    return result;
}
