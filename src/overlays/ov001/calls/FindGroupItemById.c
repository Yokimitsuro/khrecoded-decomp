#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad[7];
} Item;

typedef struct {
    u8 kind;
    u8 count;
    u8 pad[0x1e];
    Item *items;
} Group;

typedef struct {
    u8 pad[8];
    Group *groups[1];
} GroupTable;

extern GroupTable **data_ov001_020a048c;

Item *FindGroupItemById(u32 id, int groupIndex) {
    Group *group = (*data_ov001_020a048c)->groups[groupIndex];
    int i = 0;
    while (i < group->count) {
        if (id == group->items[i].id) {
            return &group->items[i];
        }
        i++;
    }
    return NULL;
}
