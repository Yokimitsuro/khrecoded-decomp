#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
    u8 keepAudio : 1;
} CommState;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 lowFlags : 13;
    u32 selectionLocked : 1;
    u8 pad_218[0x3c];
    u8 selection;
    u8 pad_255[0x25a7];
    s8 pendingSlot;
} FieldState;

extern CommState *gContinueSceneState;
extern FieldState *data_ov001_020a0480;
extern BOOL func_ov001_020645c8(int bitId);
extern u8 func_ov037_020ba564(void);
extern void RefreshSessionSelections(void);

s32 SyncSessionCommFlags(void)
{
    gContinueSceneState->keepAudio = (u8)func_ov001_020645c8(0x3525);
    if (!data_ov001_020a0480->selectionLocked) {
        data_ov001_020a0480->selection = func_ov037_020ba564();
        RefreshSessionSelections();
        data_ov001_020a0480->pendingSlot = -1;
    }
    gContinueSceneState->flags |= 0x8000;
    return 2;
}
