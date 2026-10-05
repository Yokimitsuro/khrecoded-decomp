#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 value;
    s32 kind;
} TargetKey;

typedef struct {
    fx32 x;
    fx32 y;
} ScreenPos;

typedef struct {
    u8 pad_000[0x60];
    TargetKey keys[8];
    ScreenPos screen[16];
    u8 count;
} MarkerList;

extern void TargetKey_GetPosition(VecFx32 *out, TargetKey *key);
extern int ProjectWorldToScreenFx(const VecFx32 *world, fx32 *screen);

void MarkerList_ProjectToScreen(MarkerList *list)
{
    u8 i;

    for (i = 0; i < list->count; i++) {
        VecFx32 world;
        VecFx32 position;
        TargetKey_GetPosition(&position, &list->keys[i]);
        world = position;
        ProjectWorldToScreenFx(&world, &list->screen[i].x);
        list->screen[i].y += 0x8000;
    }
}
