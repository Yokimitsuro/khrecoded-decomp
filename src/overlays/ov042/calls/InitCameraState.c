#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 _0[0x38];
    u32 flags;
    u32 configFlags;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    u32 unk_4c;
    u32 unk_50;
    u8 _54[0x28];
    VecFx32 shake;
    u8 _88[0x34];
    fx32 unk_bc;
    fx32 unk_c0;
    u32 unk_c4;
    int unk_c8;
    u32 unk_cc;
    u32 unk_d0;
    int unk_d4;
    u32 unk_d8;
    u32 unk_dc;
    u32 unk_e0;
    u32 unk_e4;
    u32 unk_e8;
    u32 unk_ec;
    u32 unk_f0;
    u32 unk_f4;
    u32 unk_f8;
    u32 unk_fc;
    u32 unk_100;
    u32 unk_104;
    u8 _108[6];
    u16 unk_10e;
    u8 _110[0x24];
    VecFx32 anchor;
    u32 mode;
} CameraState;

extern CameraState *data_ov042_020be5e0;
extern VecFx32 data_0205344c;
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void ApplyCameraConfig(void);

void InitCameraState(void) {
    CameraState *camera = data_ov042_020be5e0;
    camera->flags = 3;
    camera->configFlags = 0;
    camera->unk_48 = 0;
    camera->unk_d8 = 0;
    camera->unk_40 = 0;
    camera->unk_44 = 0;
    camera->unk_50 = 0;
    camera->unk_dc = 0;
    camera->unk_e0 = 0;
    camera->unk_e4 = 0;
    camera->unk_e8 = 0;
    camera->unk_104 = 0;
    camera->unk_10e = 3;
    camera->unk_f8 = 0;
    camera->unk_fc = 0;
    camera->unk_100 = 0;
    camera->unk_bc = 0x4000;
    camera->unk_c0 = 0xa000;
    camera->unk_c4 = 0x80000000;
    camera->unk_c8 = 0x7fffffff;
    camera->unk_d4 = -1;
    camera->unk_f4 = 0;
    camera->unk_f0 = 0x1f;
    camera->unk_ec = 0x1f;
    camera->mode = 0;
    camera->shake = data_0205344c;
    camera->anchor = *func_ov001_0206dc4c(0);
    ApplyCameraConfig();
}
