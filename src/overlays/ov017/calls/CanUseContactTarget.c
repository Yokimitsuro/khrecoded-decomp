#include "nitro/types.h"

typedef struct ContactTarget {
    void *object;
    int kind;
} ContactTarget;

typedef struct ContactLink {
    void *other;
    int type;
} ContactLink;

typedef struct ContactInfo {
    u8 pad_00[0x68];
    ContactLink link;
} ContactInfo;

extern BOOL IsObjectInChain(void *object, void *target);

BOOL CanUseContactTarget(ContactTarget *contact, void *object)
{
    ContactLink *link;
    int type;

    if (contact->kind == 4) {
        link = &((ContactInfo *)contact->object)->link;
        type = link->type;
        if (type != 6 && type != 7 && type != 0x1b && type != 0x1c && type != 8) {
            return FALSE;
        }
        if (type == 8 && IsObjectInChain(object, link->other)) {
            return FALSE;
        }
    }
    return TRUE;
}
