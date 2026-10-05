#include "nitro/types.h"

extern void func_020359c4(void *entry);
extern u8 *gActorRegistry;

void ApplyRecordTableEntry3(int index) {
    void **slots = (void **)(gActorRegistry + 0x20);
    func_020359c4(slots[index]);
}
