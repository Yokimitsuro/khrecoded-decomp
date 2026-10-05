#include "nitro/types.h"
typedef struct { u8 pad_00[0x10]; s32 value; } SourceEntry;
typedef struct { u8 pad_00[0xF0]; s32 counter; s32 value; } TargetState;

BOOL CopyEntryValueIfSet(TargetState *state, SourceEntry *entry, s32 arg2, s32 arg3)
{
    BOOL value = entry->value;
    if (value) {
        state->counter = 0;
        state->value = value;
        return TRUE;
    }
    return FALSE;
}
