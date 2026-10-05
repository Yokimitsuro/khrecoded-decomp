#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x10];
    s32 **table;
} SomeObj;

s32 GetIndexedRecordField(SomeObj *obj, s32 index)
{
    return *obj->table[index] + 8;
}
