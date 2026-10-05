#include "nitro/types.h"

typedef struct Resource {
    u8 pad_000[0x628];
    s32 ready;
} Resource;

extern int IsSceneState4(void);

BOOL IsResourceReadyOrInitialize_020be790(Resource *resource)
{
    if (resource->ready != 0) {
        return TRUE;
    }
    if (IsSceneState4() == 0) {
        return TRUE;
    }
    return FALSE;
}
