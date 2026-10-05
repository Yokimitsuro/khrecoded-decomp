#include "nitro/types.h"

extern int ForwardType7RecordSpanFromOffset14(int context);
extern u8 *data_0206083c;

int ApplyRecordTableEntry4(int index) {
    void **slots = (void **)(data_0206083c + 0x20);
    return ForwardType7RecordSpanFromOffset14((int)slots[index]);
}
