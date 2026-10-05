#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    char pad00[0x20];
    s16 sinR;
    s16 cosR;
    fx32 transS;
    fx32 transT;
    u16 width;
    u16 height;
} TexSRTAnm;

typedef struct {
    fx32 m[4][4];
} MtxFx44;

extern void FX_DivAsync(fx32 numer, fx32 denom);
extern fx32 FX_GetDivResult(void);

static inline fx32 FxOneMinus(fx32 x)
{
    x = -x;
    return x + 0x1000;
}

void NNSi_G3dCalcTexMtxRot(MtxFx44 *m, const TexSRTAnm *anm)
{
    fx32 w = anm->width << 12;
    fx32 h = anm->height << 12;

    FX_DivAsync(h, w);
    m->m[0][0] = anm->cosR;
    m->m[1][1] = anm->cosR;
    m->m[0][1] = (-anm->sinR * FX_GetDivResult()) >> 12;
    FX_DivAsync(w, h);
    m->m[3][0] = (FxOneMinus(anm->sinR + anm->cosR) * anm->width << 3) - ((anm->transS * anm->width) << 4);
    m->m[3][1] = ((anm->sinR - anm->cosR + 0x1000) * anm->height << 3) + ((anm->transT * anm->height) << 4);
    m->m[1][0] = (anm->sinR * FX_GetDivResult()) >> 12;
}
