#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_000[0x20];
    u8 renderObj[0x84];
    VecFx32 position;
    VecFx32 scale;
    u8 pad_0bc[0x74];
    s8 slot;
    s8 active;
    u8 pad_132[0xe];
    u16 angle;
} SlotMarker;

typedef struct {
    u8 pad_00[0x54];
    u32 flags;
} GeometryState;

extern const s16 data_02053580[];
extern MtxFx33 NNS_G3dGlb_prmBaseRot;
extern GeometryState NNS_G3dGlb_prmMatColor0;

extern VecFx32 *func_ov001_0206dc60(int slot);
extern u16 GetBiasAdjustedField(int index);
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *scale);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *trans);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MI_Copy36B(const void *src, void *dst);
extern void NNS_G3dGlbFlushVP(void);
extern void func_01ffe1bc(void *renderObj);

void DrawSlotMarker(SlotMarker *marker)
{
    MtxFx33 rotation;
    int angleIndex;

    if (marker->active == 0) {
        return;
    }
    marker->position = *func_ov001_0206dc60(marker->slot);
    marker->angle = GetBiasAdjustedField(marker->slot);
    NNS_G3dGlbSetBaseScale(&marker->scale);
    angleIndex = marker->angle >> 4;
    MTX_RotY33_(&rotation, -data_02053580[angleIndex], -data_02053580[(0x400 - angleIndex) & 0xfff]);
    MI_Copy36B(&rotation, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    NNS_G3dGlbSetBaseTrans(&marker->position);
    NNS_G3dGlbFlushVP();
    func_01ffe1bc(marker->renderObj);
}
