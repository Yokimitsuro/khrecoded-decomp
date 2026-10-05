#include "nitro/types.h"

typedef BOOL (*BitCompare)(int value, int operand, BOOL previous);
typedef int (*TriggerFunc)(void *trigger);

typedef struct PackedBitRef {
    u16 bitOffset;
    u16 bitCount;
} PackedBitRef;

typedef struct BitChainDef {
    s32 requiredMode;
    s16 operand;
    s8 initial;
    s8 refCount;
    u16 *bitOffsets;
    u16 *bitCounts;
    u32 compareKind;
    u32 param;
} BitChainDef;

typedef struct EventTrigger {
    TriggerFunc evaluate;
    TriggerFunc release;
    TriggerFunc destroy;
    u32 param;
    s8 fired;
    u8 pad_11;
    s8 requiredMode;
    u8 pad_13;
    s16 operand;
    s8 initial;
    s8 refCount;
    BitCompare compare;
    PackedBitRef *refs;
} EventTrigger;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern BOOL func_ov001_02069948(int value, int operand, BOOL previous);
extern BOOL func_ov001_020698e8(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069958(int value, int operand, BOOL previous);
extern BOOL func_ov001_020698f8(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069968(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069908(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069978(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069918(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069988(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069928(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069998(int value, int operand, BOOL previous);
extern BOOL func_ov001_02069938(int value, int operand, BOOL previous);
extern int EventTrigger_EvaluateBitChain(void *trigger);
extern int func_ov001_02069a30(void *trigger);
extern int func_ov001_02069a44(void *trigger);

void InitBitChainTrigger(EventTrigger *trigger, BitChainDef *def)
{
    int i;

    trigger->requiredMode = def->requiredMode;
    trigger->param = def->param;
    trigger->refCount = def->refCount;
    trigger->operand = def->operand;
    trigger->initial = def->initial;
    switch (def->compareKind) {
    case 7:
        trigger->compare = trigger->initial == 0 ? func_ov001_02069948 : func_ov001_020698e8;
        break;
    case 8:
        trigger->compare = trigger->initial == 0 ? func_ov001_02069958 : func_ov001_020698f8;
        break;
    case 9:
        trigger->compare = trigger->initial == 0 ? func_ov001_02069968 : func_ov001_02069908;
        break;
    case 10:
        trigger->compare = trigger->initial == 0 ? func_ov001_02069978 : func_ov001_02069918;
        break;
    case 11:
        trigger->compare = trigger->initial == 0 ? func_ov001_02069988 : func_ov001_02069928;
        break;
    case 12:
        trigger->compare = trigger->initial == 0 ? func_ov001_02069998 : func_ov001_02069938;
        break;
    }
    trigger->refs = NNSi_FndAllocFromDefaultHeap(trigger->refCount * sizeof(PackedBitRef));
    for (i = 0; i < trigger->refCount; i++) {
        trigger->refs[i].bitOffset = def->bitOffsets[i];
        trigger->refs[i].bitCount = def->bitCounts[i];
    }
    trigger->evaluate = EventTrigger_EvaluateBitChain;
    trigger->release = func_ov001_02069a30;
    trigger->destroy = func_ov001_02069a44;
}
