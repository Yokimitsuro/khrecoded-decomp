#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef s32 (*ScriptHandler)(void *context, TaggedValue *operands);

extern TaggedValue *ResolveTaggedValueRef(void *context, TaggedValue *value);
extern ScriptHandler gScriptVectorHandlers[];

s32 DispatchScriptHandler(void *context, TaggedValue *operands)
{
    TaggedValue *selector;
    ScriptHandler handler;

    selector = ResolveTaggedValueRef(context, operands);
    handler = gScriptVectorHandlers[selector->value];
    if (handler != NULL) {
        handler(context, operands);
    }
    return 0;
}
