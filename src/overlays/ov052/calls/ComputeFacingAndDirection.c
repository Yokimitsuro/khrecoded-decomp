#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s16 data_02053580[];
extern u32 func_ov001_0206db78(u32 index);
extern u32 func_ov021_020a7564(u32 entry);
extern int StepFacingToward(int entity, int angle);

int ComputeFacingAndDirection(int entity, VecFx32 *out)
{
    int angle = StepFacingToward(entity, func_ov021_020a7564(func_ov001_0206db78(*(u8 *)(entity + 0x9b4))));
    if (out != NULL) {
        int index = angle >> 4;
        out->x = -data_02053580[index];
        out->z = -data_02053580[(0x400 - index) & 0xfff];
    }
    return angle;
}
