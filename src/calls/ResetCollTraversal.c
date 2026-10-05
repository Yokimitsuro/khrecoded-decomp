#include "nitro/types.h"

typedef struct CollRegion {
    s32 centerX;
    s32 centerZ;
    s32 size;
} CollRegion;

typedef struct CollModel {
    u8 pad_00[0x84];
    CollRegion region;
} CollModel;

typedef struct CollTraversalFrame {
    s16 childIndex;
    u16 nodeFlags;
    CollRegion region;
} CollTraversalFrame;

extern CollTraversalFrame *data_027e00b0;
extern CollTraversalFrame data_027e00b4[];

void ResetCollTraversal(const CollModel *model)
{
    CollTraversalFrame *frames = data_027e00b4;
    s32 size = model->region.size;
    u8 depth;

    for (depth = 0; depth < 8; depth++) {
        frames[depth].region.size = size;
        size /= 2;
    }
    frames->region = model->region;
    data_027e00b0 = frames;
}
