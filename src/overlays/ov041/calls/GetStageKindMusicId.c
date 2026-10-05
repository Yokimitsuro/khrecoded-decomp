#include "nitro/types.h"

u8 GetStageKindMusicId(int stageKind) {
    switch (stageKind) {
    case 0:
        return 7;
    case 2:
        return 0x25;
    case 3:
        return 0x26;
    case 4:
        return 0x25;
    case 5:
        return 0x25;
    case 6:
        return 0x25;
    case 7:
        return 0x25;
    case 10:
        return 0x25;
    case 11:
        return 0x25;
    case 12:
        return 0x26;
    case 14:
        return 0x25;
    case 15:
        return 0x26;
    case 16:
        return 0x26;
    case 17:
        return 4;
    case 18:
        return 6;
    case 21:
        return 0x25;
    case 22:
        return 0xff;
    case 23:
        return 0xff;
    case 24:
        return 0xff;
    case 25:
        return 0xff;
    case 26:
        return 0xff;
    case 0xfd:
        return 4;
    }
    return 0xff;
}
