#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x70];
    u16 drawFlags;
    u8 pad_72[0x90 - 0x72];
    s16 linkA;
    s16 linkB;
    u8 pad_94[0xbd - 0x94];
    u8 unk_BD_low : 4;
    u8 phase : 4;
} FieldObject;

extern void SyncFieldObjectAnimation(FieldObject *obj);
extern void func_ov032_020bf410(FieldObject *obj);
extern void func_ov016_020a234c(FieldObject *obj);
extern void func_ov016_020a4a84(FieldObject *obj);

void RefreshFieldObjectPhase(FieldObject *obj)
{
    s16 link;
    int phase;

    SyncFieldObjectAnimation(obj);
    if (obj->phase >= 5) {
        func_ov032_020bf410(obj);
    } else {
        func_ov016_020a234c(obj);
    }
    phase = obj->phase;
    if (phase == 1 && ((link = obj->linkA) != -1 || obj->linkB != -1)) {
        if (link != -1) {
            obj->drawFlags |= 8;
        }
    } else if ((u8)(phase + 0xfd) <= 1) {
        func_ov016_020a4a84(obj);
    }
}
