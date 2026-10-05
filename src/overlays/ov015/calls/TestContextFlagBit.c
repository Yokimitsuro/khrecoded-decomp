#include "nitro/types.h"

typedef struct {
    u32 words[3];
} FlagBitsBlock;

extern const FlagBitsBlock data_ov015_02079f4c;
extern u8 *data_ov015_0207e960;

BOOL TestContextFlagBit(int index)
{
    FlagBitsBlock localBits = data_ov015_02079f4c;
    return (data_ov015_0207e960[0xba] & localBits.words[index]) != 0;
}
