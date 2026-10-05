#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

typedef struct GlobalStateTail {
    u8 pad_00[0x54];
    u32 flags;
} GlobalStateTail;

extern const VecFx32 data_ov001_0209deb0;
extern const VecFx32 data_ov001_0209debc;
extern const MtxFx33 data_ov001_0209dee8;
extern GlobalStateTail NNS_G3dGlb_prmMatColor0;
extern MtxFx33 NNS_G3dGlb_prmBaseRot;

extern void NNS_G3dGlbSetBaseScale(const VecFx32 *vec);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *vec);
extern void MI_Copy36B(const MtxFx33 *src, MtxFx33 *dst);
extern void NNS_G3dGlbFlushWVP(void);
extern void NNS_G3dGeBufferOP_N(int command, const u32 *params, int count);

void ApplyDefaultSceneCamera(void)
{
    VecFx32 second = data_ov001_0209deb0;
    VecFx32 first = data_ov001_0209debc;
    MtxFx33 rotation = data_ov001_0209dee8;
    u32 command;

    NNS_G3dGlbSetBaseScale(&first);
    NNS_G3dGlbSetBaseTrans(&second);
    MI_Copy36B(&rotation, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    NNS_G3dGlbFlushWVP();
    command = 0x1f00c0;
    NNS_G3dGeBufferOP_N(0x29, &command, 1);
}
