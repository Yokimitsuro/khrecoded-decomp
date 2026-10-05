#include "nitro/types.h"

typedef struct StageActor StageActor;

typedef struct ActorSlot {
    int state;
    u32 unk_04;
    u16 isActive : 1;
    u16 flags : 15;
    u8 pad_0A[2];
    u16 actorId;
} ActorSlot;

extern StageActor *func_ov001_0209c068(int id);
extern int ReleaseStageSlotEntry(int index, int slot);

void ReleaseSlotActor(ActorSlot *slot)
{
    if (slot->actorId != 0) {
        func_ov001_0209c068((s16)slot->actorId);
        ReleaseStageSlotEntry(3, slot->actorId);
        slot->actorId = 0;
        slot->isActive = FALSE;
        slot->state = 1;
    }
}
