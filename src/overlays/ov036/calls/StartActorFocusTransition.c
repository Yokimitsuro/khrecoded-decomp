#include "nitro/types.h"

typedef struct ActorSlot {
    u8 pad_00[0x20];
    s32 depth;
    u8 pad_24[0x68];
    int actorId;
    u8 pad_90[0xc];
} ActorSlot;

typedef struct FocusState {
    u8 pad_00[0x34];
    s32 step;
    s32 mode;
    s32 active;
} FocusState;

typedef struct ActorSlotWork {
    u8 pad_0000[0x1090];
    ActorSlot *slots;
    u8 pad_1094[0x8];
    FocusState focus;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

extern ActorSlotContext data_ov036_020c3940;
extern s32 _s32_div_f(s32 numerator, s32 denominator);

void StartActorFocusTransition(int focusActorId, s32 focusMode, s32 frameCount)
{
    ActorSlotWork *work = data_ov036_020c3940.work;
    FocusState *focus = &work->focus;
    int slotIndex;

    focus->mode = focusMode;
    focus->active = 1;
    focus->step = _s32_div_f(0x18, frameCount);
    if (focus->mode == 0) {
        focus->step = -focus->step;
    }
    if (focus->mode == 0) {
        return;
    }
    for (slotIndex = 0; slotIndex < 8; slotIndex++) {
        ActorSlot *slot = &work->slots[slotIndex];
        if (slot->actorId != -1) {
            if (focusActorId == slot->actorId) {
                slot->depth = 0x330;
            } else {
                slot->depth += 0x19a;
            }
        }
    }
}
