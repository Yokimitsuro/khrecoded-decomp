#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MoveOperands {
    u8 x[8];
    u8 y[8];
    u8 z[8];
    u8 pad18[4];
    int frames;
} MoveOperands;

typedef struct PlayerObject {
    u8 pad0[0x2f0];
    VecFx32 position;
} PlayerObject;

typedef struct ActiveContext {
    void *stage;
    void *source;
    PlayerObject *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56c4;
extern void *ResolveTaggedValueRef(void *context, void *value);
extern s32 TaggedValueToFixed(void *tagged);
extern void StartWalkerMove(PlayerObject *walker, VecFx32 *target, fx32 duration);

int ScriptOp_MovePlayerTo(void *context, MoveOperands *operands)
{
    VecFx32 target;
    void *tagX = ResolveTaggedValueRef(context, operands->x);
    void *tagY = ResolveTaggedValueRef(context, operands->y);
    void *tagZ = ResolveTaggedValueRef(context, operands->z);
    PlayerObject *player = data_ov021_020b56c4.object;

    target.x = TaggedValueToFixed(tagX);
    target.y = TaggedValueToFixed(tagY);
    target.z = TaggedValueToFixed(tagZ);
    if (operands->frames == 0) {
        player->position = target;
    } else {
        StartWalkerMove(player, &target, operands->frames << 12);
    }
    return 0;
}
