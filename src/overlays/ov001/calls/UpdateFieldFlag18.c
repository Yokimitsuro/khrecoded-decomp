#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x480];
    u32 lowBits : 18;
    u32 flag18 : 1;
    u32 highBits : 13;
    u8 pad_484[0x94];
    s32 unk_518;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern BOOL IsFieldFlag8Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL func_ov001_02077bd8(void);
extern BOOL func_ov001_02077c24(void);

void UpdateFieldFlag18(BOOL enable)
{
    FieldManager *manager = data_ov001_020a04c4.manager;

    if (!IsFieldFlag8Set() && !IsFieldFlag10Set() && !IsHudFlag7Set()
        && manager->unk_518 == 0 && enable) {
        if (manager->flag18 != 1 && func_ov001_02077bd8()) {
            manager->flag18 = 1;
        }
        return;
    }
    if (manager->flag18 && func_ov001_02077c24()) {
        manager->flag18 = 0;
    }
}
