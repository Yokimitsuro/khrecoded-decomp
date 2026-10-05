#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xa0];
    int kind;
} KindObject;

int GetKindDuration(KindObject *obj)
{
    switch (obj->kind) {
    case 3:
        return 20;
    case 1:
        return 30;
    case 2:
        return 20;
    }
    return 0;
}
