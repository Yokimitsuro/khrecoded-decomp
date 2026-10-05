#include "nitro/types.h"

typedef struct {
    u32 words[3];
} FlagBitsBlock;

extern const FlagBitsBlock data_ov015_02079f88;
extern u8 *data_ov015_0207e960;

void SetContextFlagBit(int index)
{
    FlagBitsBlock localBits = data_ov015_02079f88;
    data_ov015_0207e960[0xba] |= (u8)localBits.words[index];
}
