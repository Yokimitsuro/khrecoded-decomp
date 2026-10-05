#include "nitro/types.h"

extern void func_020369a8(void *entry);
extern u8 *data_0206083c;

void ClearRecordSlotFlag(int index) {
    void **slots = (void **)(data_0206083c + 0x20);
    func_020369a8(slots[index]);
}
