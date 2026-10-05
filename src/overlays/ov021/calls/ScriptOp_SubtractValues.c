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

extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt(TaggedValue *tagged);
extern s32 TaggedValueToFixed(TaggedValue *tagged);

s32 ScriptOp_SubtractValues(ScriptContext *context, TaggedValue *operands)
{
    TaggedValue *left = ResolveTaggedValueRef(context, operands);
    TaggedValue *right = ResolveTaggedValueRef(context, operands + 1);
    s32 leftValue;
    s32 rightValue;
    s32 tag = left->tag;

    if (tag == 1) {
        context->result.tag = 1;
        leftValue = TaggedValueToInt(left);
        rightValue = TaggedValueToInt(right);
    } else if (tag == 0x10) {
        context->result.tag = 0x10;
        leftValue = TaggedValueToFixed(left);
        rightValue = TaggedValueToFixed(right);
    } else {
        goto done;
    }
    context->result.value = leftValue - rightValue;
done:
    return 0;
}
