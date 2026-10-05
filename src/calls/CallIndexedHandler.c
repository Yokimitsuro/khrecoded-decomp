#include "nitro/types.h"

typedef struct {
    u32 (*handler)(void);
    u8 pad_04[0x14];
} HandlerEntry;

extern HandlerEntry gBg0TransferDispatch[];

/* Calls a handler by index if present. */
u32 CallIndexedHandler(s32 index)
{
    u32 (*handler)(void) = gBg0TransferDispatch[index].handler;

    if (handler != NULL) {
        return handler();
    }
    return 0;
}
