#include "nitro/types.h"

typedef struct TaggedKey {
    u32 kind;
    union {
        s32 value;
        struct {
            s16 first;
            s16 second;
        } pair;
    } key;
} TaggedKey;

BOOL MatchesTaggedKey(TaggedKey *expected, TaggedKey *actual)
{
    BOOL result = FALSE;

    switch (expected->kind) {
    case 2:
        if (actual->key.value != expected->key.value) {
            break;
        }
        result = TRUE;
        break;
    case 3:
        if (actual->key.value != expected->key.value) {
            break;
        }
        result = TRUE;
        break;
    case 1:
        if (actual->key.pair.first != expected->key.pair.first) {
            break;
        }
        if (actual->key.pair.second != expected->key.pair.second) {
            break;
        }
        result = TRUE;
        break;
    case 4:
        if (actual->key.value != expected->key.value) {
            break;
        }
        result = TRUE;
        break;
    }
    return result;
}
