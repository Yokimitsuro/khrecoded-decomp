#include "nitro/types.h"

typedef struct ContextHeader {
    u8 pad_00[4];
    u16 low : 11;
    u16 bit11 : 1;
    u16 high : 4;
} ContextHeader;

typedef struct FlagReader {
    u8 pad_00[0x2c];
    u16 ready;
    u8 pad_2e[2];
    u32 bit11;
} FlagReader;

extern ContextHeader *data_ov021_020b56c4;

int ReadContextFlagBit11(FlagReader *reader)
{
    ContextHeader *header = data_ov021_020b56c4;
    if (header == NULL) {
        return 0;
    }
    reader->ready = 1;
    reader->bit11 = header->bit11;
    return 0;
}
