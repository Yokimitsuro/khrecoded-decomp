#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RecordInfo {
    u16 itemId;
    u16 flagsLow : 3;
    u16 hidden : 1;
    u16 flagsHigh : 12;
    u8 pad_04[0x20];
} RecordInfo;

typedef struct SlotPosition {
    VecFx32 position;
    u8 pad_0c[4];
    u16 nextSlot;
    u8 pad_12[2];
} SlotPosition;

typedef struct EventFlags {
    u32 flags;
} EventFlags;

extern EventFlags *data_ov001_020a04a4;
extern u32 func_ov001_0206e280(void);
extern s32 ForwardToActiveServiceWithResult(void);
extern s32 func_ov001_0208796c(s32 startIndex);
extern BOOL func_ov001_02087988(s32 recordId, RecordInfo *info);
extern BOOL StageRecord_GetSlotPosition(s32 id, u32 slot, SlotPosition *outPoint);
extern BOOL IsEventSlotInRange(void *origin, s32 recordId, u32 slot, fx32 range);
extern void ClassifyTargetRange(void *origin, SlotPosition *slot, VecFx32 *target, s32 kind);
extern BOOL func_ov001_0206bb48(VecFx32 *best, VecFx32 *candidate);
extern void func_ov001_0206b948(void *owner, int recordId, int slot);

void FindBestEventSlotTarget(void *owner, VecFx32 *best, void *origin, fx32 range)
{
    u32 slot;
    int shortId;
    s32 recordId;
    SlotPosition slotPos;
    RecordInfo info;
    VecFx32 target;

    if (func_ov001_0206e280() == 0) {
        return;
    }
    if (origin == NULL && !(data_ov001_020a04a4->flags & 0x80)) {
        return;
    }
    for (recordId = ForwardToActiveServiceWithResult(); recordId != 0; recordId = func_ov001_0208796c(recordId)) {
        if (func_ov001_02087988(recordId, &info) && info.hidden) {
            continue;
        }
        slotPos.nextSlot = 0;
        shortId = (s16)recordId;
        do {
            slot = slotPos.nextSlot;
            if (StageRecord_GetSlotPosition(recordId, slot, &slotPos)
                && IsEventSlotInRange(origin, recordId, slot, range)) {
                ClassifyTargetRange(origin, &slotPos, &target, 1);
                if (func_ov001_0206bb48(best, &target)) {
                    func_ov001_0206b948(owner, shortId, (s16)slot);
                    *best = target;
                }
            }
        } while (slotPos.nextSlot != 0);
    }
}
