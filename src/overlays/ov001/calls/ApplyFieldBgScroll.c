#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x47c];
    s32 panelState;
    u8 pad_480[0x580 - 0x480];
    s32 scrollY;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern u32 func_ov001_0207b3f4(void);
extern s32 func_ov001_02063a38(void);

static inline void SetMainBg1Offset(int x, int y)
{
    *(vu32 *)0x04000014 = (u32)(((x << 0) & 0x1ff) | ((y << 16) & 0x1ff0000));
}

static inline void SetSubBg1Offset(int x, int y)
{
    *(vu32 *)0x04001014 = (u32)(((x << 0) & 0x1ff) | ((y << 16) & 0x1ff0000));
}

void ApplyFieldBgScroll(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;
    s32 scrollY = manager->scrollY;
    s32 subScrollY = scrollY - 0x28;

    if (manager->panelState == 2) {
        SetMainBg1Offset(0, 0);
    } else {
        SetMainBg1Offset(0, scrollY);
    }
    if (func_ov001_0207b3f4() == 2 || func_ov001_02063a38() == 10) {
        SetSubBg1Offset(0, 0);
    } else {
        SetSubBg1Offset(0, subScrollY);
    }
}
