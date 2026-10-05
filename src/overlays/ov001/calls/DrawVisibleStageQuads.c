#include "nitro/types.h"

typedef struct StageQuad {
    u8 pad_00[0x8];
    void *resource;
    u8 pad_0c[0x2a - 0xc];
    u8 alpha : 5;
    u8 flags : 3;
} StageQuad;

typedef struct StageManager {
    u8 pad_00000[0x18d9c];
    void *quadList;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern void *func_ov001_0208f2a4(void *list);
extern void *func_ov001_0208f2b4(void *node);
extern StageQuad *func_ov001_0208f290(void *list, void *node);
extern void func_ov001_0206ad28(StageQuad *quad);

void DrawVisibleStageQuads(void)
{
    void *node;
    StageQuad *quad;

    for (node = func_ov001_0208f2a4(data_ov001_020a0528->quadList); node != NULL;
         node = func_ov001_0208f2b4(node)) {
        quad = func_ov001_0208f290(data_ov001_020a0528->quadList, node);
        if (quad->resource != NULL && quad->alpha != 0) {
            func_ov001_0206ad28(quad);
        }
    }
}
