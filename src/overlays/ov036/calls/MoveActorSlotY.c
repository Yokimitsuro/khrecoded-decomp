#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    u8 pad_00[0x6];
    s16 height;
    u8 pad_08[0xc];
    fx32 posY;
    u8 pad_18[0x18];
    fx32 moveFrom;
    fx32 moveTo;
    s32 moveMode;
    s32 moveAxis;
    s32 moveDuration;
    s32 moveTimer;
    u8 pad_48[0x40];
    u16 flags;
    u8 pad_8A[0x12];
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
    u8 pad_0C84[0x40c];
    ActorSlot *slots;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

extern ActorSlotContext data_ov036_020c3940;
extern int FindOrAcquireOwnerSlot(int actorId);
extern int func_ov036_020bb8ec(int blockIndex);

void MoveActorSlotY(int actorId, int startY, int endY, s32 duration)
{
    ActorSlotWork *work = data_ov036_020c3940.work;
    ActorSlot *slot = &work->slots[FindOrAcquireOwnerSlot(actorId)];
    fx32 from = startY << 12;
    fx32 to = endY << 12;
    fx32 offscreenY = func_ov036_020bb8ec(slot->height);

    if (work->skipAnimations != 0) {
        duration = 0;
    }
    switch (startY) {
    case -1000:
        from = offscreenY;
        break;
    case -100:
        from = slot->posY;
        break;
    case 1000:
        from = offscreenY + (slot->height << 12);
        break;
    }
    switch (endY) {
    case -1000:
        to = from + (slot->height << 12);
        break;
    case 1000:
        to = func_ov036_020bb8ec(slot->height);
        break;
    }
    if (slot->posY == to) {
        return;
    }
    if (duration == 0) {
        slot->posY = to;
        return;
    }
    if (slot->flags & 1) {
        return;
    }
    slot->moveFrom = from;
    slot->posY = from;
    slot->moveTo = to;
    slot->moveDuration = duration;
    slot->moveTimer = duration;
    slot->moveMode = (from > to) ? 5 : 4;
    slot->moveAxis = 1;
    slot->flags |= 1;
}
