#include "nitro/types.h"

typedef struct PanelObject {
    u8 pad_00[0x94];
    u32 unk_94_0 : 1;
    u32 isActive : 1;
} PanelObject;

typedef struct PanelState {
    u8 pad_00[0x2bc];
    s32 unk_2BC;
    s32 unk_2C0;
    s32 unk_2C4;
    u32 slotFlags;
    u8 pad_2CC[0x22];
    s8 selectedSlot;
    u8 pad_2EF[0x6818 - 0x2ef];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern PanelObject *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9604(void *panel, PanelObject *object);
extern void func_ov027_020b96c0(void *panel, PanelObject *object, int mode);

void RefreshSelectedSlotFlags(void) {
    void *panel;
    PanelObject *object;

    data_ov013_02074ce0->unk_2BC = 0;
    data_ov013_02074ce0->unk_2C0 = 0;
    data_ov013_02074ce0->unk_2C4 = 0;
    data_ov013_02074ce0->slotFlags = 0;
    if (FindWidgetById(data_ov013_02074ce0->panel, data_ov013_02074ce0->selectedSlot + 201)->isActive) {
        data_ov013_02074ce0->slotFlags |= 1;
    }
    if (FindWidgetById(data_ov013_02074ce0->panel, data_ov013_02074ce0->selectedSlot + 101)->isActive) {
        data_ov013_02074ce0->slotFlags |= 2;
    }
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 5);
    func_ov027_020b9604(panel, object);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 5);
    func_ov027_020b96c0(panel, object, 0);
}
