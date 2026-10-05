#include "nitro/types.h"

typedef struct {
    u32 position : 9;
    u8 pad_04[0x1dc];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

typedef struct {
    u8 pad_00[2];
    s8 rowIndex;
} RowSelector;

typedef struct {
    u8 pad_00[4];
    RowOwner *owner;
    u8 pad_08[0x2b];
    u8 limit;
    u8 pad_34[0xb8];
    RowSelector *selector;
} RowGroup;

int GetRemainingRowSpan(RowGroup *group)
{
    return group->limit - group->owner->rows[group->selector->rowIndex].position;
}
