#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x12c];
    u32 sub130;
} Entity;

extern void FreeStateBuffer(u32 *sub);
extern void func_020353b8(u32 *entity);
extern void func_02035608(u32 *entity);

void Obj_ShutdownBase(Entity *entity)
{
    FreeStateBuffer(&entity->sub130);
    func_020353b8(&entity->flags);
    func_02035608(&entity->flags);
    entity->flags = 0;
}
