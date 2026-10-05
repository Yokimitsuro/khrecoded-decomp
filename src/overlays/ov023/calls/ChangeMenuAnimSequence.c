#include "nitro/types.h"

typedef struct MenuAnimSlot {
    int slot;
    int sequence;
} MenuAnimSlot;

extern void SetSlotAnimSequence(void *owner, int slot, int sequence, u32 mode);
extern void func_0204f18c(void *owner, int slot, u8 mode);

void ChangeMenuAnimSequence(void *owner, MenuAnimSlot *anim, int sequence, u32 mode)
{
    if (anim->sequence != sequence) {
        SetSlotAnimSequence(owner, anim->slot, sequence, mode);
        anim->sequence = sequence;
        func_0204f18c(owner, anim->slot, mode);
    }
}
