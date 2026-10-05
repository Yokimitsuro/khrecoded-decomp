#include "nitro/types.h"

extern int ForwardType7RecordSpanFromOffset14(int context);
extern u8 *gActorRegistry;

int ApplyRecordTableEntry4(int index) {
    void **slots = (void **)(gActorRegistry + 0x20);
    return ForwardType7RecordSpanFromOffset14((int)slots[index]);
}
