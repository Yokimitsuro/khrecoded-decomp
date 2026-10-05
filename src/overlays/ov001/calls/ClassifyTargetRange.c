#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RangeResult {
    fx32 distance;
    int zone;
    int tag;
} RangeResult;

typedef struct RangeConfig {
    u8 pad_00[0x48];
    fx32 farLimit;
    fx32 midLimit;
} RangeConfig;

extern RangeConfig *data_ov001_020a04a4;
extern const s16 data_02053580[];
extern void func_ov001_0206ba18(RangeResult *result);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField(int index);
extern int func_ov021_020af414(void);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void ClassifyTargetRange(int index, VecFx32 *target, RangeResult *result, int tag) {
    RangeConfig *config = data_ov001_020a04a4;
    VecFx32 *origin;
    fx32 distance;
    fx32 leaderDot;
    fx32 cameraDot;
    VecFx32 direction;
    VecFx32 facing;
    int angle;

    func_ov001_0206ba18(result);
    result->tag = tag;
    origin = func_ov001_0206dc4c(index);
    distance = VEC_Distance(target, origin);
    VEC_Subtract(target, origin, &direction);
    if (direction.x != 0 || direction.y != 0 || direction.z != 0) {
        VEC_Normalize(&direction, &direction);
    }
    direction.y = 0;
    angle = GetBiasAdjustedField(index) >> 4;
    facing.y = 0;
    facing.x = -data_02053580[angle];
    facing.z = -data_02053580[(0x400 - angle) & 0xfff];
    leaderDot = VEC_DotProduct(&facing, &direction);
    angle = (u16)func_ov021_020af414() >> 4;
    facing.y = 0;
    facing.x = -data_02053580[angle];
    facing.z = -data_02053580[(0x400 - angle) & 0xfff];
    cameraDot = VEC_DotProduct(&facing, &direction);
    if (distance <= 0x3000) {
        result->distance = distance;
        if (leaderDot >= 0xab8) {
            result->zone = 3;
        } else {
            result->zone = 2;
        }
    } else if (distance <= 0x5000) {
        result->distance = distance;
        if (cameraDot >= 0xab8) {
            result->zone = 1;
        } else {
            result->zone = 0;
        }
    } else if (distance <= config->midLimit) {
        result->distance = distance;
        result->zone = 0;
    } else if (distance <= config->farLimit) {
        result->distance = distance;
        result->zone = -1;
    }
}
