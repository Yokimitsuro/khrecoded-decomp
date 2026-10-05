#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x6c];
    int kind;
} Actor;

typedef struct Trigger {
    Actor *actor;
    int mode;
} Trigger;

typedef struct ContactInfo {
    u8 pad_00[0x67];
    u8 unk0 : 2;
    u8 surface : 6;
} ContactInfo;

BOOL CanTriggerOnContact(Trigger *trigger, ContactInfo *contact)
{
    if (trigger->mode == 4) {
        if (contact->surface == 0x10 && (trigger->actor->kind == 1 || trigger->actor->kind == 0x15)) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}
