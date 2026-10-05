#include "nitro/types.h"

typedef struct {
    u8 pad[0x32];
    u8 flagIndex;
} Obj;

typedef struct {
    u8 pad[0x178];
    u32 bits[1];
} FlagSet;

extern FlagSet *data_ov001_020a04fc;

BOOL IsNodeFlagBitClear(Obj *obj) {
    int bitIndex = obj->flagIndex;
    int wordIndex = bitIndex / 32;
    bitIndex = 31 - (bitIndex & 0x1f);
    if (data_ov001_020a04fc->bits[wordIndex] & (1U << bitIndex)) {
        return FALSE;
    }
    return TRUE;
}
