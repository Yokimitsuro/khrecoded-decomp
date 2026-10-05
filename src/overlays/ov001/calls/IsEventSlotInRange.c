#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPosition {
    VecFx32 position;
    u32 extra[2];
} SlotPosition;

extern VecFx32 *func_ov001_0206dc4c(int context);
extern int IsStageEventReady(u32 id);
extern BOOL StageRecord_GetSlotPosition(u16 eventId, u16 slot, SlotPosition *outPosition);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL IsEventSlotInRange(int context, int eventId, int slot, fx32 range)
{
    VecFx32 *origin = func_ov001_0206dc4c(context);
    SlotPosition slotPosition;

    if (!IsStageEventReady((u16)eventId)) {
        return FALSE;
    }
    if (!StageRecord_GetSlotPosition(eventId, slot, &slotPosition)) {
        return FALSE;
    }
    if (VEC_Distance(&slotPosition.position, origin) > range) {
        return FALSE;
    }
    return TRUE;
}
