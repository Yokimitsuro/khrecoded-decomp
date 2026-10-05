#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollShape {
    u8 pad_00[0x1c];
    int kind;
    VecFx32 velocity;
    VecFx32 max;
    VecFx32 min;
} CollShape;

typedef struct BoxShape {
    u8 pad_00[4];
    VecFx32 max;
    VecFx32 min;
    int kind;
} BoxShape;

typedef struct Kind7Entry {
    u8 pad_00[0x10];
    BoxShape box;
    u8 pad_30[0x20];
    s8 state;
    u8 pad_51;
    s8 lockCount;
    u8 pad_53;
    u16 flags;
} Kind7Entry;

typedef int (*TouchFn)(BoxShape *self, CollShape *other, void *context, int flags);
typedef int (*ResolveFn)(BoxShape *self, CollShape *other, void *context, int flags, VecFx32 *push);

extern TouchFn gCollisionTestPairDispatch[][6];
extern ResolveFn gCollisionSweepPairDispatch[][6];
extern void NegateVecFx32(VecFx32 *vec);

int CollideKind7Entry(Kind7Entry *entry, CollShape *other, void *context)
{
    VecFx32 reverse;
    VecFx32 push;
    int result;

    if (entry->flags & 8) {
        return 0;
    }
    if (entry->lockCount > 0) {
        return 0;
    }
    if (entry->state == 0 && entry->box.kind >= 0) {
        if (entry->box.max.x >= other->min.x && entry->box.min.x <= other->max.x && entry->box.max.z >= other->min.z &&
            entry->box.min.z <= other->max.z && entry->box.max.y >= other->min.y && entry->box.min.y <= other->max.y) {
            if (other->velocity.x == 0 && other->velocity.y == 0 && other->velocity.z == 0) {
                result = 2;
            } else {
                reverse = other->velocity;
                NegateVecFx32(&reverse);
                push = reverse;
                result = 1;
            }
        } else {
            result = 0;
        }
        if (result != 0) {
            if (result == 2) {
                return gCollisionTestPairDispatch[entry->box.kind][other->kind](&entry->box, other, context, (other->kind == 2 ? 2 : 0) | 8);
            }
            return gCollisionSweepPairDispatch[entry->box.kind][other->kind](&entry->box, other, context, 8, &push);
        }
        return 0;
    }
    return 0;
}
