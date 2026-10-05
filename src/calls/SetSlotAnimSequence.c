#include "nitro/types.h"

typedef struct AnimElement {
    u8 pad_00[0x14];
    const void *animBank;
} AnimElement;

typedef struct AnimSlot {
    u8 cellAnim[0x60];
    int elementIndex;
    u8 pad_64[0x28];
} AnimSlot;

typedef struct SlotOwner {
    u8 pad_00[0x18];
    AnimSlot slots[1];
} SlotOwner;

extern AnimElement *GetElementAddress(SlotOwner *owner, int index);
extern const void *NNS_G2dGetAnimSequenceByIdx(const void *animBank, u16 index);
extern void NNS_G2dSetCellAnimationSequence(void *cellAnim, const void *sequence);

void SetSlotAnimSequence(SlotOwner *owner, int slot, int sequence)
{
    AnimElement *element;

    if (slot < 0) {
        return;
    }
    element = GetElementAddress(owner, owner->slots[slot].elementIndex);
    NNS_G2dSetCellAnimationSequence(owner->slots[slot].cellAnim,
        NNS_G2dGetAnimSequenceByIdx(element->animBank, sequence));
}
