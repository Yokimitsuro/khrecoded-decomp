#include "nitro/types.h"

extern void InitModelInstance(void *object, s32 sourceA, s32 sourceB, s32 flag, void *extra);

void func_0202ed94(u8 *object, s32 value, s32 sourceB, void *extra) {
    *(s32 *)(object + 0x74) = value;
    InitModelInstance(object, 0, sourceB, 1, extra);
}
