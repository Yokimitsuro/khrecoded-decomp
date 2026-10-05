#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 group;
    u8 index;
} TargetInfo;

typedef struct {
    u8 pad0[0x194];
    TargetInfo info;
} TargetOwner;

typedef struct {
    u8 pad0[0x14];
    TargetOwner *owner;
} LockTarget;

typedef struct {
    u8 pad0[0x10];
    LockTarget *target;
    u8 pad14[0xb0];
    int lockMode;
} LockOnInfo;

typedef struct {
    u8 pad0[0x234];
    u32 lockFlags;
    u8 pad238[0x3c];
    LockOnInfo lock;
    u8 pad33c[0x9ac - 0x33c];
    u64 flags;
} Actor;

extern u32 func_ov001_0208724c(u32 group, u32 index);
extern BOOL IsFieldUnitAction7(u32 unit);

BOOL IsLockedOnActiveFieldUnit(Actor *actor)
{
    u32 locking = actor->lockFlags & 4;
    BOOL result = FALSE;
    LockOnInfo *lock;
    if ((actor->flags & 0x100020820ULL) != 0) {
        return FALSE;
    }
    if (locking && (lock = &actor->lock)->lockMode == 1) {
        TargetOwner *owner = lock->target->owner;
        TargetInfo *info = &owner->info;
        if (info->kind == 4) {
            u32 unit = func_ov001_0208724c(info->group, info->index);
            if (*(u8 *)(*(int *)(unit + 4) + 0x5a) == 9 && IsFieldUnitAction7(unit)) {
                result = TRUE;
            }
        }
    }
    return result;
}
