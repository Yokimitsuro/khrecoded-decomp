#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x60c];
    int slotValues[2];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern void LoadSlotIconGraphics(int slot, int iconId);
extern int func_ov001_0207162c(int a, int b, int c, int d);
extern BOOL IsFieldFlag8Set(void);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern void func_ov001_02078710(s32 index, s32 kind);

void SetFieldSlotValue(int index, int value, int param, int extra)
{
    if (value == -1 || index < 0 || index > 1) {
        return;
    }
    data_ov001_020a04c4.manager->slotValues[index] = value;
    LoadSlotIconGraphics(index, value);
    func_ov001_0207162c(index + 1, extra, param, extra);
    if (IsFieldFlag8Set() || IsFieldFlag13OrSessionFlagSet()) {
        func_ov001_02078710(index, value);
    }
}
