#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u32 *data_ov001_020a0528;
extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern unsigned int random_next_scaled(unsigned int upperBound);
extern void ForwardSubModePairA(int kind, int value);
extern void func_ov042_020bd76c(u32 first, u32 second);
extern void GetCameraOrbitOffset(VecFx32 *out, u32 angle);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void StartCameraParticle_020bcb58(VecFx32 *pos, int id, int speed, fx32 radius);
extern void ResetCameraUp(int value);

void HandleSessionEffectEvent(int event, int value) {
    if (data_ov001_020a0528 == NULL || (*data_ov001_020a0528 & 0x10000) != 0) {
        return;
    }
    if (!func_ov001_02063a24()) {
        return;
    }
    switch (func_ov001_02063a38()) {
    case 0:
    case 2:
    case 3:
    case 6:
        if (event == 1) {
            ForwardSubModePairA(3, value);
        }
        break;
    case 4:
        if (event == 1) {
            func_ov042_020bd76c(0x333, 0xf000);
        }
        break;
    case 7:
        switch (event) {
        case 1: {
            int sign;
            VecFx32 position;
            VecFx32 direction;
            VecFx32 scaled;
            sign = random_next_scaled(2) != 0 ? 1 : -1;
            GetCameraOrbitOffset(&direction, random_next_scaled(0x6488));
            scaled = direction;
            ScaleVecFx32InPlace(&scaled, 0x1ec);
            position = scaled;
            StartCameraParticle_020bcb58(&position, 0x333, (int)((s64)sign * 0x430), 0xa000);
            break;
        }
        case 2:
            ResetCameraUp((int)((s64)value * 0x3244 / 0xb4000));
            break;
        }
        break;
    }
}
