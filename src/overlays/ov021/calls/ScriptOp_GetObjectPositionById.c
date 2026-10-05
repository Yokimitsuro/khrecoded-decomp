#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u8 pad_00[8];
    TaggedValue operand;
} ScriptCommand;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} ScriptObject;

extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt(TaggedValue *tagged);
extern ScriptObject *func_ov021_020b02d8(ScriptContext *context, s32 id);

int ScriptOp_GetObjectPositionById(ScriptContext *context, ScriptCommand *command)
{
    ScriptObject *object = func_ov021_020b02d8(context, TaggedValueToInt(ResolveTaggedValueRef(context, &command->operand)));
    if (object != NULL) {
        context->vector = object->position;
    }
    return 0;
}
