#include "nitro/types.h"

typedef struct LinkTarget {
    u8 kind;
    u8 group;
    u8 index;
} LinkTarget;

typedef struct FieldLinkOwner {
    u8 pad_000[0x1A4];
    LinkTarget link;
} FieldLinkOwner;

extern u32 func_ov001_0207f060(u32 param1, u32 param2);
extern u32 func_ov001_0208724c(u32 param1, u32 param2);

u32 QueryLinkTarget(FieldLinkOwner *owner)
{
    LinkTarget *link = &owner->link;

    switch (link->kind) {
    case 2:
        return func_ov001_0207f060(link->group, link->index);
    case 4:
        return func_ov001_0208724c(link->group, link->index);
    }
    return 0;
}
