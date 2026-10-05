#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 axes[3];
} Basis;

typedef struct {
    fx32 sine;
    fx32 cosine;
    u8 pad08[0xc];
    VecFx32 position;
    VecFx32 lookAt;
    VecFx32 up;
    u8 pad38[0x14];
    fx32 weights[3];
    u8 pad58[0x24];
    VecFx32 forwardUp;
    u8 pad88[0x54];
    VecFx32 lookAtOffset;
    VecFx32 positionOffset;
    VecFx32 target;
    VecFx32 origin;
    int fieldOfView;
    int particle[4];
    VecFx32 particleOrigin;
} Panel;

extern Panel *data_ov044_020d0ec0;
extern const s16 data_02053580[];

extern void GetPanelBasis(Basis *out);
extern void CombineBasisAxes(const Basis *basis, const fx32 *weights, VecFx32 *out, VecFx32 *partial);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL UpdateDriftParticle(void *particle);
extern void func_ov044_020d00b0(BOOL shouldBlend);

#define PANEL_ANGLE_INDEX(fov) ((int)((((s64)((fov) / 2) << 16) / 0x6488) & 0xffff) >> 4)

void UpdatePanelCamera(void)
{
    Panel *panel = data_ov044_020d0ec0;
    Panel *camera;
    Basis basis;
    VecFx32 full;
    VecFx32 partial;
    VecFx32 positionSum;
    VecFx32 lookAtSum;

    GetPanelBasis(&basis);
    CombineBasisAxes(&basis, panel->weights, &full, &partial);
    VEC_Add(&panel->target, &partial, &panel->positionOffset);
    VEC_Add(&panel->target, &full, &panel->lookAtOffset);
    panel->sine = data_02053580[PANEL_ANGLE_INDEX(panel->fieldOfView)];
    panel->cosine = data_02053580[(0x400 - PANEL_ANGLE_INDEX(panel->fieldOfView)) & 0xfff];
    if (panel->particle[0] != 0) {
        UpdateDriftParticle(panel->particle);
        panel->origin = panel->particleOrigin;
    }
    camera = data_ov044_020d0ec0;
    VEC_Add(&data_ov044_020d0ec0->lookAtOffset, &data_ov044_020d0ec0->origin, &lookAtSum);
    camera->lookAt = lookAtSum;
    VEC_Add(&data_ov044_020d0ec0->positionOffset, &data_ov044_020d0ec0->origin, &positionSum);
    camera->position = positionSum;
    camera->up = data_ov044_020d0ec0->forwardUp;
    func_ov044_020d00b0(TRUE);
}


