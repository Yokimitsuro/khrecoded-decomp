#include "nitro/types.h"

int GetStageKindSoundId(int stageKind) {
    switch (stageKind) {
    case 0:
        return 0xd0;
    case 2:
        return 0xd3;
    case 3:
        return 0xd4;
    case 4:
        return 0xd7;
    case 5:
        return 0xd5;
    case 6:
        return 0xd8;
    case 7:
        return 0xd9;
    case 10:
        return 0xe5;
    case 11:
        return 0xe3;
    case 12:
        return 0xe4;
    case 14:
        return 0xec;
    case 15:
        return 0xeb;
    case 16:
        return 0xed;
    case 17:
        return 0xea;
    case 18:
        return 0xef;
    case 21:
        return 0xdd;
    case 22:
        return 0xde;
    case 23:
        return 0xdf;
    case 24:
        return 0xe0;
    case 25:
        return 0xe1;
    case 26:
        return 0xe2;
    case 0xfd:
        return 0x43;
    }
    return -1;
}
