#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad2;
    s32 payload;
} ScriptOperand;

typedef struct ScriptObj {
    u8 pad_00[0x1cc];
    s32 armed;
    s32 valueA;
    s32 valueB;
    char text[0x40];
} ScriptObj;

extern int ScriptVm_ReadOperandInt(void *obj, void *cmd);
extern ScriptOperand *ScriptVm_ResolveOperand(void *obj, void *cmd);
extern int ByteCode_ResolveOperand(void *obj, void *operand);
extern char *strncpy(char *dst, const char *src, unsigned int n);

int func_02026590(ScriptObj *obj, ScriptOperand *cmd)
{
    ScriptOperand *resolved = ScriptVm_ResolveOperand(obj, cmd + 2);

    obj->valueA = ScriptVm_ReadOperandInt(obj, cmd);
    obj->valueB = ScriptVm_ReadOperandInt(obj, cmd + 1);

    if (resolved->type == 0) {
        obj->text[0] = 0;
    } else {
        char *src = (char *)ByteCode_ResolveOperand(obj, resolved);
        strncpy(obj->text, src, 0x3f);
        obj->text[0x3f] = 0;
    }

    obj->armed = 0;
    return 3;
}
