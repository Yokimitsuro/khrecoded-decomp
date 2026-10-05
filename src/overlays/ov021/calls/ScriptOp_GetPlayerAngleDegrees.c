#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2e[2];
    s32 result;
} ScriptContext;

typedef struct {
    u8 pad_000[0x2e6];
    u16 angle;
} PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;

int ScriptOp_GetPlayerAngleDegrees(ScriptContext *context)
{
    PlayerActor *player = data_ov021_020b56c4.player;

    if (player == NULL) {
        return 0;
    }
    context->resultType = 0x10;
    context->result = (s32)(((s64)player->angle * 0x1680000 + 0x80000) >> 20);
    return 0;
}
