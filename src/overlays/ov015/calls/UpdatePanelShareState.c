#include "nitro/types.h"

typedef struct {
    u8 data[0x70];
} PlayerCardSlot;

typedef struct {
    int ids[3];
} WidgetIdList;

typedef struct {
    u8 pad_00;
    u8 exitReady;
    u8 pad_02[0xb9];
    s8 choice;
    u8 pad_bc[3];
    s8 hostMode;
    u8 pad_c0[0x20];
    u8 flagsLow : 2;
    u8 touchLocked : 1;
    u8 flagsMid : 3;
    u8 widgetsHidden : 1;
    u8 slotsDirty : 1;
    u8 dirtySlots : 3;
    u8 pad_e1_bits : 5;
    u8 lowBits : 3;
    u8 holdRefresh : 1;
    u8 sharingActive : 1;
    u8 highBits : 3;
    u8 pad_e3;
    s32 state;
    u8 pad_e8[4];
    s32 slotIndex;
    u8 pad_f0[0x69d0];
    u8 manager[0x6444];
    u16 touchCursor;
    u8 pad_cf06[0x52];
    PlayerCardSlot slots[3];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern WidgetIdList data_ov015_02079f7c;

extern void UpdateMenuTouch(void);
extern BOOL PlaySoundEffect(int bank, int id);
extern void SlideInPanelWidget(int slot);
extern void func_ov015_0206f688(int slot, int value);
extern u16 *func_ov002_02062000(void);
extern BOOL func_ov002_020632ac(void);
extern BOOL IsButtonBPressed(void);
extern void UpdateWidgetRootOnly(void *manager, u16 entry);
extern u16 GetMenuCursorTouch(int arg);
extern void func_ov015_020716f8(void);
extern int TestContextFlagBit(int slot);
extern void *FindWidgetById(void *manager, int id);
extern BOOL IsWidgetMoveFinished(void *widget);
extern void SelectWidgetAndSlideOut(void *widget);
extern void SetWidgetRootTouchEnabled(void *manager, int enabled);
extern void SetEntrySlotsVisible(void *manager, void *widget, int visible);
extern void HidePanelOptionSlots(void);
extern BOOL AreAllWidgetMovesFinished(void *manager);
extern void func_ov015_02070af8(int mode);
extern void func_ov002_020664f4(int frames);
extern void func_ov015_02072cb4(void);
extern BOOL func_ov002_0206655c(void);
extern void func_ov015_0206fa98(void);
extern void UpdatePlayerCounter(void);
extern u32 DispatchContextCommand(u32 command, void *value, u32 extra, void *buffer);
extern void FreePanelBuffers(void);
extern void StopSeqArcOrDefault(int bank, int seq, int fade);
extern void ClearBusyFlag(void);

void UpdatePanelShareState(void)
{
    WidgetIdList ids;
    u8 *manager;
    void *widget;
    int slot;

    UpdateMenuTouch();
    data_ov015_0207e960->holdRefresh = 0;
    if (data_ov015_0207e960->slotsDirty) {
        PlaySoundEffect(2, 7);
        if (data_ov015_0207e960->dirtySlots & 1) {
            SlideInPanelWidget(0);
            func_ov015_0206f688(0, 0);
        }
        if (data_ov015_0207e960->dirtySlots & 2) {
            SlideInPanelWidget(1);
            func_ov015_0206f688(1, 0);
        }
        if (data_ov015_0207e960->dirtySlots & 4) {
            SlideInPanelWidget(2);
            func_ov015_0206f688(2, 0);
        }
        data_ov015_0207e960->dirtySlots = 0;
        data_ov015_0207e960->slotsDirty = 0;
    }
    if (data_ov015_0207e960->state == 10) {
        UpdateWidgetRootOnly(data_ov015_0207e960->manager, *func_ov002_02062000());
    } else if (!func_ov002_020632ac() && !IsButtonBPressed() && data_ov015_0207e960->state < 100) {
        UpdateWidgetRootOnly(data_ov015_0207e960->manager, 0);
    }
    switch (data_ov015_0207e960->state) {
    case 0:
        data_ov015_0207e960->touchCursor = GetMenuCursorTouch(0);
        data_ov015_0207e960->state = 5;
        break;
    case 5:
        if (IsButtonBPressed() || data_ov015_0207e960->holdRefresh) {
            func_ov015_020716f8();
            data_ov015_0207e960->touchLocked = 1;
            data_ov015_0207e960->state = 10;
            return;
        }
        if (func_ov002_020632ac()) {
            ids = data_ov015_02079f7c;
            slot = -1;
            if (TestContextFlagBit(0) == 1) {
                slot = 0;
            } else if (TestContextFlagBit(1) == 1) {
                slot = 1;
            } else if (TestContextFlagBit(2) == 1) {
                slot = 2;
            }
            if (slot != -1) {
                widget = FindWidgetById(data_ov015_0207e960->manager, ids.ids[slot]);
                if (IsWidgetMoveFinished(widget)) {
                    PlaySoundEffect(2, 1);
                    SelectWidgetAndSlideOut(widget);
                }
            }
        }
        if (data_ov015_0207e960->widgetsHidden) {
            SetWidgetRootTouchEnabled(data_ov015_0207e960->manager, 0);
            manager = data_ov015_0207e960->manager;
            SetEntrySlotsVisible(manager, FindWidgetById(manager, 10), 0);
            manager = data_ov015_0207e960->manager;
            SetEntrySlotsVisible(manager, FindWidgetById(manager, 11), 0);
            manager = data_ov015_0207e960->manager;
            SetEntrySlotsVisible(manager, FindWidgetById(manager, 12), 0);
            data_ov015_0207e960->touchLocked = 1;
            data_ov015_0207e960->state = 0x14;
        }
        break;
    case 10:
        if (IsButtonBPressed()) {
            PlaySoundEffect(2, 2);
            data_ov015_0207e960->choice = 2;
        }
        if (data_ov015_0207e960->choice != 0) {
            data_ov015_0207e960->state = 11;
        }
        break;
    case 11:
        data_ov015_0207e960->state = 12;
        break;
    case 12:
        if (data_ov015_0207e960->choice != 0) {
            HidePanelOptionSlots();
            if (data_ov015_0207e960->choice == 1) {
                data_ov015_0207e960->state = 100;
                return;
            }
            data_ov015_0207e960->touchLocked = 0;
            SetWidgetRootTouchEnabled(data_ov015_0207e960->manager, 1);
            data_ov015_0207e960->state = 0;
        }
        break;
    case 15:
        if (AreAllWidgetMovesFinished(data_ov015_0207e960->manager)) {
            data_ov015_0207e960->state = 0x14;
        }
        break;
    case 0x14:
        data_ov015_0207e960->touchLocked = 1;
        data_ov015_0207e960->state = 0x1e;
        break;
    case 0x1e:
        data_ov015_0207e960->state = 0x28;
        break;
    case 0x28:
        func_ov015_02070af8(6);
        break;
    case 100:
        func_ov002_020664f4(3);
        data_ov015_0207e960->touchLocked = 1;
        func_ov015_02072cb4();
        data_ov015_0207e960->state = 0x6e;
        break;
    case 0x6e:
        if (data_ov015_0207e960->hostMode == 1 && func_ov002_0206655c()) {
            for (slot = 0; slot < 3; slot++) {
                data_ov015_0207e960->slotIndex = slot;
                if (TestContextFlagBit(slot)) {
                    func_ov015_0206fa98();
                    UpdatePlayerCounter();
                    DispatchContextCommand(0x80000001, &data_ov015_0207e960->slots[slot], 0, 0);
                }
            }
            FreePanelBuffers();
            data_ov015_0207e960->sharingActive = 0;
            if (DispatchContextCommand(5, 0, 0, 0)) {
                StopSeqArcOrDefault(2, 0xd, 4);
            }
            ClearBusyFlag();
            data_ov015_0207e960->exitReady = 2;
            data_ov015_0207e960->state = 0x96;
        }
        break;
    }
}
