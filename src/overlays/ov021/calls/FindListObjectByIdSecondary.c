#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    int id;
} ListObject;

typedef struct {
    u8 pad_00[0x58];
    u8 list[0xc];
} ListOwner;

extern void *NNS_FndGetNextListObject(void *list, void *object);

ListObject *FindListObjectByIdSecondary(ListOwner *owner, int id) {
    ListObject *object;
    ListObject *next;

    for (object = NNS_FndGetNextListObject(owner->list, NULL); object != NULL; object = next) {
        next = NNS_FndGetNextListObject(owner->list, object);
        if (object->id == id) {
            break;
        }
    }
    return object;
}
