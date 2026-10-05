#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x28];
    fx32 timer;
} ScriptContext;

typedef struct PlayerActor PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *value);
extern fx32 ApplyActorScaleFactors(PlayerActor *actor);

int ScriptCmd_WaitPlayerScaledTime(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *duration = ResolveTaggedValueRef(context, args);
    int result = 3;
    PlayerActor *player = data_ov021_020b56c4.player;

    if (player == NULL) {
        return 0;
    }
    if (duration->value > 0) {
        if (context->timer == 0) {
            context->timer = TaggedValueToFixed(duration);
        } else {
            context->timer -= ApplyActorScaleFactors(player);
            if (context->timer <= 0) {
                result = 0;
                context->timer = 0;
            }
        }
    }
    return result;
}
