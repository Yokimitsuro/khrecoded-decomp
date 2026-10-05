#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupObject {
    u8 pad_00[0x76];
    s8 displayScale;
    u8 pad_77[0xBF - 0x77];
    s8 scaleLevel;
} GroupObject;

typedef struct ObjectGroup {
    u8 pad_00[0x1C];
    fx32 scaleX;
    fx32 scaleY;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc80(void *object);
extern int ArmObject_02051180(void);
extern fx32 FX_Mul(fx32 left, fx32 right);
extern int Fx32ToIntTruncate(fx32 value);

void ApplyGroupScale(GroupObject *object) {
    ObjectGroup *group = func_ov032_020bbc80(object);
    fx32 scale = FX_Mul(0x1000, ArmObject_02051180());
    scale = FX_Mul(group->scaleX, scale);
    if (scale <= 0x1000) {
        scale = 0x1000;
    }
    group->scaleX = scale;
    group->scaleY = scale;
    object->scaleLevel = Fx32ToIntTruncate(scale);
    object->displayScale = object->scaleLevel;
}
