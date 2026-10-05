#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x480];
    u32 lowBits : 8;
    u32 flag8 : 1;
    u32 flag9 : 1;
    u32 flag10 : 1;
    u32 midBits : 5;
    u32 flag16 : 1;
    u32 highBits : 15;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

BOOL IsFieldFlag16Set(void)
{
    if (data_ov001_020a04c4.manager->flag16 == 1) {
        return TRUE;
    }
    return FALSE;
}
