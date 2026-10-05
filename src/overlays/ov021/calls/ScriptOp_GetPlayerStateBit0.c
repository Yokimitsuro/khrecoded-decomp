#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2E[2];
    int result;
} ScriptContext;

typedef struct {
    u8 pad_000[0x26c];
    u32 stateBits : 31;
    u32 stateTop : 1;
} PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;

int ScriptOp_GetPlayerStateBit0(ScriptContext *context) {
    PlayerActor *player = data_ov021_020b56c4.player;

    if (player == NULL) {
        return 0;
    }
    context->resultType = 1;
    context->result = (player->stateBits & 1) != 0;
    return 0;
}
