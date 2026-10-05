#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern BOOL IsFieldPanelShown(void);
extern void func_ov001_02071aac(int page, int mode);
extern void func_ov001_02071aa4(void);
extern void func_ov001_02071cd4(void);
extern void func_ov001_02071be4(void);
extern void func_ov001_02071d6c(int argument);

int ScriptCmd_OpenFieldPanelScreen(void *context, ScriptOperand *operands)
{
    int screenType;
    int argument;

    screenType = ScriptVm_ReadOperandInt(context, operands);
    argument = ScriptVm_ReadOperandInt(context, operands + 1);
    if (!IsFieldPanelShown()) {
        return 0;
    }
    switch (screenType) {
    case 0:
        switch (argument) {
        case 9:
            func_ov001_02071aac(7, 1);
            break;
        case 8:
            func_ov001_02071aac(8, 2);
            break;
        default:
            func_ov001_02071aac(argument, 0);
            break;
        }
        break;
    case 1:
        func_ov001_02071aa4();
        break;
    case 2:
        func_ov001_02071cd4();
        break;
    case 3:
        func_ov001_02071be4();
        break;
    case 4:
        func_ov001_02071d6c(argument);
        break;
    }
    return 1;
}
