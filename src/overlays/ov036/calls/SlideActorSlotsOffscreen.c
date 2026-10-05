#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    u8 pad_00[0x10];
    fx32 posX;
    u8 pad_14[0x24];
    s32 moveMode;
    s32 moveAxis;
    u8 pad_40[0x4c];
    s32 ownerId;
    u8 pad_90[0xc];
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0x1090];
    ActorSlot *slots;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

extern ActorSlotContext data_ov036_020c3940;
extern void MoveActorSlotX(int actorId, int startX, int endX, s32 duration);

void SlideActorSlotsOffscreen(void)
{
    ActorSlotWork *work = data_ov036_020c3940.work;
    ActorSlot *slot;
    int i;

    for (i = 0; i < 8; i++) {
        int x;

        slot = &work->slots[i];
        if (slot->ownerId == -1) {
            continue;
        }
        x = slot->posX >> 12;
        if (x == -1000 || x == 1000) {
            continue;
        }
        if (x <= 0x80) {
            MoveActorSlotX(slot->ownerId, x, -1000, 10);
        } else {
            MoveActorSlotX(slot->ownerId, x, 1000, 10);
        }
        slot->moveMode = 2;
        slot->moveAxis = 0;
    }
}
