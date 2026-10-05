#include "nitro/types.h"

typedef struct RecordEntry {
    u8 pad_00[0x8];
    u16 flags;
} RecordEntry;

typedef struct RecordUser {
    u8 pad_00[0x38];
    u8 recordIndex;
} RecordUser;

extern RecordEntry *ActorSlot_GetByIndex(int index);
extern void ApplyRecordTableEntry5(int index, int param2, int param3);
extern void FieldObject_SetPhaseMode(RecordUser *user, int state);

void ApplyRecordOrSetState(RecordUser *user, BOOL enable)
{
    if (enable) {
        if (user->recordIndex != 0 && !(ActorSlot_GetByIndex(user->recordIndex)->flags & 2)) {
            ApplyRecordTableEntry5(user->recordIndex, 0, 0);
        }
    } else {
        FieldObject_SetPhaseMode(user, 2);
    }
}
