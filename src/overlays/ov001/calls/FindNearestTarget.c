#include "nitro/types.h"

typedef struct TargetCandidate {
    s32 object;
    u8 pad_04[0x10];
} TargetCandidate;

typedef struct TargetSearch {
    s32 bestDistance;
    s32 bestIndex;
    s32 unk_08;
} TargetSearch;

extern TargetCandidate *func_ov001_0206b930(TargetCandidate *candidate);
extern TargetSearch *func_ov001_0206ba18(TargetSearch *search);
extern void func_ov001_0206b598(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206b744(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern BOOL ResolveWaitTarget(TargetCandidate *candidate, void *target);

BOOL FindNearestTarget(void *target, void *origin, u32 kinds)
{
    TargetCandidate candidate;
    TargetSearch search;
    BOOL found = FALSE;

    func_ov001_0206b930(&candidate);
    func_ov001_0206ba18(&search);
    if (kinds & 1) {
        func_ov001_0206b598(&candidate, &search, origin, 0x9000);
    }
    if (kinds & 2) {
        func_ov001_0206b744(&candidate, &search, origin, 0x6000);
    }
    if (candidate.object != 0 && ResolveWaitTarget(&candidate, target)) {
        found = TRUE;
    }
    return found;
}
