#include "nitro/types.h"

typedef struct SlotState {
    int timer;
    int unk4;
    int unk8;
    int id;
    int mode;
} SlotState;

typedef struct SlotOwner {
    u8 pad[0xd0];
    int count;
} SlotOwner;

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsFieldFlag8Set(void);
extern SlotState *CycleMenuEntry(SlotOwner *owner, int index, int create, int flags);

void AdvanceActiveSlotTimers(SlotOwner *owner) {
    SlotState *slot;
    int i;

    if (IsModeSetOrFlag370aClear() && !IsHudFlag7Set() &&
        !IsFieldFlag10Set() && !IsFieldFlag8Set()) {
        for (i = 0; i < owner->count; i++) {
            slot = CycleMenuEntry(owner, i, 1, 0);
            if (slot->id != -1 && slot->mode != 3) {
                slot->timer += 2;
            }
        }
    }
}
