#include "nitro/types.h"

typedef struct ContextHeader {
    u8 pad_00[4];
    u16 low : 10;
    u16 bit10 : 1;
    u16 high : 5;
} ContextHeader;

typedef struct FlagReader {
    u8 pad_00[0x2c];
    u16 ready;
    u8 pad_2e[2];
    u32 bit10;
} FlagReader;

extern ContextHeader *data_ov021_020b56c4;

int ReadContextFlagBit10(FlagReader *reader)
{
    ContextHeader *header = data_ov021_020b56c4;
    if (header == NULL) {
        return 0;
    }
    reader->ready = 1;
    reader->bit10 = header->bit10;
    return 0;
}
