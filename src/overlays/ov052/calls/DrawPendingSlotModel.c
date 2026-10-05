#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad[0xa4];
    VecFx32 position;
    u8 pad_b0[0x54];
} SlotModel;

extern int func_ov052_020ceb74(int entity);
extern void func_01ffb12c(SlotModel *node);

void DrawPendingSlotModel(int entity, u8 *request)
{
    VecFx32 position = *(VecFx32 *)(entity + 0xa00);
    SlotModel *node = NULL;
    u8 flags = request[8];

    if (flags & 1) {
        request[8] = flags & 0xfe;
        node = *(SlotModel **)(entity + 0x106c);
    } else if (flags & 2) {
        request[8] = flags & 0xfd;
        node = *(SlotModel **)(entity + 0x106c) + 1;
    } else if (flags & 4) {
        request[8] = flags & 0xfb;
        node = *(SlotModel **)(entity + 0x106c) + 2;
    } else if (flags & 0x40) {
        request[8] = flags & 0xbf;
        node = *(SlotModel **)(entity + 0x106c) + 3;
        position = *(VecFx32 *)func_ov052_020ceb74(entity);
    }
    if (node != NULL) {
        node->position = position;
        func_01ffb12c(node);
    }
}
