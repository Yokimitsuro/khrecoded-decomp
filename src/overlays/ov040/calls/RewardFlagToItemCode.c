#include "nitro/types.h"

u32 RewardFlagToItemCode(u32 flagId)
{
    u32 code;

    code = 0xffffffff;
    switch (flagId) {
    case 0xcb:
        code = 0x1e0;
        break;
    case 0xcc:
        code = 0x1e1;
        break;
    case 0xcd:
        code = 0x1e2;
        break;
    case 0xce:
        code = 0x1e3;
        break;
    case 0xcf:
        code = 0x1e4;
        break;
    case 0xd0:
        code = 0x1e5;
        break;
    case 0xd1:
        code = 0x1e6;
        break;
    case 0xd2:
        code = 0x1e7;
        break;
    case 0xd3:
        code = 0x1e8;
        break;
    case 0xd4:
        code = 0x1e9;
        break;
    case 0xd5:
        code = 0x1ea;
        break;
    case 0xd6:
        code = 0x1eb;
        break;
    case 0xd7:
        code = 0x1ec;
        break;
    case 0xd8:
        code = 0x1ed;
    }
    return code;
}
