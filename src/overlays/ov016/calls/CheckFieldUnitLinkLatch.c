#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x194];
    u8 state;
} OwnerInfo;

typedef struct {
    u8 pad_00[0x14];
    OwnerInfo *info;
} Owner;

typedef struct {
    Owner *owner;
    int kind;
} FieldLink;

typedef struct {
    u8 pad_00[0xc0];
    u32 flags;
} FieldUnit;

int CheckFieldUnitLinkLatch(FieldLink *link, void *other, FieldUnit *unit)
{
    if (!(unit->flags & 0x2000)) {
        if (link->kind == 4) {
            switch (link->owner->info->state) {
            case 0:
            case 1:
            case 2:
            case 4:
                unit->flags |= 0x2000;
                return 1;
            }
        }
        return 1;
    }
    return 2;
}