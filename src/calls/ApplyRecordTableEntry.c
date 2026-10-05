#include "nitro/types.h"

extern void ActorEntry_SetModel(void *entry, int a1, int a2, int a3);
extern u8 *gActorRegistry;

void ApplyRecordTableEntry(int index, int a1, int a2, int a3) {
    void **slots = (void **)(gActorRegistry + 0x20);
    ActorEntry_SetModel(slots[index], a1, a2, a3);
}
