#include "nitro/types.h"

typedef void (*StateCallback)(int entity, int state);
typedef void (*EntityHook)(int entity, int frame);
typedef int (*StateQuery)(int entity);

extern u32 func_ov001_0206db78(u32 index);
extern BOOL func_ov052_020c8914(int entity);

void AdvanceChargeState(int entity)
{
    BOOL advance = FALSE;
    u32 locking;
    int power;
    int state;
    func_ov001_0206db78(*(u8 *)(entity + 0x9b4));
    locking = *(u32 *)(entity + 0x234) & 4;
    power = *(int *)(entity + 0x9c4);
    if (func_ov052_020c8914(entity)) {
        return;
    }
    if (*(int *)(entity + 0x760) >= 0x9000 && *(EntityHook *)(entity + 0x1fc) != NULL) {
        (*(EntityHook *)(entity + 0x1fc))(entity, 0x9000);
    }
    if (power >= 0x3000 && locking) {
        advance = TRUE;
    } else {
        if (*(StateQuery *)(entity + 0x22c) != NULL) {
            state = (*(StateQuery *)(entity + 0x22c))(entity);
        } else {
            state = *(int *)(entity + 0x1dc);
        }
        if (state != 4 && power >= 0x20000) {
            advance = TRUE;
        }
    }
    if (advance) {
        if (locking) {
            (*(StateCallback *)(entity + 0x10ec))(entity, 5);
        } else {
            (*(StateCallback *)(entity + 0x10ec))(entity, 4);
        }
    }
}
