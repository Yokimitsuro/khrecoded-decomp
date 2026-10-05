#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    u16 unk_0c;
    u16 unk_0e;
    u16 next;
    u16 unk_12;
} SlotPoint;

typedef struct {
    u32 kind;
    union {
        u8 *object;
        struct {
            u16 stageId;
            u16 slot;
        } path;
    } source;
} TargetSource;

typedef struct {
    u32 unk_00;
    TargetSource target;
    u8 pad_0c[0x38 - 0x0c];
    s16 goalSlot;
} CameraTargetState;

extern CameraTargetState *data_ov001_020a04a4;

extern VecFx32 *func_ov001_0207f898(u8 *object);
extern VecFx32 *func_ov001_0208641c(u8 *object);
extern BOOL StageRecord_GetSlotPosition(u32 id, u32 slot, SlotPoint *outPoint);
extern void func_ov001_0206b948(TargetSource *target, s16 stageId, s16 slot);

BOOL ResolveCameraTargetPosition(VecFx32 *out) {
    CameraTargetState *state = data_ov001_020a04a4;
    TargetSource *target = &state->target;
    BOOL result = FALSE;
    VecFx32 *position;
    SlotPoint point;
    u16 slot;
    BOOL searching;

    switch (state->target.kind) {
    case 2:
        position = func_ov001_0207f898(target->source.object);
        *out = *position;
        break;
    case 3:
        position = func_ov001_0208641c(target->source.object);
        *out = *position;
        break;
    case 1:
        slot = target->source.path.slot;
        searching = TRUE;
        do {
            StageRecord_GetSlotPosition(target->source.path.stageId, slot, &point);
            if (point.next != state->goalSlot) {
                if (StageRecord_GetSlotPosition(target->source.path.stageId, point.next, NULL)) {
                    func_ov001_0206b948(target, target->source.path.stageId, point.next);
                    result = TRUE;
                    searching = FALSE;
                } else {
                    slot = point.next;
                }
            } else {
                *out = point.position;
                searching = FALSE;
            }
        } while (searching);
        break;
    case 4:
        *out = *(VecFx32 *)(target->source.object + 0xbc);
        break;
    }
    return result;
}
