#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2e[2];
    fx32 result;
} ScriptContext;

typedef struct {
    u32 key;
    s32 nameIndex;
    u8 pad_08[0xc];
    VecFx32 scale;
} AttachPoint;

typedef struct {
    u8 pad_00[0xa];
    u16 eventId;
} StageActor;

typedef struct StageObject StageObject;

typedef struct {
    u32 unk_00;
    StageActor *actor;
    u32 unk_08;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt(TaggedValue *value);
extern StageObject *func_ov001_0209c114(u32 id);
extern void func_ov001_020978b8(StageObject *object, u32 key, AttachPoint *out);

int ScriptOp_GetAttachPointScale(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *key = ResolveTaggedValueRef(context, args + 1);
    StageActor *actor = data_ov021_020b56c4.actor;
    StageObject *object;
    AttachPoint point;

    if (actor == NULL) {
        return 0;
    }
    context->resultType = 0x10;
    context->result = 0x1000;
    if (actor->eventId != 0 && (object = func_ov001_0209c114(actor->eventId)) != NULL) {
        func_ov001_020978b8(object, TaggedValueToInt(key), &point);
        context->result = point.scale.x;
    }
    return 0;
}
