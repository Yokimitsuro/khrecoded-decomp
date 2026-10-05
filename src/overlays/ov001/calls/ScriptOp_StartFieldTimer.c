#include "nitro/types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

typedef struct TimerTarget {
    int value;
    int target;
} TimerTarget;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern int ByteCode_ResolveOperand(void *vm, void *operand);
extern void SetupEventTriggerNode(int id, BOOL repeat, int unused, BOOL paused, BOOL silent, TimerTarget *target);

int ScriptOp_StartFieldTimer(void *vm, ScriptOperand *operands)
{
    int repeat = ScriptVm_ReadOperandInt(vm, &operands[0]);
    int id = ScriptVm_ReadOperandInt(vm, &operands[1]);
    TimerTarget target;
    int paused;
    int silent;

    target.value = ScriptVm_ReadOperandInt(vm, &operands[2]);
    paused = ScriptVm_ReadOperandInt(vm, &operands[3]);
    silent = ScriptVm_ReadOperandInt(vm, &operands[4]);
    target.target = ByteCode_ResolveOperand(vm, &operands[5]);
    SetupEventTriggerNode(id, repeat != 0, 0, paused != 0, silent != 0, &target);
    return 1;
}
