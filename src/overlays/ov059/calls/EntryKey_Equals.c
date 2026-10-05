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

BOOL EntryKey_Equals(EntryKey *a, EntryKey *b)
{
    if (a->kind == 2) {
        if (b->kind != 2) {
            return FALSE;
        }
        if (a->key.pair.first == b->key.pair.first && a->key.pair.second == b->key.pair.second) {
            return TRUE;
        }
    } else {
        if (b->kind != 1) {
            return FALSE;
        }
        if (a->key.value == b->key.value) {
            return TRUE;
        }
    }
    return FALSE;
}
