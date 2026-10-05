#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} HudEntry;

typedef struct {
    u8 pad_000[0x6e4];
    HudEntry *entries;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

HudEntry *GetHudEntry(int entryIndex) {
    return &data_ov001_020a04c4.context->entries[entryIndex];
}
