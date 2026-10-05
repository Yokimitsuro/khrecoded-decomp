#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Mtx33 {
    fx32 m[9];
} Mtx33;

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

extern const VecFx32 data_ov035_020bc41c;
extern const VecFx32 data_ov035_020bc410;
extern const Mtx33 data_ov035_020bc444;
extern Mtx33 NNS_G3dGlb_prmBaseRot;
extern GeometryState NNS_G3dGlb_prmMatColor0;
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *target);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *target);
extern void MI_Copy36B(const Mtx33 *src, Mtx33 *dst);
extern void NNS_G3dGlbFlushWVP(void);
extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

void SetupMovieCamera(void) {
    u32 command;
    VecFx32 position;
    VecFx32 target;
    Mtx33 rotation;

    position = data_ov035_020bc41c;
    target = data_ov035_020bc410;
    rotation = data_ov035_020bc444;
    NNS_G3dGlbSetBaseScale(&target);
    NNS_G3dGlbSetBaseTrans(&position);
    MI_Copy36B(&rotation, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    NNS_G3dGlbFlushWVP();
    command = 0x1f08c0;
    NNS_G3dGeBufferOP_N(0x29, &command, 1);
}
