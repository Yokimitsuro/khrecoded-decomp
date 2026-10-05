#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 pad_02[0x6];
} ScriptOperand;

typedef struct BoxSize {
    s32 width;
    s32 height;
} BoxSize;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern int ByteCode_ResolveOperand(void *vm, ScriptOperand *operand);
extern char *strcat(char *dst, const char *src);
extern void Utf8ToUcs2(const char *src, u16 *dst, int dstCount);
extern BOOL OpenTextWindowVariant(const BoxSize *boxSize, const u16 *text, s32 optionA, s32 optionB);
extern const char data_ov036_020c385c[];

BOOL ScriptCmd_ShowJoinedMessage(void *vm, ScriptOperand *op)
{
    BoxSize box;
    u16 text[0x200];
    char joined[0x100];
    int i;

    box.width = ScriptVm_ReadOperandInt(vm, op++);
    box.height = ScriptVm_ReadOperandInt(vm, op++);
    joined[0] = '\0';
    for (i = 0; i < 2; i++) {
        if (op->type == 0) {
            break;
        }
        if (i > 0) {
            strcat(joined, data_ov036_020c385c);
        }
        strcat(joined, (const char *)ByteCode_ResolveOperand(vm, op++));
    }
    Utf8ToUcs2(joined, text, 0x200);
    OpenTextWindowVariant(&box, text, ScriptVm_ReadOperandInt(vm, op), 0);
    return TRUE;
}
