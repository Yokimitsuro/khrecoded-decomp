#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageController {
    u8 pad_00[0xa];
    u16 eventId;
} StageController;

typedef struct StageActor {
    u8 pad_000[0x1d2];
    u16 controllerId;
    u8 pad_1d4[0x28c - 0x1d4];
    u16 lowBits : 11;
    u16 anchorId : 3;
    u16 highBits : 2;
} StageActor;

extern StageController *GetStageController(u32 id);
extern u8 *func_ov001_0209c114(u32 id);
extern void func_ov001_02099080(u32 id, VecFx32 *outPosition);
extern void ChooseWanderDestination(u8 *record, StageActor *actor, VecFx32 *position);

void PlaceActorAtStageAnchor(StageActor *actor, int unused, VecFx32 *position)
{
    StageController *controller = GetStageController(actor->controllerId);
    u8 *record = NULL;

    if (controller != NULL && controller->eventId != 0) {
        record = func_ov001_0209c114(controller->eventId);
    }
    func_ov001_02099080(actor->anchorId, position);
    if (record != NULL) {
        ChooseWanderDestination(record, actor, position);
    }
}
