#include "nitro/types.h"

typedef struct ListElement {
    u16 id;
    u8 pad_02[0x22];
    u8 active : 1;
    u8 loaded : 1;
    u8 pad_25[0xB];
} ListElement;

typedef struct ElementList {
    u8 pad_00[0x10];
    ListElement *items;
    u8 pad_14[0x20];
    int count;
} ElementList;

ListElement *FindLoadedElementById(ElementList *list, u32 id)
{
    int i;

    for (i = 0; i < list->count; i++) {
        if (list->items[i].loaded == 1 && id == list->items[i].id) {
            break;
        }
    }
    return &list->items[i];
}
