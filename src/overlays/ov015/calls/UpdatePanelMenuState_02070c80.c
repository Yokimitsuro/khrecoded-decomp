#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
} EntryPos;

typedef struct {
    u8 pad_00[0x94];
    u32 visible : 1;
    u32 active : 1;
} PanelEntry;

typedef struct {
    s8 stateIndex;
    u8 exitReady;
    s8 cursor;
    u8 pad_03[0xdd];
    u8 lowBit : 1;
    u8 confirmPending : 1;
    u8 highBits : 6;
    u8 pad_e1;
    u8 lowBits : 3;
    u8 cancelRequested : 1;
    u8 topBits : 4;
    u8 pad_e3;
    s32 state;
    u8 pad_e8[0x69d8];
    u8 manager[0x6444];
    u16 touchCursor;
} PanelContext;

extern PanelContext *data_ov015_0207e960;

extern void UpdateMenuTouch(void);
extern u16 GetMenuCursorTouch(int arg);
extern BOOL IsButtonBPressed(void);
extern void PlaySoundEffect(int bank, int id);
extern PanelEntry *FindWidgetById(void *manager, int id);
extern void func_ov027_020b9380(void *manager, PanelEntry *entry, EntryPos *pos, int flag);
extern void SetEntrySlotsVisible(void *manager, PanelEntry *entry, int visible);
extern void DrawPanelInfoText(void);
extern u16 *func_ov002_02062000(void);
extern void UpdateWidgetRootOnly(void *manager, u16 entry);
extern void func_ov002_020664f4(int mode);
extern BOOL func_ov002_0206655c(void);
extern u32 DispatchContextCommand(u32 command, u32 value, u32 extra, void *buffer);
extern void StopSeqArcOrDefault(int bank, int seq, int fade);
extern void func_ov002_020620fc(int arg);
extern void func_ov015_02070af8(char nextState);

void UpdatePanelMenuState_02070c80(void)
{
    u8 *manager;
    EntryPos markerPos;
    EntryPos cursorPos;
    s8 prevCursor;
    s32 prevX;

    data_ov015_0207e960->cancelRequested = 0;
    UpdateMenuTouch();
    switch (data_ov015_0207e960->state) {
    case 0:
        data_ov015_0207e960->touchCursor = GetMenuCursorTouch(0);
        data_ov015_0207e960->state = 5;
        break;
    case 5:
        if (IsButtonBPressed()) {
            PlaySoundEffect(2, 4);
            data_ov015_0207e960->state = 10;
            return;
        }
        prevCursor = data_ov015_0207e960->cursor;
        manager = data_ov015_0207e960->manager;
        func_ov027_020b9380(manager, FindWidgetById(manager, 10), &markerPos, 0);
        manager = data_ov015_0207e960->manager;
        func_ov027_020b9380(manager, FindWidgetById(manager, 11), &cursorPos, 0);
        markerPos.x -= 0x19000;
        prevX = cursorPos.x;
        if (markerPos.x == prevX) {
            if (!FindWidgetById(data_ov015_0207e960->manager, 0x13)->active) {
                manager = data_ov015_0207e960->manager;
                SetEntrySlotsVisible(manager, FindWidgetById(manager, 0x13), 1);
                DrawPanelInfoText();
            }
        } else {
            manager = data_ov015_0207e960->manager;
            SetEntrySlotsVisible(manager, FindWidgetById(manager, 0x13), 0);
        }
        UpdateWidgetRootOnly(data_ov015_0207e960->manager, *func_ov002_02062000());
        manager = data_ov015_0207e960->manager;
        func_ov027_020b9380(manager, FindWidgetById(manager, 11), &cursorPos, 0);
        if (data_ov015_0207e960->cursor != prevCursor || prevX == cursorPos.x) {
            DrawPanelInfoText();
        }
        if (data_ov015_0207e960->cancelRequested) {
            PlaySoundEffect(2, 4);
            data_ov015_0207e960->state = 10;
            return;
        }
        if (data_ov015_0207e960->confirmPending) {
            func_ov002_020664f4(3);
            data_ov015_0207e960->confirmPending = 0;
            data_ov015_0207e960->state = 0x32;
        }
        break;
    case 10:
        func_ov002_020664f4(3);
        data_ov015_0207e960->state = 0x14;
        break;
    case 0x14:
        if (func_ov002_0206655c()) {
            if (DispatchContextCommand(5, 0, 0, 0)) {
                StopSeqArcOrDefault(2, 0xd, 4);
            }
            data_ov015_0207e960->exitReady = 1;
        }
        break;
    case 0x32:
        if (func_ov002_0206655c()) {
            func_ov002_020620fc(-1);
            func_ov015_02070af8(2);
        }
        break;
    case 100: /* idle state with no work */
        prevX = 0;
        break;
    }
}
