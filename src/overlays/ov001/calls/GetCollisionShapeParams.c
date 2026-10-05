#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct ShapeSource {
    u8 pad_00[0x14];
    s32 shapeType;
    fx32 radius;
    fx32 height;
} ShapeSource;

typedef struct ShapeParams {
    s32 kind;
    fx32 height;
    fx32 radius;
} ShapeParams;

extern fx32 FX_Mul(fx32 a, fx32 b);

ShapeParams *GetCollisionShapeParams(ShapeSource *source, ShapeParams *params)
{
    if (source == NULL) {
        return NULL;
    }
    switch (source->shapeType) {
    case 2:
        if (source->radius == 0) {
            return NULL;
        }
        params->kind = 0;
        params->radius = FX_Mul(source->radius, FX32_ONE);
        params->height = FX_Mul(source->height, FX32_ONE);
        break;
    case 0:
        if (source->radius == 0) {
            return NULL;
        }
        params->kind = 2;
        params->radius = FX_Mul(source->radius, FX32_ONE);
        params->height = FX_Mul(source->height, FX32_ONE);
        break;
    case 1:
        if (source->radius == 0) {
            return NULL;
        }
        params->kind = 1;
        params->radius = FX_Mul(source->radius, FX32_ONE);
        params->height = FX_Mul(source->height, FX32_ONE);
        break;
    default:
        params = NULL;
        break;
    }
    return params;
}
