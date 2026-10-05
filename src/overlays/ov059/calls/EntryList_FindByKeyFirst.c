#include "nitro/types.h"

typedef struct {
    union {
        u32 value;
        struct {
            u16 first;
            u16 second;
        } pair;
    } key;
    s32 kind;
} EntryKey;

extern int EntryList_FindByFirstId(void *list, u16 id);
extern int EntryList_FindByValue(void *list, u32 value);

int EntryList_FindByKeyFirst(void *list, EntryKey *key)
{
    if (key->kind == 2) {
        return EntryList_FindByFirstId(list, key->key.pair.first);
    }
    return EntryList_FindByValue(list, key->key.value);
}
