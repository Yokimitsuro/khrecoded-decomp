#include "nitro/types.h"

typedef struct {
    u16 kind : 4;
    u16 id : 12;
} VisitedEntry;

typedef struct {
    VisitedEntry entries[7];
    u16 count;
} VisitedList;

typedef struct {
    u8 pad_00[0xdc];
    VisitedList visited;
} FieldObject;

BOOL RecordVisitedEntry(FieldObject *obj, int kind, int id)
{
    VisitedList *list = &obj->visited;
    u32 count = list->count;
    int i;

    if (count < 7) {
        for (i = 0; i < (int)count; i++) {
            if (kind == list->entries[i].kind && id == list->entries[i].id) {
                return TRUE;
            }
        }
        list->entries[count].kind = kind;
        list->entries[list->count].id = id;
        list->count++;
    }
    return FALSE;
}
