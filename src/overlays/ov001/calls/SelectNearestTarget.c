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
    u32 flags;
    TargetCandidate current;
    u8 pad_18[0x30];
    s32 lockRange;
} Manager;

extern Manager *data_ov001_020a04a4;
extern TargetCandidate *func_ov001_0206b930(TargetCandidate *candidate);
extern TargetSearch *func_ov001_0206ba18(TargetSearch *search);
extern void ScanActorsForNearestTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void ScanObjectsForNearestTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void FindBestEventSlotTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void PickBestPartyTarget(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void SetMenuOpenState(int mode, int flag);

void SelectNearestTarget(void)
{
    Manager *manager = data_ov001_020a04a4;
    TargetCandidate candidate;
    TargetSearch search;

    if (manager->flags & 1) {
        SetMenuOpenState(1, 1);
        return;
    }
    func_ov001_0206b930(&candidate);
    func_ov001_0206ba18(&search);
    ScanActorsForNearestTarget(&candidate, &search, NULL, manager->lockRange);
    ScanObjectsForNearestTarget(&candidate, &search, NULL, manager->lockRange);
    FindBestEventSlotTarget(&candidate, &search, NULL, manager->lockRange);
    PickBestPartyTarget(&candidate, &search, NULL, manager->lockRange);
    if (candidate.object != 0) {
        manager->current = candidate;
        SetMenuOpenState(1, 1);
    }
}
