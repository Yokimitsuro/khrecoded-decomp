#include "nitro/types.h"

extern void PushContact(void *object, s32 a, s32 b, s32 c, void *extra);

void func_02032000(void *object, void *extra) {
    PushContact(object, 0, 0, 0, extra);
}
