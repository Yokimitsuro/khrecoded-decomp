#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    u16 *name;
    u16 *description;
} TextEntry;

typedef struct {
    u32 baseA;
    u32 baseB;
    TextEntry *entries;
    u32 *strings;
} State;

extern State *data_020613d0;
extern u32 Archive_LoadFile(u32 fileId, u32 param2);
extern u32 func_0202c4a0(u32 fileId, u32 param2);
extern u16 *SkipWideString(u16 *text);

void LoadTextEntryTablesLarge(int useAlt)
{
    State *state = data_020613d0;
    int i;
    u16 *name;
    u16 *description;
    TextEntry *entry;

    if (useAlt != 0) {
        state->entries = (TextEntry *)func_0202c4a0(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0x11);
        state->strings = (u32 *)func_0202c4a0(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0x11);
    } else {
        state->entries = (TextEntry *)Archive_LoadFile(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0x11);
        state->strings = (u32 *)Archive_LoadFile(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0x11);
    }
    /* Strings follow a leading offset word */
    entry = state->entries;
    name = (u16 *)(state->strings + 1);
    description = (u16 *)((u8 *)state->strings + state->strings[0]);
    for (i = 0; i < 0x200; i++) {
        entry->name = name;
        entry->description = description;
        name = SkipWideString(name);
        description = SkipWideString(description);
        entry++;
    }
}
