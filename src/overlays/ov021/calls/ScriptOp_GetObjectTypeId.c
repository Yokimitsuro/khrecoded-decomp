#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    u16 resultTag;
    u16 pad_2e;
    s32 resultValue;
} ScriptContext;

typedef struct {
    u8 pad_00[8];
    TaggedValue operand;
} ScriptCommand;

typedef struct StageObject {
    u8 pad_000[0x280];
    u16 typeId;
} StageObject;

typedef struct ScriptGlobals {
    u8 pad_00[8];
    StageObject *activeObject;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern StageObject *FindStageObjectById(u16 id);

int ScriptOp_GetObjectTypeId(ScriptContext *context, ScriptCommand *command)
{
    TaggedValue *idValue = ResolveTaggedValueRef(context, &command->operand);
    StageObject *object = data_ov021_020b56c4.activeObject;
    StageObject *found;

    if (object == NULL) {
        return 0;
    }
    if (idValue->value != 0) {
        found = FindStageObjectById(idValue->value);
        if (found != NULL) {
            object = found;
        }
    }
    context->resultTag = 1;
    context->resultValue = object->typeId;
    return 0;
}
