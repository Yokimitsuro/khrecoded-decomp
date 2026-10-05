#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x14];
    VecFx32 target;
} SubModeView;

typedef struct {
    fx32 minX;
    fx32 maxX;
    fx32 maxY;
    fx32 minY;
} ViewBounds;

typedef struct {
    u8 pad_00[4];
    VecFx32 velocity;
} CarryMotion;

extern VecFx32 *func_ov052_020ceb74(void *actor);
extern SubModeView *func_ov021_020af614(void);
extern ViewBounds *func_ov042_020bd5b0(void);
extern VecFx32 *func_ov042_020bd344(void);

void SteerCarriedActorInView(void *actor, CarryMotion *motion, u16 input, BOOL force)
{
    VecFx32 *pos;
    SubModeView *view;
    ViewBounds *bounds;
    VecFx32 *drift;

    pos = func_ov052_020ceb74(actor);
    view = func_ov021_020af614();
    bounds = func_ov042_020bd5b0();
    drift = func_ov042_020bd344();

    if (drift->x != 0 || drift->y != 0 || drift->z != 0) {
        force = FALSE;
    }
    if (input & 0x10) {
        if (view->target.x + (bounds->maxX - 0x3800) > pos->x || force) {
            motion->velocity.x += 0x333;
        }
    } else if (input & 0x20) {
        if (view->target.x + (bounds->minX + 0x3800) < pos->x || force) {
            motion->velocity.x -= 0x333;
        }
    } else if (input & 0x40) {
        if (view->target.y + (bounds->maxY - 0x3800) > pos->y || force) {
            motion->velocity.y += 0x333;
        }
    } else if (input & 0x80) {
        if (view->target.y + (bounds->minY + 0x2000) < pos->y) {
            motion->velocity.y -= 0x333;
        }
    }
    if (view->target.x + (bounds->maxX - 0x1800) < pos->x && !force) {
        motion->velocity.x -= 0x4cd;
    }
    if (view->target.x + (bounds->minX + 0x1800) > pos->x && !force) {
        motion->velocity.x += 0x4cd;
    }
    if (view->target.y + (bounds->maxY - 0x1800) < pos->y && !force) {
        motion->velocity.y -= 0x4cd;
    }
    if (view->target.y + (bounds->minY + 0x1000) > pos->y) {
        motion->velocity.y += 0x4cd;
    }
}
