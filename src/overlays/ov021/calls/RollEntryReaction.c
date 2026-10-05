#include "nitro/types.h"

typedef struct ReactionEntry {
    u8 pad0[0x9b4];
    u8 playerIndex;
    u8 pad9b5[0xa51 - 0x9b5];
    u8 reaction;
} ReactionEntry;

typedef struct ReactionSource {
    u8 pad0[0x14];
    int entryId;
} ReactionSource;

typedef struct ReactionParams {
    u8 pad0[0x3c];
    int result;
    u8 pad40[0x28];
    int mode;
} ReactionParams;

extern ReactionEntry *GetBoundedEntryField(int id);
extern int func_ov052_020d1258(ReactionEntry *entry, int *out);
extern void func_ov052_020d1190(ReactionEntry *entry, int reaction);
extern u32 random_next_scaled(u32 range);
extern BOOL IsPlayerEntryFlagSet(u8 index, int flag);

int RollEntryReaction(ReactionSource *source, ReactionParams *params, int *out)
{
    int reaction;
    int result;
    ReactionEntry *entry;

    entry = GetBoundedEntryField(source->entryId);

    entry->reaction = 0;
    *out = 0x16;
    if (params->mode != 1 || (result = func_ov052_020d1258(entry, out)) == 0) {
        reaction = 0;
        if (random_next_scaled(0x64000) < 0x4b000) {
            reaction++;
            if (IsPlayerEntryFlagSet(entry->playerIndex, 0x33)) {
                reaction++;
            }
        }
        func_ov052_020d1190(entry, reaction);
        entry->reaction = reaction;
        result = params->result;
    }
    return result;
}
