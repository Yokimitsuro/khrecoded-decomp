#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    u8 pad_00[0x6];
    s16 baseY;
    u8 pad_08[0x8];
    fx32 posX;
    u8 pad_14[0x88];
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0x1090];
    ActorSlot *slots;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

typedef struct SlotPosition {
    fx32 x;
    fx32 y;
} SlotPosition;

extern ActorSlotContext data_ov036_020c3940;
extern int func_ov036_020bb7e0(int actorId);

void GetActorSlotPosition(SlotPosition *outPosition, int actorId)
{
    ActorSlotWork *work = data_ov036_020c3940.work;
    ActorSlot *slot = &work->slots[func_ov036_020bb7e0(actorId)];
    SlotPosition position;

    position.x = slot->posX;
    position.y = slot->baseY << 12;
    *outPosition = position;
}
