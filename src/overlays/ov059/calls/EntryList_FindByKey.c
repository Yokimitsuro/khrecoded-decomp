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

extern u32 func_ov059_020cf46c(void *list, u32 firstId, u32 secondId);
extern int EntryList_FindByValue(void *list, u32 value);

int EntryList_FindByKey(void *list, EntryKey *key)
{
    if (key->kind == 2) {
        return func_ov059_020cf46c(list, key->key.pair.first, key->key.pair.second);
    }
    return EntryList_FindByValue(list, key->key.value);
}
