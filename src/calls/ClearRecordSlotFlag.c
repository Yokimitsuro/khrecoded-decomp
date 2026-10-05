#include "nitro/types.h"

extern void func_020369a8(void *entry);
extern u8 *gActorRegistry;

void ClearRecordSlotFlag(int index) {
    void **slots = (void **)(gActorRegistry + 0x20);
    func_020369a8(slots[index]);
}
