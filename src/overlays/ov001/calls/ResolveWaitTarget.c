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

typedef struct WaitTarget {
    u8 kind;
    u8 pad_01[3];
    union {
        s32 value;
        struct {
            s16 first;
            s16 second;
        } pair;
    } key;
} WaitTarget;

extern BOOL IsWaitTargetReady(WaitTarget *target);

BOOL ResolveWaitTarget(TaggedKey *source, WaitTarget *target)
{
    BOOL result = TRUE;

    switch (source->kind) {
    case 0:
        result = FALSE;
        target->kind = 0;
        target->key.value = 0;
        break;
    case 1:
        target->kind = 1;
        target->key.pair.first = source->key.pair.first;
        target->key.pair.second = source->key.pair.second;
        break;
    case 2:
        target->kind = 2;
        target->key.value = source->key.value;
        break;
    case 3:
        target->kind = 3;
        target->key.value = source->key.value;
        break;
    case 4:
        target->kind = 4;
        target->key.value = source->key.value;
        break;
    }
    if (!IsWaitTargetReady(target)) {
        result = FALSE;
        target->kind = 0;
        target->key.value = 0;
    }
    return result;
}
