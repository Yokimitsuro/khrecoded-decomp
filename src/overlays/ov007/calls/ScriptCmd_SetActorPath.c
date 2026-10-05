#include "nitro/types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    s16 node;
    u8 speed;
    u8 wait;
} PathNode;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f050(int actorId);
extern void SetPathTable(void *set, int index, int count, const PathNode *nodes);

BOOL ScriptCmd_SetActorPath(void *vm, ScriptOperand *op) {
    int actorId = ScriptVm_ReadOperandInt(vm, op++);
    int pathIndex = ScriptVm_ReadOperandInt(vm, op++);
    int count = ScriptVm_ReadOperandInt(vm, op++);
    PathNode nodes[32];
    int i;

    for (i = 0; i < count; i++) {
        nodes[i].node = ScriptVm_ReadOperandInt(vm, op++);
        nodes[i].speed = ScriptVm_ReadOperandInt(vm, op++);
        nodes[i].wait = ScriptVm_ReadOperandInt(vm, op++);
    }
    SetPathTable(func_ov001_0207f050(actorId), pathIndex, count, nodes);
    return TRUE;
}
