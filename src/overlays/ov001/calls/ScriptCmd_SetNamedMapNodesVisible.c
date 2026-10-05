#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern const char *ByteCode_ResolveOperand(void *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern int strlen(const char *str);
extern void ApplyToNamedCollisionFaces(const char *name, int nameLength, BOOL visible);

int ScriptCmd_SetNamedMapNodesVisible(void *context, ScriptOperand *operands)
{
    const char *name;
    int visible;

    name = ByteCode_ResolveOperand(context, operands);
    visible = ScriptVm_ReadOperandInt(context, operands + 1);
    ApplyToNamedCollisionFaces(name, strlen(name), visible != 0);
    return 1;
}
