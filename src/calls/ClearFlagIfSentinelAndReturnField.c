#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xC];
    u32 unk_0C;
    u8 pad_10[0x44];
    s32 unk_54;
} UnkStruct_0203ab80;

u32 ClearFlagIfSentinelAndReturnField(UnkStruct_0203ab80 *obj)
{
    if (obj->unk_54 == -1) {
        obj->unk_54 = 0;
    }
    return obj->unk_0C;
}
