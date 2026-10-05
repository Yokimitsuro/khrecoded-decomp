#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void func_020353b8(u32 *sub);

void func_020359c4(Container *obj)
{
    if ((obj->flags & 4) != 0) {
        func_020353b8(&obj->sub);
        obj->flags = obj->flags & 0xfffb;
    }
}
