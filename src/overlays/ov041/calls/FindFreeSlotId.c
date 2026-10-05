#include "nitro/types.h"

extern int ActorSlot_GetByIndex(int id);

u32 FindFreeSlotId(void) {
    int inUse;
    u32 id;

    id = 0;
    do {
        inUse = ActorSlot_GetByIndex(id & 0xffff);
        if (inUse == 0) {
            return id & 0xff;
        }
        id = id + 1;
    } while ((int)id < 0x200);
    return 0xff;
}
