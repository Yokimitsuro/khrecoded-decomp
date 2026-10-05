#include "nitro/types.h"

extern void func_020359c4(void *entry);
extern u8 *data_0206083c;

void ApplyRecordTableEntry3(int index) {
    void **slots = (void **)(data_0206083c + 0x20);
    func_020359c4(slots[index]);
}
