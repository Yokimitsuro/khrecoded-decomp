#include "nitro/types.h"

typedef struct {
    u16 unk0;
    u16 current;
    u16 maximum;
} HpStats;

typedef struct {
    u8 pad_000[0x1d4];
    HpStats *hp;
} BattleEntry;

typedef struct {
    u32 state[4];
    s8 triggered;
    u8 unk11;
    s8 setIndex;
    u8 unk13;
    s8 mode;
    u8 unk15;
    s16 threshold;
} HpTrigger;

extern int func_ov001_02067ed4(void);
extern BattleEntry *func_ov001_0206db5c(int index);
extern BOOL func_ov001_02069464(HpTrigger *trigger);

int CheckLeaderHpTrigger(HpTrigger *trigger)
{
    BattleEntry *entry;

    trigger->triggered = 0;
    if (trigger->setIndex != func_ov001_02067ed4()) {
        return 0;
    }
    entry = func_ov001_0206db5c(0);
    if (entry != NULL) {
        int current = entry->hp->current;
        int maximum = entry->hp->maximum;
        switch (trigger->mode) {
        case 0:
            if (current > trigger->threshold) {
                goto done;
            }
            break;
        case 1:
            if (current * 100 / maximum > trigger->threshold) {
                goto done;
            }
            break;
        default:
            goto done;
        }
        trigger->triggered = 1;
    }
done:
    if (!func_ov001_02069464(trigger)) {
        return 0;
    }
    return trigger->triggered;
}
