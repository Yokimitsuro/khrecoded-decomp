#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void ActorRegistry_UnregisterSlot(Container *obj, u16 arg);
extern void func_020359c4(Container *obj);
extern void ActorSlot_Unlink(Container *obj);
extern void Obj_ShutdownBase(void *entity);

void Obj_ConditionalShutdown(Container *obj, u16 arg) {
    if (obj->flags & 0x80) {
        ActorRegistry_UnregisterSlot(obj, arg);
    }
    if (obj->flags & 0x40) {
        return;
    }
    if ((obj->flags & 4) == 0) {
        return;
    }
    func_020359c4(obj);
    if (obj->flags & 2) {
        ActorSlot_Unlink(obj);
    }
    Obj_ShutdownBase((u8 *)obj + 0x10);
    obj->flags = 0;
}
