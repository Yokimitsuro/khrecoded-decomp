#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x608];
    BOOL refreshRequested;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern void func_ov001_02078938(int mode);

void RequestFieldRefresh(void)
{
    data_ov001_020a04c4.manager->refreshRequested = TRUE;
    func_ov001_02078938(0);
}
