#include "nitro/types.h"

typedef struct RecordSet {
    u32 words[4];
} RecordSet;

typedef struct ProfileData {
    RecordSet record;
    u8 pad_10[0x70 - 0x10];
} ProfileData;

typedef struct SelectionView {
    s32 x;
    s32 y;
    u8 pad_08[0x18 - 0x8];
    RecordSet *selection;
    u8 pad_1C[0x4aa - 0x1c];
    u8 alpha;
    u8 layout : 2;
} SelectionView;

typedef struct PanelState {
    u8 pad_00[0x99];
    u8 unk_99_0 : 1;
    u8 hasSelection : 1;
    u8 pad_9A[0x2e8 - 0x9a];
    s32 savedClearCount;
    u8 pad_2EC[0x2f0 - 0x2ec];
    s8 clearCount;
    u8 pad_2F1[0x39c - 0x2f1];
    u8 manager[0xcc94 - 0x39c];
    SelectionView view;
    RecordSet record;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int func_ov013_02070cb4(void);
extern int DispatchContextCommand(u32 command, int value, int extra, void *buffer);
extern void ResetSelectionView(SelectionView *view);
extern void func_ov002_02067c10(void *manager, SelectionView *view);
extern void SetGroupSlotsVisible(void *manager, SelectionView *view, int visible);
extern void ReleaseGroupSlots(void *manager, SelectionView *view);

void RebuildPanelSelection(void) {
    ProfileData profile;
    PanelState *state;

    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    if (data_ov013_02074ce0->hasSelection) {
        ReleaseGroupSlots(data_ov013_02074ce0->manager, &data_ov013_02074ce0->view);
        data_ov013_02074ce0->hasSelection = FALSE;
    }
    MI_CpuFill8(&data_ov013_02074ce0->record, 0, sizeof(RecordSet));
    DispatchContextCommand(0, func_ov013_02070cb4(), 0, &profile);
    state = data_ov013_02074ce0;
    state->record = profile.record;
    state->view.selection = &state->record;
    ResetSelectionView(&data_ov013_02074ce0->view);
    data_ov013_02074ce0->view.alpha = 200;
    data_ov013_02074ce0->view.layout = 1;
    data_ov013_02074ce0->view.x = 0xc6000;
    data_ov013_02074ce0->view.y = 0x24000;
    func_ov002_02067c10(data_ov013_02074ce0->manager, &data_ov013_02074ce0->view);
    SetGroupSlotsVisible(data_ov013_02074ce0->manager, &data_ov013_02074ce0->view, TRUE);
    data_ov013_02074ce0->hasSelection = TRUE;
    data_ov013_02074ce0->savedClearCount = data_ov013_02074ce0->clearCount;
}
