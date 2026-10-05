#include "nitro/types.h"

typedef struct RenderContext {
    u8 pad_00[8];
    void *queue;
} RenderContext;

extern RenderContext data_ov021_020b56c4;
extern void NotifySceneObjectHandler(void *queue, void *item);

int SubmitActorRender(u8 *actor)
{
    NotifySceneObjectHandler(data_ov021_020b56c4.queue, actor + 0x34);
    return 0;
}
