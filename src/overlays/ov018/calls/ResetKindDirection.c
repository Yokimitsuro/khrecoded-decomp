#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x53];
    s8 direction;
    int timer;
    u8 pad_58[0x48];
    int kind;
} KindObject;

void ResetKindDirection(KindObject *obj)
{
    switch (obj->kind) {
    case 3:
        obj->direction = 1;
        break;
    case 1:
        obj->direction = 1;
        break;
    case 2:
        obj->direction = -1;
        break;
    }
    obj->timer = 0;
}
