#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    TaggedValue result;
} ScriptContext;

extern TaggedValue *func_ov021_020b038c(ScriptContext *context, s32 offset);

TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value)
{
    if (value->tag == 8) {
        if (value->value == -1) {
            value = &context->result;
        } else {
            value = func_ov021_020b038c(context, value->value);
        }
    }
    return value;
}
