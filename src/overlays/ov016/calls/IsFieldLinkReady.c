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

BOOL IsFieldLinkReady(FieldLink *link)
{
    if (link->kind == 4) {
        u8 state = link->owner->info->state;
        if (state == 2 || state == 4) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}
