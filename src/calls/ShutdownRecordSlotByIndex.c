#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void Obj_ConditionalShutdown(Container *obj, int arg);
extern u8 *data_0206083c;

void ShutdownRecordSlotByIndex(int index) {
    Container **slots = (Container **)(data_0206083c + 0x20);
    Obj_ConditionalShutdown(slots[index], index);
}
