#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0x72 - 0x44];
    s16 facing;
    u8 pad_74[0xac - 0x74];
    s32 timer;
    u8 pad_b0[0xbd - 0xb0];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 pad_be[2];
    u32 flags;
    u8 pad_c4[0xec - 0xc4];
    u16 anchorId : 15;
    u16 anchorFlag : 1;
    u8 pad_ee[2];
    fx32 anchorX;
    fx32 anchorSpeed;
} FieldObject;

extern void DispatchFieldObjectPhase(FieldObject *obj);
extern void func_ov016_020a6b1c(FieldObject *obj);
extern void func_ov016_020a6ce4(FieldObject *obj, const VecFx32 *position);

void TickFieldObjectRespawn(FieldObject *obj)
{
    VecFx32 position;
    BOOL keepState;
    s16 facing;
    u16 anchorId;
    fx32 anchorX;
    fx32 anchorSpeed;

    if (obj->timer == 0) {
        return;
    }
    keepState = TRUE;
    if (obj->phase != 2 && obj->phase != 4) {
        keepState = FALSE;
    }
    obj->timer -= 0x89;
    if (keepState) {
        DispatchFieldObjectPhase(obj);
    }
    if (obj->timer < 0) {
        facing = obj->facing;
        anchorId = obj->anchorId;
        anchorX = obj->anchorX;
        anchorSpeed = obj->anchorSpeed;
        position = obj->position;
        func_ov016_020a6b1c(obj);
        if (keepState) {
            obj->facing = facing;
            obj->anchorId = anchorId;
            obj->anchorX = anchorX;
            obj->anchorSpeed = anchorSpeed;
            obj->flags |= 4;
            func_ov016_020a6ce4(obj, &position);
        }
    }
}
