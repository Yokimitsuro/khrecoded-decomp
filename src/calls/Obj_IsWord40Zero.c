#include "nitro/types.h"

BOOL Obj_IsWord40Zero(u8 *object) {
    return *(s32 *)(object + 0x40) == 0;
}
