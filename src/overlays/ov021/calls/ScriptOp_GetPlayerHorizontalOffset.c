#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2e[2];
    fx32 result;
} ScriptContext;

typedef struct PlayerActor PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;
extern void NotifySceneObjectHandler(PlayerActor *player, VecFx32 *out);
extern VecFx32 *func_ov001_02090f2c(PlayerActor *player);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_Mag(const VecFx32 *v);

int ScriptOp_GetPlayerHorizontalOffset(ScriptContext *context)
{
    PlayerActor *player = data_ov021_020b56c4.player;
    VecFx32 current;
    VecFx32 reference;
    VecFx32 delta;

    if (player == NULL) {
        return 0;
    }
    NotifySceneObjectHandler(player, &current);
    reference = *func_ov001_02090f2c(player);
    VEC_Subtract(&current, &reference, &delta);
    delta.y = 0;
    context->resultType = 0x10;
    context->result = VEC_Mag(&delta);
    return 0;
}
