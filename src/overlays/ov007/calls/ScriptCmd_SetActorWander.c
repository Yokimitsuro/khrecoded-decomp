#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    s16 pathIndex;
    s8 mode;
    u8 pad;
    union {
        VecFx32 pos;
        u8 wait;
    } arg;
} WanderParams;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f060(int a, int b);
extern void func_ov007_020a18e0(void *actor, WanderParams *params);

BOOL ScriptCmd_SetActorWander(void *vm, ScriptOperand *op) {
    int group = ScriptVm_ReadOperandInt(vm, op);
    int actorId = ScriptVm_ReadOperandInt(vm, op + 1);
    WanderParams params;

    params.pathIndex = ScriptVm_ReadOperandInt(vm, op + 2);
    params.mode = ScriptVm_ReadOperandInt(vm, op + 3);
    switch (params.mode) {
    case 0:
    case 3:
        params.arg.pos.x = ScriptVm_ReadOperandFx32(vm, op + 4);
        params.arg.pos.y = ScriptVm_ReadOperandFx32(vm, op + 5);
        params.arg.pos.z = ScriptVm_ReadOperandFx32(vm, op + 6);
        break;
    case 1:
    case 2:
        params.arg.wait = ScriptVm_ReadOperandInt(vm, op + 4);
        break;
    }
    func_ov007_020a18e0(func_ov001_0207f060(group, actorId), &params);
    return TRUE;
}
