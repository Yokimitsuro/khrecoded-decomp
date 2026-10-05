#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x76];
    s8 weight;
    u8 pad_77[0xbf - 0x77];
    s8 currentWeight;
} FieldObject;

static inline void SetWeight(FieldObject *obj, int weight)
{
    obj->weight = weight;
    obj->currentWeight = obj->weight;
}

void SetFieldObjectWeightByKind(FieldObject *obj, int kind)
{
    switch (kind) {
    case 11:
        SetWeight(obj, 1);
        return;
    case 3:
        SetWeight(obj, 1);
        return;
    case 0:
        SetWeight(obj, 1);
        return;
    case 16:
        SetWeight(obj, 3);
        return;
    case 1:
        SetWeight(obj, 1);
        return;
    case 10:
        SetWeight(obj, 3);
        return;
    }
    SetWeight(obj, 0);
}
