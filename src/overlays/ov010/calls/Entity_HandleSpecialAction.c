#include "nitro/types.h"

typedef struct Entity Entity;

typedef int (*EntityModeFunc)(Entity *entity, int mode);

typedef struct EntityTimer {
    u8 pad_00[4];
    int delay;
} EntityTimer;

struct Entity {
    u8 pad_000[0x9b4];
    u8 slot;
    u8 pad_9b5[7];
    EntityTimer timer;
    u8 pad_9c4[0x10ec - 0x9c4];
    EntityModeFunc modeCallback;
};

extern void *data_ov010_020a1de0;

extern void *func_ov001_0206db78(u8 slot);
extern u16 SharedObject_GetId(void *self);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov010_020a0cf8(void *actor);
extern BOOL DispatchSlotAction(Entity *entity);

BOOL Entity_HandleSpecialAction(Entity *entity)
{
    void *self = func_ov001_0206db78(entity->slot);
    EntityTimer *timer = &entity->timer;
    BOOL result = FALSE;
    void *actor = data_ov010_020a1de0;

    if (SharedObject_GetId(self) == 8) {
        int mode = entity->modeCallback(entity, 0x1e);
        if (mode == 0x1e) {
            func_ov010_020a0cf8(actor);
            timer->delay = 0x18;
            result = TRUE;
        } else if (mode == 0x1f) {
            result = TRUE;
        }
    } else if (!func_ov001_020645c8(0x3713) || SharedObject_GetId(self) != 7) {
        result = DispatchSlotAction(entity);
    }
    return result;
}
