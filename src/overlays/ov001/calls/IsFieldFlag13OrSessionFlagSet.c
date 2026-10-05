#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x480];
    u32 lowBits : 13;
    u32 flag13 : 1;
    u32 highBits : 18;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern BOOL func_ov001_020645c8(u32 flagIndex);

BOOL IsFieldFlag13OrSessionFlagSet(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;

    if (manager == NULL) {
        if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
            return TRUE;
        }
        return FALSE;
    }
    if (manager->flag13 == 1) {
        return TRUE;
    }
    return FALSE;
}
