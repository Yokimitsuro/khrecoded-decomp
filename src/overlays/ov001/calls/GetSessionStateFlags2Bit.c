#include "nitro/types.h"

typedef struct
{
    u32 bits : 2;
} SessionStateFlags2;

extern u8 *data_0205fe0c;

u32 GetSessionStateFlags2Bit(void)
{
    return ((SessionStateFlags2 *)(data_0205fe0c + 0x2878))->bits;
}
