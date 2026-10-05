#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPoint {
    VecFx32 position;
    u32 unk_0C;
    u16 nextSlot;
    u16 pad_12;
} SlotPoint;

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
extern s32 ForwardToActiveServiceWithResult(void);
extern s32 func_ov001_0208796c(s32 startIndex);
extern BOOL StageRecord_GetSlotPosition(u32 id, u32 slot, void *outPoint);
extern BOOL IsEventSlotInRange(void *origin, s32 recordId, u16 slot, s32 range);
extern BOOL CheckSideOffsetInRange(const VecFx32 *position, const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern TargetCandidate *func_ov001_0206b948(TargetCandidate *candidate, s16 recordId, s16 slot);

BOOL ScanRecordSlotsForSideTarget(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset)
{
    Manager *manager = data_ov001_020a04a4;
    BOOL found = FALSE;
    s32 recordId;
    u16 slot;
    SlotPoint point;

    if (!(manager->flags & 0x80)) {
        return found;
    }
    for (recordId = ForwardToActiveServiceWithResult(); recordId != 0; recordId = func_ov001_0208796c(recordId)) {
        s16 shortId;

        point.nextSlot = 0;
        shortId = recordId;
        do {
            slot = point.nextSlot;
            if (StageRecord_GetSlotPosition(recordId, slot, &point) &&
                IsEventSlotInRange(NULL, recordId, slot, manager->lockRange) &&
                CheckSideOffsetInRange(&point.position, facing, low, high, direction, outOffset)) {
                func_ov001_0206b948(&manager->current, shortId, slot);
                high = *outOffset;
                found = TRUE;
            }
        } while (point.nextSlot != 0);
    }
    return found;
}
