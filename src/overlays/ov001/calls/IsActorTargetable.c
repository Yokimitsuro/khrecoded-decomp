#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x3b];
    u8 lowBits : 4;
    u8 shapeKind : 4;
} FieldObject;

extern const s16 data_02053580[];
extern VecFx32 *func_ov001_0206dc4c(s32 playerIndex);
extern VecFx32 *func_ov001_0207f898(FieldObject *object);
extern s32 FieldObject_GetClassValue4c(FieldObject *object);
extern u16 GetBiasAdjustedField(s32 playerIndex);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL IsActorTargetable(s32 playerIndex, FieldObject *object, s32 range)
{
    VecFx32 *playerPos = func_ov001_0206dc4c(playerIndex);
    VecFx32 *targetPos = func_ov001_0207f898(object);
    fx32 flatDistance = 0x7fffffff;
    fx32 distance;
    int angle;
    VecFx32 direction;
    VecFx32 forward;
    VecFx32 targetFlat;
    VecFx32 playerFlat;

    if (targetPos == NULL) {
        return FALSE;
    }
    distance = VEC_Distance(targetPos, playerPos);
    if (distance > FieldObject_GetClassValue4c(object) || distance > range) {
        return FALSE;
    }
    VEC_Subtract(targetPos, playerPos, &direction);
    direction.y = 0;
    if (direction.x != 0 || direction.y != 0 || direction.z != 0) {
        VEC_Normalize(&direction, &direction);
    }
    forward.z = 0;
    forward.y = 0;
    forward.x = 0;
    angle = GetBiasAdjustedField(playerIndex) >> 4;
    forward.x = -data_02053580[angle];
    forward.z = -data_02053580[(0x400 - angle) & 0xfff];
    if (object->shapeKind != 1 && object->shapeKind != 8) {
        playerFlat = *playerPos;
        targetFlat = *targetPos;
        targetFlat.y = 0;
        playerFlat.y = 0;
        flatDistance = VEC_Distance(&targetFlat, &playerFlat);
    }
    if (VEC_DotProduct(&forward, &direction) < 0x800 && flatDistance > 0x1000) {
        return FALSE;
    }
    return TRUE;
}
