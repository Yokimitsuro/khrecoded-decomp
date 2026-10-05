#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x131];
    s8 flag;
    u8 pad_132[0x12];
    u32 field144;
} SomeObj;

void ClearFlagAndField0x144(SomeObj *obj)
{
    if (obj->flag != 0) {
        obj->flag = 0;
        obj->field144 = 0;
    }
}
