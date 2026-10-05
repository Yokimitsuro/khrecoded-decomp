#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x94];
    s32 selectedSlot;
    u8 pad_98[0x1c];
    s32 confirmed;
    s32 field_b8;
    s32 field_bc;
    u8 pad_C0[0x4];
    s32 fadePending;
} PanelState;

extern PanelState *data_0205fe24;
extern u32 data_0205fde0;
extern u16 data_02060500;

extern void func_0202819c(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void ResetPanelFieldB8AndNotify(void);
extern void UpdatePanelPromptBlink(void);
extern void func_020281c8(void);
extern BOOL ToggleSelectedPanelSlot(void);
extern void func_020284e4(void);
extern void func_0204d994(void);
extern void UpdatePanelSlotBlink(int slot);

BOOL UpdatePanelPromptInput(void)
{
    PanelState *panel = data_0205fe24;

    if (data_0205fde0 == 0) {
        return TRUE;
    }
    if (panel->confirmed != 0) {
        func_0202819c();
        return TRUE;
    }
    if (panel->field_b8 == 0) {
        PlaySoundEffect(0, 3);
        ResetPanelFieldB8AndNotify();
        return TRUE;
    }
    if (panel->fadePending == 0) {
        if (data_02060500 & 8) {
            PlaySoundEffect(0, 3);
            ResetPanelFieldB8AndNotify();
            return TRUE;
        }
        if (panel->field_bc == 0) {
            UpdatePanelPromptBlink();
            func_020281c8();
            return TRUE;
        }
        if (!ToggleSelectedPanelSlot() && (data_02060500 & 1)) {
            if (panel->selectedSlot == 0) {
                ResetPanelFieldB8AndNotify();
            } else {
                func_020284e4();
                func_0204d994();
                panel->confirmed = 1;
            }
            PlaySoundEffect(0, 1);
            return TRUE;
        }
    }
    UpdatePanelPromptBlink();
    UpdatePanelSlotBlink(panel->selectedSlot);
    func_020281c8();
    return TRUE;
}
