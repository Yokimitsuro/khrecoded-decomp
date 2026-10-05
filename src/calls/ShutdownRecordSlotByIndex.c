#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void Obj_ConditionalShutdown(Container *obj, int arg);
extern u8 *gActorRegistry;

void ShutdownRecordSlotByIndex(int index) {
    Container **slots = (Container **)(gActorRegistry + 0x20);
    Obj_ConditionalShutdown(slots[index], index);
}
