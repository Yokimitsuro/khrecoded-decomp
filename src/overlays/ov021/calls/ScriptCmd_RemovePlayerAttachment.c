#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct ScriptContext ScriptContext;
typedef struct PlayerActor PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt(TaggedValue *value);
extern void func_ov001_02091ae8(PlayerActor *player, u16 firstId, u16 secondId, int arg3);

int ScriptCmd_RemovePlayerAttachment(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *first = ResolveTaggedValueRef(context, args);
    TaggedValue *second = ResolveTaggedValueRef(context, args + 1);
    PlayerActor *player = data_ov021_020b56c4.player;
    s32 firstId;

    if (player == NULL) {
        return 0;
    }
    firstId = TaggedValueToInt(first);
    func_ov001_02091ae8(player, firstId, TaggedValueToInt(second), 0);
    return 0;
}
