#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2E[2];
    int result;
} ScriptContext;

typedef struct {
    u8 pad_000[0x28c];
    u16 flagsLow : 15;
    u16 hidden : 1;
} PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;

int ScriptOp_GetPlayerHiddenFlag(ScriptContext *context) {
    PlayerActor *player = data_ov021_020b56c4.player;

    if (player == NULL) {
        return 0;
    }
    context->resultType = 1;
    context->result = player->hidden;
    return 0;
}
