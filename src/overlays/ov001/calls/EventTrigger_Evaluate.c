#include "nitro/types.h"

typedef struct EventTrigger {
    u8 pad_00[0x10];
    s8 fired;
    u8 pad_11;
    s8 requiredMode;
    u8 pad_13;
    s8 conditionKind;
    u8 pad_15;
    u16 eventIndex;
} EventTrigger;

extern int func_ov001_02067ed4(void);
extern s32 func_ov001_02087890(s32 mode);
extern BOOL func_ov001_0208784c(u16 eventIndex);
extern BOOL func_ov001_02069464(EventTrigger *trigger);

int EventTrigger_Evaluate(EventTrigger *trigger)
{
    trigger->fired = 0;
    if (trigger->requiredMode != func_ov001_02067ed4()) {
        return 0;
    }
    switch (trigger->conditionKind) {
    case 0:
        if (func_ov001_02087890(1)) {
            trigger->fired = 1;
        }
        break;
    case 1:
        if (func_ov001_0208784c(trigger->eventIndex)) {
            trigger->fired = 1;
        }
        break;
    }
    if (!func_ov001_02069464(trigger)) {
        return 0;
    }
    return trigger->fired;
}
