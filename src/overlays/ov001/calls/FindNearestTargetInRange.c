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

typedef struct Manager {
    u8 pad_00[0x4c];
    s32 searchRange;
} Manager;

extern Manager *data_ov001_020a04a4;
extern TargetCandidate *func_ov001_0206b930(TargetCandidate *candidate);
extern TargetSearch *func_ov001_0206ba18(TargetSearch *search);
extern void ScanActorsForNearestTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void ScanObjectsForNearestTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void FindBestEventSlotTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void PickBestPartyTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);

BOOL FindNearestTargetInRange(TargetCandidate *result, void *origin)
{
    Manager *manager = data_ov001_020a04a4;
    BOOL found = FALSE;
    TargetCandidate candidate;
    TargetSearch search;

    func_ov001_0206b930(&candidate);
    func_ov001_0206ba18(&search);
    ScanActorsForNearestTarget(&candidate, &search, origin, manager->searchRange);
    ScanObjectsForNearestTarget(&candidate, &search, origin, manager->searchRange);
    FindBestEventSlotTarget(&candidate, &search, origin, manager->searchRange);
    PickBestPartyTarget(&candidate, &search, origin, manager->searchRange);
    if (candidate.object != 0) {
        *result = candidate;
        found = TRUE;
    }
    return found;
}
