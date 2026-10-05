#include "nitro/types.h"

typedef struct ContextHeader {
    u8 pad_00[6];
    u16 low : 13;
    u16 bit13 : 1;
    u16 high : 2;
} ContextHeader;

typedef struct FlagReader {
    u8 pad_00[0x2c];
    u16 ready;
    u8 pad_2e[2];
    u32 bit13;
} FlagReader;

extern ContextHeader *data_ov021_020b56c4;

int ReadContextFlagBit13(FlagReader *reader)
{
    ContextHeader *header = data_ov021_020b56c4;
    if (header == NULL) {
        return 0;
    }
    reader->ready = 1;
    reader->bit13 = header->bit13;
    return 0;
}
