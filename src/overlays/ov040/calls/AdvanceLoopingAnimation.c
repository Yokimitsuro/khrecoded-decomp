#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xd8];
    s16 layerFrames[5];
} AnimationSet;

extern AnimationSet *data_ov040_020be280;
extern u16 AdvanceAnimationTracks(AnimationSet *state, fx32 delta);
extern fx32 func_0202f4cc(AnimationSet *state, int layer);
extern void func_01ffb2f8(AnimationSet *state, u16 layer, fx32 frame);

void AdvanceLoopingAnimation(fx32 delta) {
    if (AdvanceAnimationTracks(data_ov040_020be280, delta) != 0) {
        int layer = 0;
        fx32 frame = func_0202f4cc(data_ov040_020be280, 0) - delta;
        do {
            if (data_ov040_020be280->layerFrames[(u16)layer] > 0) {
                func_01ffb2f8(data_ov040_020be280, (u16)layer, frame);
            }
            layer++;
        } while (layer < 5);
    }
}
