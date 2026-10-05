#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPosition {
    VecFx32 position;
    u32 extra[2];
} SlotPosition;

typedef struct WaitSubject {
    u8 pad_00[0xbc];
    VecFx32 position;
} WaitSubject;

typedef struct WaitTarget {
    u8 kind;
    u8 pad_01[3];
    union {
        struct {
            u16 eventId;
            u16 slot;
        } event;
        int entry;
        WaitSubject *subject;
    } u;
    VecFx32 position;
} WaitTarget;

extern int IsStageEventReady(u32 id);
extern BOOL StageRecord_GetSlotPosition(u32 id, u32 slot, SlotPosition *outPosition);
extern VecFx32 *func_ov001_0207f898(int entry);
extern VecFx32 *func_ov001_0208641c(int entry);

VecFx32 *GetWaitTargetPosition(WaitTarget *target)
{
    SlotPosition slot;
    VecFx32 *source;

    switch (target->kind) {
    case 1:
        if (IsStageEventReady(target->u.event.eventId)) {
            StageRecord_GetSlotPosition(target->u.event.eventId, target->u.event.slot, &slot);
            target->position = slot.position;
        }
        break;
    case 2:
        source = func_ov001_0207f898(target->u.entry);
        if (source != NULL) {
            target->position = *source;
        }
        break;
    case 3:
        source = func_ov001_0208641c(target->u.entry);
        if (source != NULL) {
            target->position = *source;
        }
        break;
    case 4:
        source = &target->u.subject->position;
        if (source != NULL) {
            target->position = *source;
        }
        break;
    }
    return &target->position;
}
