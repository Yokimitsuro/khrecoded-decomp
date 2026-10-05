#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitMessage {
    VecFx32 direction;
    u8 flagA;
    u8 flagB;
    s32 power;
    s32 unk_14;
    s32 unk_18;
} HitMessage;

typedef struct HitTarget {
    u8 pad_00[0x68];
    int entry;
    s32 kind;
} HitTarget;

typedef struct ContactRef {
    void *target;
    s32 kind;
} ContactRef;

typedef struct HitQuery {
    u8 pad_00[4];
    VecFx32 direction;
} HitQuery;

extern const VecFx32 data_0205344c;

extern BOOL IsFacingContactNormal(ContactRef *ref, const VecFx32 *direction);
extern u32 func_ov001_02086408(int entry, HitMessage *message);

BOOL HandleContactHit(ContactRef *ref, HitQuery *query)
{
    HitTarget *target;
    HitMessage message;

    if (ref->kind == 4) {
        target = ref->target;
        if (target->kind == 0x1e) {
            message.direction = data_0205344c;
            message.flagA = 0;
            message.flagB = 0;
            message.unk_14 = 0;
            message.unk_18 = 0;
            message.power = 100;
            func_ov001_02086408(target->entry, &message);
        }
        return FALSE;
    }
    if (IsFacingContactNormal(ref, &query->direction)) {
        return TRUE;
    }
    return FALSE;
}
