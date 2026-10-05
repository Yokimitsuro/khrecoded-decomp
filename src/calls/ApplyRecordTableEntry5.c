#include "nitro/types.h"

extern void ActorSlot_PlaceAndLink(void *entry, int param2, int param3);
extern u8 *gActorRegistry;

void ApplyRecordTableEntry5(int index, int param2, int param3) {
    void **slots = (void **)(gActorRegistry + 0x20);
    ActorSlot_PlaceAndLink(slots[index], param2, param3);
}
