#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0x58 - 0x44];
    VecFx32 target;
    u8 pad_64[0x77 - 0x64];
    u8 mode;
    u8 pad_78[0xc0 - 0x78];
    u32 flags;
} FieldObject;

extern VecFx32 *func_ov001_0206dc4c(int arg);
extern void PlaceFieldObjectNode(FieldObject *obj, VecFx32 *target, VecFx32 *source);

void SteerFieldObjectToTarget(FieldObject *obj)
{
    VecFx32 point;

    if (obj->flags & 0x8000) {
        if (obj->mode == 6) {
            point = *func_ov001_0206dc4c(0);
            point.y += 0xc00;
            PlaceFieldObjectNode(obj, &obj->target, &point);
            return;
        }
        PlaceFieldObjectNode(obj, &obj->target, &obj->position);
    }
}
