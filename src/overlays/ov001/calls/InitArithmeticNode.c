#include "nitro/types.h"

typedef struct ArithmeticParams {
    u32 flag;
    u16 slotA;
    u16 slotB;
    s16 operation;
    u16 operand;
} ArithmeticParams;

typedef struct ArithmeticNode {
    void *evaluate;
    u8 pad_04[4];
    u8 flag;
    u8 pad_09[3];
    u16 slotA;
    u16 slotB;
    s16 operation;
    u16 operand;
} ArithmeticNode;

extern void func_ov001_02069d34(ArithmeticNode *node);

void InitArithmeticNode(ArithmeticNode *node, const ArithmeticParams *params)
{
    node->flag = params->flag;
    node->slotA = params->slotA;
    node->slotB = params->slotB;
    node->operation = params->operation;
    node->operand = params->operand;
    node->evaluate = func_ov001_02069d34;
}
