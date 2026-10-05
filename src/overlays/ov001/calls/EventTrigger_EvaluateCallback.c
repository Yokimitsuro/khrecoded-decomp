#include "nitro/types.h"

struct TableEntry;

typedef struct EntryOps {
    u8 pad_00[0x30];
    BOOL (*check)(struct TableEntry *entry);
} EntryOps;

typedef struct TableEntry {
    u8 pad_00[4];
    EntryOps *ops;
} TableEntry;

typedef struct EventTrigger {
    u8 pad_00[0x10];
    s8 fired;
    u8 pad_11;
    s8 requiredMode;
    u8 pad_13;
    s8 conditionKind;
    s8 tableIndex;
    s16 entryIndex;
} EventTrigger;

extern int func_ov001_02067ed4(void);
extern void *func_ov001_0208723c(int index);
extern TableEntry *func_ov001_02086384(void *table, int index);
extern BOOL func_ov001_02069464(EventTrigger *trigger);

int EventTrigger_EvaluateCallback(EventTrigger *trigger)
{
    TableEntry *entry;
    BOOL result = FALSE;

    trigger->fired = 0;
    if (trigger->requiredMode != func_ov001_02067ed4()) {
        return result;
    }
    if (trigger->conditionKind == 0) {
        entry = func_ov001_02086384(func_ov001_0208723c(trigger->tableIndex), trigger->entryIndex);
        if (entry->ops->check != NULL) {
            result = entry->ops->check(entry);
        }
        if (result) {
            trigger->fired = 1;
        }
    }
    if (!func_ov001_02069464(trigger)) {
        return 0;
    }
    return trigger->fired;
}
