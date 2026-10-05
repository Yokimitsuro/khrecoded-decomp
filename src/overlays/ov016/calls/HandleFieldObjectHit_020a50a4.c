#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 effectId;
} HitParams;

typedef struct {
    u8 pad_00[0x76];
    s8 weight;
    u8 mode;
    u8 pad_78[0xbd - 0x78];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 unk_BE_low : 4;
    u8 state : 4;
    s8 currentWeight;
    u8 pad_c0[0xc8 - 0xc0];
    int soundId;
} FieldObject;

extern BOOL func_ov001_02087674(FieldObject *obj, HitParams *params);
extern BOOL PushFieldObject(FieldObject *obj, HitParams *params);
extern void func_ov016_020a3c04(FieldObject *obj, u8 effectId);
extern void ApplyGroupLeaderHit(FieldObject *obj, int arg);
extern void func_ov016_020a6d60(FieldObject *obj, BOOL hasEffect);

int HandleFieldObjectHit_020a50a4(FieldObject *obj, HitParams *params)
{
    int result;

    if (func_ov001_02087674(obj, params)) {
        return 0x10;
    }
    if (obj->state == 0) {
        result = 1;
        if (obj->weight > 1) {
            obj->soundId = 0x222;
        }
        if (PushFieldObject(obj, params)) {
            result = 0;
        } else if (obj->mode == 11) {
            func_ov016_020a3c04(obj, params->effectId);
            return 0;
        }
        if (obj->weight == 0) {
            return result;
        }
        if (obj->phase >= 5) {
            ApplyGroupLeaderHit(obj, 0);
        } else {
            obj->currentWeight--;
        }
        if (obj->currentWeight > 0) {
            return 0;
        }
        func_ov016_020a6d60(obj, params->effectId != 0xff);
    }
    return 0;
}
