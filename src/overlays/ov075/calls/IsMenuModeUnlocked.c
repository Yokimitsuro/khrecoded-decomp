#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2c6c];
    u8 unlockedModes;
} SaveData;

extern SaveData *data_0205fe0c;

BOOL IsMenuModeUnlocked(int mode)
{
    u8 unlocked = data_0205fe0c->unlockedModes;
    int bit;
    BOOL result;

    switch (mode) {
    case 1:
        bit = 0;
        break;
    case 2:
        bit = 3;
        break;
    case 3:
        bit = 4;
        break;
    case 4:
        bit = 2;
        break;
    case 5:
        bit = 1;
        break;
    }
    result = TRUE;
    if (!(unlocked & (1 << bit))) {
        result = FALSE;
    }
    return result;
}