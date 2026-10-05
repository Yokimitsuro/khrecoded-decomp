#include "nitro/types.h"

typedef struct ScriptContext {
    u8 pad0[0x14];
    int state;
    u8 pad18[0x84];
    u32 flags : 31;
    u32 flagTop : 1;
} ScriptContext;

typedef struct PlayerObject {
    u8 pad0[0x28a];
    u16 lowBits : 10;
    u16 moveLock : 4;
    u16 highBits : 2;
} PlayerObject;

typedef struct ActiveContext {
    void *stage;
    int pad4;
    PlayerObject *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56c4;

int ScriptOp_ClearPlayerStateBits(ScriptContext *context)
{
    PlayerObject *object = data_ov021_020b56c4.object;

    if (object == NULL) {
        return 5;
    }
    if (context->state == 10) {
        return 5;
    }
    if (object != NULL) {
        object->moveLock = 0;
    }
    context->flags &= ~2;
    return 5;
}
