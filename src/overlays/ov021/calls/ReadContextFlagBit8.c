#include "nitro/types.h"

typedef struct ContextHeader {
    u8 pad_00[4];
    u16 low : 8;
    u16 bit8 : 1;
    u16 high : 7;
} ContextHeader;

typedef struct FlagReader {
    u8 pad_00[0x2c];
    u16 ready;
    u8 pad_2e[2];
    u32 bit8;
} FlagReader;

extern ContextHeader *data_ov021_020b56c4;

int ReadContextFlagBit8(FlagReader *reader)
{
    ContextHeader *header = data_ov021_020b56c4;
    if (header == NULL) {
        return 0;
    }
    reader->ready = 1;
    reader->bit8 = header->bit8;
    return 0;
}
