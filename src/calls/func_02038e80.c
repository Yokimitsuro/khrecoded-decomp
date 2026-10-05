#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x108];
    u32 node;
} Entity;

extern BOOL func_02038b64(Entity **handle, void *out, u32 arg);
extern void Obj_SetPosition(Entity *entity, void *in);
extern u32 GetActorRegistry(void);
extern void QuadTree_ReinsertNodeIfFlagSet(u32 tree, u32 *node);

void func_02038e80(Entity **handle, u32 arg)
{
    u8 buf[12];
    Entity *entity;
    u32 world;

    if (func_02038b64(handle, buf, arg) != 0) {
        Obj_SetPosition(*handle, buf);
        entity = *handle;
        if (entity->node != 0) {
            world = GetActorRegistry();
            QuadTree_ReinsertNodeIfFlagSet(**(u32 **)(world + 4), &entity->node);
        }
    }
}
