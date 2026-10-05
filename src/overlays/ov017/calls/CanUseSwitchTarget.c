#include "nitro/types.h"

typedef struct ContactTarget {
    void *object;
    int kind;
} ContactTarget;

typedef struct LinkedObject {
    u8 pad_00[0x60];
    void *occupant;
} LinkedObject;

typedef struct ContactLink {
    LinkedObject *other;
    int type;
} ContactLink;

typedef struct ContactInfo {
    u8 pad_00[0x68];
    ContactLink link;
} ContactInfo;

extern u32 func_ov017_020a5dfc(LinkedObject *object);

BOOL CanUseSwitchTarget(ContactTarget *contact)
{
    ContactLink *link;
    int type;

    if (contact->kind == 4) {
        link = &((ContactInfo *)contact->object)->link;
        type = link->type;
        if (type != 0x1b && type != 0x1c && type != 8) {
            return FALSE;
        }
        if (type == 0x1b && func_ov017_020a5dfc(link->other)) {
            return FALSE;
        }
        if (link->type == 8 && link->other->occupant != NULL) {
            return FALSE;
        }
    }
    return TRUE;
}
