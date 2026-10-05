#include "nitro/types.h"

typedef struct Resource {
    u8 pad_000[0x628];
    s32 ready;
} Resource;

extern int func_ov001_0206a814(void);
extern void func_ov001_0206a834(int arg);

BOOL IsResourceReadyOrInitialize(Resource *resource)
{
    if (resource->ready != 0) {
        return TRUE;
    }
    if (func_ov001_0206a814() != 0) {
        func_ov001_0206a834(0);
        return TRUE;
    }
    return FALSE;
}
