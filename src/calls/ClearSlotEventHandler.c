#include "nitro/types.h"

extern int func_02011460(int slot, void (*callback)(void *), void *arg);

int ClearSlotEventHandler(void *record)
{
    u16 *handlerActive;
    u16 slot;

    if (record == NULL) {
        return 6;
    }
    handlerActive = (u16 *)((u8 *)record + 0x80e);
    if (*handlerActive == 0) {
        return 3;
    }
    slot = *(u16 *)((u8 *)record + 0x816);
    func_02011460(slot, 0, 0);
    *handlerActive = 0;
    *(u16 *)((u8 *)record + 0x81c) = 0;
    return 0;
}
