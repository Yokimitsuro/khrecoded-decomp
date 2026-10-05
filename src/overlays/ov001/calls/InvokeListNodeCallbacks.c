#include "nitro/types.h"

typedef void (*Callback)(void *node);

extern u32 data_ov001_020a04f8;
extern void func_ov001_020871b8(void);

void InvokeListNodeCallbacks(void)
{
    u8 *node;
    Callback callback;

    for (node = *(u8 **)(data_ov001_020a04f8 + 8); node != 0; node = *(u8 **)(node + 4)) {
        callback = *(Callback *)(*(u8 **)(node + 8) + 0x40);
        if (callback != 0) {
            (*callback)(node);
        }
    }
    func_ov001_020871b8();
}
