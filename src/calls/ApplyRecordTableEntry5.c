#include "nitro/types.h"

extern void func_02035a2c(void *entry, int param2, int param3);
extern u8 *data_0206083c;

void ApplyRecordTableEntry5(int index, int param2, int param3) {
    void **slots = (void **)(data_0206083c + 0x20);
    func_02035a2c(slots[index], param2, param3);
}
