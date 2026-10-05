#include "nitro/types.h"

typedef struct PackedBitRef {
    u16 bitOffset;
    u16 bitCount;
} PackedBitRef;

typedef BOOL (*BitCompare)(int value, int operand, BOOL previous);

typedef struct EventTrigger {
    u8 pad_00[0x10];
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

extern int func_ov001_02067ed4(void);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern BOOL func_ov001_02069464(EventTrigger *trigger);

int EventTrigger_EvaluateBitChain(EventTrigger *trigger)
{
    int i;
    s16 value;

    if (trigger->requiredMode != -1 && trigger->requiredMode != func_ov001_02067ed4()) {
        return 0;
    }
    if (trigger->initial == 0) {
        trigger->fired = FALSE;
    } else {
        trigger->fired = TRUE;
    }
    for (i = 0; i < trigger->refCount; i++) {
        value = ReadSessionPackedBits(trigger->refs[i].bitOffset, trigger->refs[i].bitCount);
        trigger->fired = trigger->compare(value, trigger->operand, trigger->fired != 0) != 0;
    }
    if (!func_ov001_02069464(trigger)) {
        return 0;
    }
    return trigger->fired;
}
