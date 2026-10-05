#ifndef KH_RECODED_OV032_ROW_DEFINITION_H
#define KH_RECODED_OV032_ROW_DEFINITION_H

#include "nitro/types.h"

typedef struct RowDefinition {
    u32 moveSpeed;
    s16 respawnLimit;
    s16 cycleLimit;
    s16 stepLimit;
    s16 turnLimit;
    s32 idleLimit;
    u8 sequence[11];
    u8 pad_1b[0xd];
} RowDefinition;

typedef struct RowEntry {
    u32 flags : 28;
    u32 definitionIndex : 4;
    u8 pad_04[0x1dc];
} RowEntry;

typedef struct RowOwner {
    u8 pad_00[0xcc];
    RowEntry *rows;
    RowDefinition *definitions;
} RowOwner;

RowDefinition *GetRowDefinition(RowOwner *owner, s32 index);

#endif
