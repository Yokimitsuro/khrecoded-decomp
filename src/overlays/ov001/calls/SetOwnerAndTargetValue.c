#include "nitro/types.h"

typedef struct LinkedTarget {
    u8 pad_000[0x1C0];
    u32 value;
} LinkedTarget;

typedef struct LinkedValueOwner {
    u8 pad_00[0xC];
    LinkedTarget *target;
    u8 pad_10[0x44];
    u32 value;
} LinkedValueOwner;

void SetOwnerAndTargetValue(LinkedValueOwner *owner, u32 value)
{
    owner->value = value;
    if (owner->target != NULL) {
        owner->target->value = value;
    }
}
