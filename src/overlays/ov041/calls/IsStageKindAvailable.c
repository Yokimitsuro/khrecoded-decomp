#include "nitro/types.h"

extern int ResolveEventVariant(int index);

BOOL IsStageKindAvailable(int stageKind) {
    BOOL found = FALSE;
    int i;

    for (i = 0; i < 10; i++) {
        int kind = -1;
        switch (ResolveEventVariant(i)) {
        case 0xe1:
            kind = 6;
            break;
        case 0xe2:
            kind = 7;
            break;
        case 0xe3:
            kind = 8;
            break;
        case 0xe4:
            kind = 9;
            break;
        case 0xe5:
            kind = 0xc;
            break;
        case 0xe6:
            kind = 0xf;
            break;
        case 0xe7:
            kind = 0x12;
            break;
        case 0xe8:
            kind = 0x13;
            break;
        case 0xe9:
            kind = 0x14;
            break;
        case 0xea:
            kind = 0x15;
            break;
        case 0xeb:
            kind = 0x16;
            break;
        case 0xec:
            kind = 0x17;
            break;
        case 0xb7:
            kind = 0x18;
            break;
        case 0xb8:
            kind = 0x19;
            break;
        }
        if (kind == stageKind) {
            found = TRUE;
            break;
        }
    }
    return found;
}
