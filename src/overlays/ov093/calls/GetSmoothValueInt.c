#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 target;
    fx32 current;
} SmoothValue;

typedef struct {
    u8 pad_0000[0xd1e4];
    SmoothValue smoothValues[2];
} SceneWork;

extern SceneWork *data_ov093_020c5100;

int GetSmoothValueInt(int index)
{
    return data_ov093_020c5100->smoothValues[index].current >> 12;
}
