#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptContext {
    u8 pad0[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct PlayerObject {
    u8 pad0[0x2e6];
    u16 facing;
} PlayerObject;

typedef struct ActiveContext {
    void *stage;
    void *source;
    PlayerObject *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56c4;
extern const s16 data_02053580[];
extern void *ResolveTaggedValueRef(ScriptContext *context, void *value);
extern s32 TaggedValueToFixed(void *tagged);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

int ScriptOp_MoveAlongPlayerFacing(ScriptContext *context, u8 *operands)
{
    VecFx32 facing;
    VecFx32 direction;
    void *tagged = ResolveTaggedValueRef(context, operands + 8);
    PlayerObject *player = data_ov021_020b56c4.object;

    facing.x = data_02053580[player->facing >> 4];
    facing.y = 0;
    facing.z = data_02053580[(0x400 - (player->facing >> 4)) & 0xfff];
    VEC_Normalize(&facing, &direction);
    VEC_MultAdd(TaggedValueToFixed(tagged), &direction, &context->position, &context->position);
    return 0;
}
