#include "nitro/types.h"

typedef struct Resource {
    u8 pad_000[0x628];
    s32 ready;
} Resource;

extern int IsScreenModeIdle(void);
extern void SetScreenFlag200(int arg);

BOOL IsResourceReadyOrInitialize(Resource *resource)
{
    if (resource->ready != 0) {
        return TRUE;
    }
    if (IsScreenModeIdle() != 0) {
        SetScreenFlag200(0);
        return TRUE;
    }
    return FALSE;
}
