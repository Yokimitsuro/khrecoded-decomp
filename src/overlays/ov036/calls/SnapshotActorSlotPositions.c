#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPoint {
    fx32 x;
    fx32 y;
} SlotPoint;

typedef struct SlotEntry {
    u8 pad_00[0x10];
    SlotPoint pos;
    u8 pad_18[0x60];
    SlotPoint savedPos;
    u8 pad_80[0xc];
    s32 ownerId;
    u8 pad_90[0xc];
} SlotEntry;

typedef struct PanelWork {
    u8 pad_0000[0x658];
    u8 subVm[0x628];
    s32 isBusy;
    u8 pad_0C84[0x40c];
    SlotEntry *slots;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern void MarkPendingActionIfTargetSet(void *vm);

s32 SnapshotActorSlotPositions(void)
{
    int i;
    PanelWork *work = data_ov036_020c3940.work;

    MarkPendingActionIfTargetSet(work->subVm);
    for (i = 0; i < 8; i++) {
        SlotEntry *slot = &work->slots[i];
        if (slot->ownerId != -1) {
            slot->savedPos = slot->pos;
        }
    }
    return data_ov036_020c3940.work->isBusy;
}
