#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetActor {
    u8 pad_00[4];
    struct TargetActor *next;
} TargetActor;

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
extern TargetActor *func_ov001_0207f0b4(void);
extern BOOL func_ov001_0206b4a4(void *origin, TargetActor *actor, s32 range);
extern VecFx32 *func_ov001_0207f898(TargetActor *actor);
extern BOOL CheckSideOffsetInRange(const VecFx32 *position, const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern TargetCandidate *func_ov001_0206b938(TargetCandidate *candidate, TargetActor *actor);

BOOL ScanActorsForSideTarget(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset)
{
    Manager *manager = data_ov001_020a04a4;
    BOOL found = FALSE;
    TargetActor *actor;

    for (actor = func_ov001_0207f0b4(); actor != NULL; actor = actor->next) {
        if (func_ov001_0206b4a4(NULL, actor, manager->lockRange) &&
            CheckSideOffsetInRange(func_ov001_0207f898(actor), facing, low, high, direction, outOffset)) {
            func_ov001_0206b938(&manager->current, actor);
            high = *outOffset;
            found = TRUE;
        }
    }
    return found;
}
