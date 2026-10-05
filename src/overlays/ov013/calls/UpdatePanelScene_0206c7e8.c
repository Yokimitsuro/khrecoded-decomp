#include "nitro/types.h"

typedef struct PanelMode {
    void (*update)(void);
    void *enter;
    void *leave;
} PanelMode;

typedef struct PanelState {
    s8 mode;
    s8 result;
    u8 pad_02[6];
    s8 cardDelay;
    u8 pad_09[0x98 - 0x9];
    u8 flags98Low : 4;
    u8 listDirty : 1;
    u8 flags98High : 3;
    u8 flags99Low : 3;
    u8 cardShown : 1;
    u8 cardLocked : 1;
    u8 flags99High : 3;
    u8 layout : 2;
    u8 layoutRest : 6;
    u8 pad_09b[0x2e4 - 0x9b];
    s32 lastCursor;
    s32 lastPhaseCursor;
    u8 pad_2ec[4];
    s8 cursor;
    u8 pad_2f1[0x39c - 0x2f1];
    u8 manager[0x6818 - 0x39c];
    u8 panel[0xcc94 - 0x6818];
    u8 groups[0xd259 - 0xcc94];
    u8 phasePending : 1;
    u8 pad_d259 : 7;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern PanelMode gPanelEntryStateHandler[];
extern void BlinkPanelCursor_02071454(void);
extern void UpdateFloatingPanelSprites(void);
extern void DrawPlayerCardDetails(void);
extern void func_ov013_0207174c(int phase);
extern void func_ov013_02071444(void);
extern void SetGroupSlotsVisible(void *manager, void *groups, int visible);
extern void func_ov013_0206ca70(void);
extern void NNS_FndInitListWithOffset0_0204f130(void *list);

int UpdatePanelScene_0206c7e8(void)
{
    BOOL atTenth = FALSE;
    int cursor;

    data_ov013_02074ce0->lastCursor = data_ov013_02074ce0->cursor;
    gPanelEntryStateHandler[data_ov013_02074ce0->mode].update();
    if (data_ov013_02074ce0->layout != 0) {
        BlinkPanelCursor_02071454();
    }
    UpdateFloatingPanelSprites();
    cursor = data_ov013_02074ce0->cursor;
    if ((cursor + 1) % 10 == 0) {
        atTenth = TRUE;
    }
    if (data_ov013_02074ce0->mode != 6 && data_ov013_02074ce0->mode != 7) {
        if (data_ov013_02074ce0->lastCursor != cursor) {
            data_ov013_02074ce0->cardDelay = 6;
            data_ov013_02074ce0->cardShown = 1;
            DrawPlayerCardDetails();
        }
        if (data_ov013_02074ce0->lastPhaseCursor != data_ov013_02074ce0->cursor && !atTenth &&
            data_ov013_02074ce0->phasePending == 1) {
            func_ov013_0207174c(2);
        }
        if (data_ov013_02074ce0->cardShown) {
            if (!atTenth) {
                if (data_ov013_02074ce0->cardDelay == 0) {
                    if (!data_ov013_02074ce0->cardLocked) {
                        func_ov013_02071444();
                    }
                } else {
                    data_ov013_02074ce0->cardDelay--;
                    if (data_ov013_02074ce0->cardDelay < 0) {
                        data_ov013_02074ce0->cardDelay = 0;
                    }
                }
            } else {
                SetGroupSlotsVisible(data_ov013_02074ce0->manager, data_ov013_02074ce0->groups, FALSE);
                data_ov013_02074ce0->cardShown = 0;
                data_ov013_02074ce0->phasePending = 0;
                data_ov013_02074ce0->lastPhaseCursor = -1;
                func_ov013_0207174c(0);
            }
        }
    }
    func_ov013_0206ca70();
    if (data_ov013_02074ce0->listDirty) {
        NNS_FndInitListWithOffset0_0204f130(data_ov013_02074ce0->manager);
    }
    NNS_FndInitListWithOffset0_0204f130(data_ov013_02074ce0->panel);
    return data_ov013_02074ce0->result;
}
