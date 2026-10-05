#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_0000[0x27b6];
    u8 lowBits : 6;
    u8 pendingSubModels : 1;
    u8 highBit : 1;
} FieldState;

extern FieldState *data_ov001_020a0480;
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov052_020ceb14(void *entity, int enable);
extern void func_ov052_020ce7c0(void *entity, int mode, int enable);

void SetEntityModeHideSubModels(void *entity, int mode, int enable)
{
    if (mode == 2) {
        BOOL allowed = TRUE;
        if (func_ov001_020645c8(0x351f) || data_ov001_020a0480->pendingSubModels) {
            allowed = FALSE;
        }
        if (enable && allowed) {
            func_ov052_020ceb14(entity, 0);
        }
        if (enable && data_ov001_020a0480->pendingSubModels) {
            data_ov001_020a0480->pendingSubModels = 0;
        }
    }
    func_ov052_020ce7c0(entity, mode, enable);
}
