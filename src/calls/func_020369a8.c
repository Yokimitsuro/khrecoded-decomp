#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void Obj_RemoveFromQuadTree(u32 *sub);

void func_020369a8(Container *obj)
{
    if ((obj->flags & 0x100) == 0) {
        return;
    }
    Obj_RemoveFromQuadTree(&obj->sub);
    obj->flags = obj->flags & 0xfeff;
}
