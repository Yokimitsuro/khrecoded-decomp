#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    s32 isActive;
    u16 angle;
    s16 angleStep;
    s16 angleScale;
    u8 pad_2A[0xAC - 0x2A];
    s32 currentCount;
    s32 targetCount;
} RotatingContext;

extern RotatingContext *data_ov001_020a04f4;
extern void HandleDirectionalPrompt(RotatingContext *context, s32 flag);
extern void LayoutFrameCornerSprites(RotatingContext *context);
extern void PlaceOrbitSpriteCorners(RotatingContext *context);

s32 UpdateSpinningMode(void)
{
    RotatingContext *context = data_ov001_020a04f4;

    if (context->isActive != 0) {
        HandleDirectionalPrompt(context, 0);
        context->angle = (context->angle + 0x10000 + context->angleStep * context->angleScale) % 0x10000;
        LayoutFrameCornerSprites(context);
        if (context->currentCount < context->targetCount) {
            PlaceOrbitSpriteCorners(context);
        }
    }
    return 0;
}
