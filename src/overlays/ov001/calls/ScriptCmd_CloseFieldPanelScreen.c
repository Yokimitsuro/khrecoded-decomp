#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern BOOL IsCounterNegative(void);
extern void func_ov001_02071b7c(void);
extern void func_ov001_02071aa8(void);
extern void *func_ov001_02071d64(void);
extern void *func_ov001_02071ccc(void);
extern void *func_ov001_02071de8(void);

int ScriptCmd_CloseFieldPanelScreen(void *context, ScriptOperand *operands)
{
    if (IsCounterNegative()) {
        switch (ScriptVm_ReadOperandInt(context, operands)) {
        case 0:
            func_ov001_02071b7c();
            break;
        case 1:
            func_ov001_02071aa8();
            break;
        case 2:
            func_ov001_02071d64();
            break;
        case 3:
            func_ov001_02071ccc();
            break;
        case 4:
            func_ov001_02071de8();
            break;
        }
        return 1;
    }
    return 0;
}
