#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 words[2];
} ScriptOperand;

extern int GetTextWindowStatus(void);
extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern int func_ov036_020c30f8(void);
extern BOOL func_ov001_020645c8(u32 bitOffset);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void func_ov036_020bda00(void);
extern void func_ov036_020c3374(void);

BOOL ScriptCmd_WaitWindowAnswer(void *vm, ScriptOperand *operands)
{
    int expected;
    int choice;

    switch (GetTextWindowStatus()) {
    case 0:
        expected = ScriptVm_ReadOperandInt(vm, &operands[2]);
        choice = func_ov036_020c30f8();
        if (func_ov001_020645c8(choice + 0x3700)) {
            if (choice == expected) {
                WriteSessionPackedBits(0x3521, 4, 2);
            } else {
                WriteSessionPackedBits(0x3521, 4, 1);
            }
        } else {
            WriteSessionPackedBits(0x3521, 4, 0);
        }
        func_ov036_020bda00();
        return TRUE;
    case 3:
        func_ov036_020c3374();
        break;
    }
    return FALSE;
}
