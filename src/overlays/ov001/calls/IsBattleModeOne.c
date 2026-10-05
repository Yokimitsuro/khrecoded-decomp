#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_0000[0x27f1];
    u8 enabled : 1;
    u8 battleMode : 3;
    u8 extra : 4;
} FieldState;

extern FieldState *data_ov001_020a0480;

BOOL IsBattleModeOne(void)
{
    if (data_ov001_020a0480->battleMode == 1) {
        return TRUE;
    }
    return FALSE;
}
