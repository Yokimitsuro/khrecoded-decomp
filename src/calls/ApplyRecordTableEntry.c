#include "nitro/types.h"

extern void ActorEntry_SetModel(void *entry, int a1, int a2, int a3);
extern u8 *data_0206083c;

void ApplyRecordTableEntry(int index, int a1, int a2, int a3) {
    void **slots = (void **)(data_0206083c + 0x20);
    ActorEntry_SetModel(slots[index], a1, a2, a3);
}
