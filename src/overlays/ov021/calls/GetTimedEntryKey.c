#include "nitro/types.h"

typedef struct KeyClock {
    u8 pad0[0x10];
    int time;
    int keepAll;
} KeyClock;

extern KeyClock data_ov021_020b5640;

u32 GetTimedEntryKey(int id)
{
    u32 key = ((data_ov021_020b5640.time + 0x8000U & 0xfffffc) << 7) | 0x80000000 | (id + 0x50 & 0x1ff);

    if (data_ov021_020b5640.keepAll == 0) {
        switch (id) {
        case 0x16:
        case 0x1f:
        case 0x23:
        case 0x24:
        case 0x28:
            key = 0;
            break;
        }
    }
    return key;
}
