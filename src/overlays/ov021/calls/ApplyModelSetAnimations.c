#include "nitro/types.h"

typedef struct ModelSet {
    u32 flags;
    u32 hasSub;
    u8 resource[0x220];
    void *sub;
} ModelSet;

typedef struct AnimIdList {
    u32 ids[5];
} AnimIdList;

extern const AnimIdList data_ov021_020b4fc8;
extern int *func_01ffb2f8(void *model, u16 id, int arg);

void ApplyModelSetAnimations(ModelSet *set, int arg)
{
    int i;
    u32 id;
    AnimIdList list;

    if (!(set->flags & 1)) {
        return;
    }
    list = data_ov021_020b4fc8;
    for (i = 0; i < 5; i++) {
        id = list.ids[i];
        func_01ffb2f8(set->resource, id, arg);
        if (set->hasSub != 0 && set->sub != NULL) {
            func_01ffb2f8(set->sub, id, arg);
        }
    }
}
