#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NNSG3dResMdl NNSG3dResMdl;

typedef struct ShadowVolume {
    VecFx32 position;
    fx32 scale;
    NNSG3dResMdl **modelRef;
    u8 alpha;
    u8 pad_15;
    u16 rotY;
} ShadowVolume;

extern NNSG3dResMdl *data_02060840;

BOOL ShadowVolume_Init(ShadowVolume *shadow, const VecFx32 *position, fx32 scale, NNSG3dResMdl *model)
{
    shadow->position = *position;
    shadow->scale = scale;
    /* Original stores the address of the model parameter. */
    shadow->modelRef = (model == NULL) ? &data_02060840 : &model;
    shadow->alpha = 8;
    shadow->rotY = 0;
    return TRUE;
}
