#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetObject {
    struct TargetObject *next;
} TargetObject;

typedef struct TargetCandidate {
    s32 kind;
    void *object;
    u8 pad_08[0xc];
} TargetCandidate;

typedef struct Manager {
    u32 flags;
    TargetCandidate current;
    u8 pad_18[0x30];
    s32 lockRange;
} Manager;

extern Manager *data_ov001_020a04a4;
extern TargetObject *func_ov001_02087264(void);
extern BOOL func_ov001_0206b614(void *origin, TargetObject *object, s32 range);
extern VecFx32 *func_ov001_0208641c(TargetObject *object);
extern BOOL CheckSideOffsetInRange(const VecFx32 *position, const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern TargetCandidate *func_ov001_0206b940(TargetCandidate *candidate, TargetObject *object);

BOOL ScanObjectsForSideTarget(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset)
{
    Manager *manager = data_ov001_020a04a4;
    BOOL found = FALSE;
    TargetObject *object;

    if (!(manager->flags & 0x40)) {
        return found;
    }
    for (object = func_ov001_02087264(); object != NULL; object = object->next) {
        if (func_ov001_0206b614(NULL, object, manager->lockRange) &&
            CheckSideOffsetInRange(func_ov001_0208641c(object), facing, low, high, direction, outOffset)) {
            func_ov001_0206b940(&manager->current, object);
            high = *outOffset;
            found = TRUE;
        }
    }
    return found;
}
