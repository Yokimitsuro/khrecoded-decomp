#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactSlot {
    signed long value;
    signed long field;
    u8 surfaceType;
    u8 pad_09[3];
} ContactSlot;

typedef struct ContactNormal {
    signed long x;
    signed long y;
    signed long z;
} ContactNormal;

typedef struct ContactList {
    ContactSlot slots[16];
    ContactNormal normals[16];
    u8 count;
} ContactList;

typedef struct Mover {
    u8 pad_00[0xb4];
    ContactList *contacts;
    u8 pad_b8[0x2c];
    s8 contactPlane[16];
    s8 planeContact[16];
} Mover;

void RemoveContactSlot(Mover *mover, ContactList *list, u8 slot, u8 planeCount)
{
    u8 count = list->count;
    u8 i;

    for (i = slot; i < (signed long)mover->contacts->count - 1; i++) {
        mover->contactPlane[slot] = mover->contactPlane[slot + 1];
    }
    for (i = 0; i < planeCount; i++) {
        if (mover->planeContact[i] > slot) {
            mover->planeContact[i]--;
        } else if (slot == mover->planeContact[i]) {
            mover->planeContact[i] = -1;
        }
    }
    for (i = slot + 1; i < count; i++) {
        list->slots[i - 1] = list->slots[i];
        list->normals[i - 1] = list->normals[i];
    }
    list->count--;
}
