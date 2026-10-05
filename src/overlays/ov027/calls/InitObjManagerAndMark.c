#include "nitro/types.h"

extern void InitObjManager(int manager, u32 *config);

void InitObjManagerAndMark(void *obj, void *config) {
    InitObjManager((int)obj, (u32 *)config);
    *(u32 *)((u8 *)obj + 0x6478) |= 4;
}
