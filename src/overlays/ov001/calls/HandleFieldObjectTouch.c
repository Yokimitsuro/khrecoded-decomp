#include "nitro/types.h"

typedef struct FieldObjectInfo {
    u8 pad[0x7d];
    u8 type;
    u8 pad7e[4];
    u8 category;
} FieldObjectInfo;

typedef struct TouchObject {
    u8 pad0[8];
    FieldObjectInfo *info;
    u8 padC[0x42];
    u16 flags;
} TouchObject;

extern int func_ov001_020644b0(void);
extern void func_ov001_020642a0(void);

BOOL HandleFieldObjectTouch(TouchObject *object) {
    BOOL locked = (func_ov001_020644b0() == 900);

    if (!locked && (u8)(object->info->category + 0xff) <= 1) {
        switch (object->info->type) {
        case 5:
        case 9:
            return TRUE;
        case 1:
        case 15:
            if (object->flags & 0x40) {
                return TRUE;
            }
            func_ov001_020642a0();
            return TRUE;
        }
    }
    return TRUE;
}
