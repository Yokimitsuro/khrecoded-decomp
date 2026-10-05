#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    int x;
    int y;
    u8 pad_0c[8];
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} TouchRegion;

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} TouchBounds;

typedef struct {
    u8 pad_0000[0xcdc8];
    TouchRegion region;
    u8 pad_cde4[0xf064 - 0xcde4];
    BOOL isTouchScrolling;
    u8 pad_f068[0x2c];
    TouchBounds bounds;
} MenuScene;

extern MenuScene *data_ov097_020c2540;
extern void RuntimeState_SetCondition(int value);

void ApplyTouchRegionBounds(MenuScene *scene)
{
    TouchBounds *bounds;
    TouchRegion *region;

    scene->isTouchScrolling = FALSE;
    RuntimeState_SetCondition(TRUE);
    bounds = &data_ov097_020c2540->bounds;
    region = &scene->region;
    bounds->right = region->x + region->right;
    bounds->bottom = region->y + region->bottom;
    bounds->left = region->x + region->left;
    bounds->top = region->y + region->top;
}
