#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    void *actor;
} RenderOwner;

typedef struct {
    u8 pad_00[4];
    RenderOwner *owner;
} RenderContext;

extern void func_ov059_020cd2a0(void *actor, RenderContext *renderState);

void NodeCallback_CaptureMatrix(RenderContext *context)
{
    func_ov059_020cd2a0(context->owner->actor, context);
}
