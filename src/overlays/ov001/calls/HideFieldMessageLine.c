#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x480];
    u32 isSliding : 1;
    u32 unk_480_1 : 3;
    u32 isPaused : 1;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern void ReleasePendingSceneTags(void);
extern void ClearFieldStatusRow(void);

void HideFieldMessageLine(void)
{
    if (data_ov001_020a04c4.manager->isPaused != 1) {
        ReleasePendingSceneTags();
        ClearFieldStatusRow();
    }
}
