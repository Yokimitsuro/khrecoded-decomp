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

typedef struct TargetScore {
    s32 distance;
    s32 priority;
    s32 valid;
} TargetScore;

typedef struct Manager {
    u32 flags;
} Manager;

extern Manager *data_ov001_020a04a4;
extern u32 func_ov001_0206e280(void);
extern TargetObject *func_ov001_02087264(void);
extern BOOL func_ov001_0206b614(void *origin, TargetObject *object, s32 range);
extern VecFx32 *func_ov001_0208641c(TargetObject *object);
extern void ClassifyTargetRange(void *origin, VecFx32 *position, TargetScore *score, s32 kind);
extern BOOL func_ov001_0206bb48(TargetScore *best, TargetScore *score);
extern TargetCandidate *func_ov001_0206b940(TargetCandidate *candidate, TargetObject *object);

void ScanObjectsForNearestTarget(TargetCandidate *candidate, TargetScore *best, void *origin, s32 range)
{
    TargetObject *object;
    TargetScore score;

    if (!func_ov001_0206e280()) {
        return;
    }
    if (origin == NULL && !(data_ov001_020a04a4->flags & 0x40)) {
        return;
    }
    for (object = func_ov001_02087264(); object != NULL; object = object->next) {
        if (func_ov001_0206b614(origin, object, range)) {
            ClassifyTargetRange(origin, func_ov001_0208641c(object), &score, 3);
            if (func_ov001_0206bb48(best, &score)) {
                func_ov001_0206b940(candidate, object);
                *best = score;
            }
        }
    }
}
