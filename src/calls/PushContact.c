#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ContactSlot {
    s32 value;
    s32 field;
    u8 surfaceType;
    u8 pad_09[3];
} ContactSlot;

typedef struct ContactList {
    ContactSlot slots[16];
    VecFx32 normals[16];
    u8 count;
} ContactList;

void PushContact(ContactList *list, s32 value, s32 field, u8 surfaceType, VecFx32 *normal)
{
    u8 i;

    if (list->count < 16) {
        list->slots[list->count].value = value;
        list->slots[list->count].field = field;
        list->slots[list->count].surfaceType = surfaceType;
        list->normals[list->count] = *normal;
        list->count++;
        return;
    }
    for (i = 1; i < 16; i++) {
        list->slots[i - 1] = list->slots[i];
        list->normals[i - 1] = list->normals[i];
    }
    list->slots[list->count - 1].value = value;
    list->slots[list->count - 1].field = field;
    list->slots[list->count - 1].surfaceType = surfaceType;
    list->normals[list->count - 1] = *normal;
}
