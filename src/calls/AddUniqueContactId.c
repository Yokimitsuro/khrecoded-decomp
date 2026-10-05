#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ContactList {
    u8 pad_00[0xc0];
    VecFx32 normals[16];
    u8 count;
    u8 ids[32];
    u8 idCount;
} ContactList;

void AddUniqueContactId(ContactList *list, u8 id)
{
    u8 count = list->idCount;
    u8 i;

    for (i = 0; i < count; i++) {
        if (id == list->ids[i]) {
            return;
        }
    }
    list->ids[list->idCount++] = id;
}
