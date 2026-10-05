#include "nitro/types.h"

typedef struct TriggerSlot {
    u8 pad_00[8];
    s8 requiredMode;
    u8 kind;
    u8 pad_0A[0xE];
} TriggerSlot;

typedef struct TriggerNode {
    u8 pad_00[0x38];
    TriggerSlot slot;
    u8 pad_50[3];
    u8 config;
} TriggerNode;

typedef struct TriggerQueue TriggerQueue;

extern TriggerQueue *data_ov001_020a0498;

extern TriggerNode *func_ov001_02069014(TriggerQueue *queue, u16 id);
extern BOOL func_ov001_020645c8(u32 value);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void func_ov001_020645dc(u32 bit);
extern void MIi_CpuClear32(u32 value, void *dest, u32 size);
extern void func_ov001_02069de0(TriggerSlot *slot, void *source, BOOL isSecondary);
extern void InitArithmeticNode(TriggerSlot *slot, void *params);

void SetupEventTriggerNode(u32 id, BOOL isSecondary, int type, int kind, u32 initialBit, void *params)
{
    TriggerQueue *queue = data_ov001_020a0498;
    TriggerNode *node;
    int bit;
    TriggerSlot *slot;

    if (isSecondary) {
        id += 0xF8;
    }
    bit = id * 2 + 0x331F;
    node = func_ov001_02069014(queue, id);
    if (!func_ov001_020645c8(bit + 1)) {
        WriteSessionPackedBits(bit, 1, initialBit);
        func_ov001_020645dc(bit + 1);
    }
    slot = &node->slot;
    MIi_CpuClear32(0, slot, sizeof(TriggerSlot));
    slot->requiredMode = -1;
    slot->kind = kind;
    switch (type) {
    case 0:
        func_ov001_02069de0(slot, params, isSecondary);
        break;
    case 1:
        InitArithmeticNode(slot, params);
        break;
    }
    node->config |= 2;
}
