#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct {
    u8 pad_00[0x20];
    s32 tileScale;
    u8 pad_24[0x2c];
    s32 originX;
    s32 originY;
    u8 pad_58[0x7f68];
    fx32 zoom;
} MapView;

extern fx32 FX_Mul(fx32 left, fx32 right);

void WorldToMapPosition(MapView *view, MapPoint *out, const VecFx32 *worldPos)
{
    fx32 mapX = FX_Mul(worldPos->x * view->tileScale, view->zoom);
    fx32 mapY = FX_Mul(worldPos->z * view->tileScale, view->zoom);

    out->x = mapX + view->originX * FX32_ONE;
    out->y = mapY + view->originY * FX32_ONE;
}
