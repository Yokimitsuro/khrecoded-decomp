#include "nitro/types.h"

typedef struct {
    u8 pad00[2];
    s8 selection;
    u8 pad03[5];
    s32 state;
    u8 pad0c[0x69dc];
    u8 menu[1];
} SaveMenu;

extern SaveMenu *data_ov002_0206c464;
extern u8 *data_0205fe0c;

extern BOOL IsButtonBPressed(void);
extern BOOL func_ov002_020632ac(void);
extern void PlaySoundEffect(int bank, int id);
extern void func_ov002_02064f6c(int result);
extern u16 *func_ov002_02062000(void);
extern void UpdateWidgetRootOnly(void *menu, u16 entry);
extern int FindWidgetById(void *menu, int index);
extern void SetFocusedWidget(void *menu, int handle);
extern void SetEntrySlotsVisible(void *menu, int handle, int visible);
extern void func_ov027_020b90b8(void *menu, int flag);
extern void ShowSaveMessage(int mode);
extern int InvokeCallback(u32 slot);
extern void IncrementBusyCounter(void);
extern void DecrementBusyCounterIfPositive(void);
extern int PollCardThreadState(void);
extern void SetCardThreadStartTick(void);
extern void func_ov002_02066c44(void);
extern void UpdateMenuTouch(void);
extern int GetMenuCursorHeld(int arg);
extern void func_ov002_020620fc(int arg);

void UpdateSaveMenuState(void)
{
    u8 *menu;

    switch (data_ov002_0206c464->state) {
    case 0:
        if (IsButtonBPressed()) {
            PlaySoundEffect(2, 2);
            func_ov002_02064f6c(1);
            return;
        }
        switch (data_ov002_0206c464->selection) {
        case 0:
            UpdateWidgetRootOnly(data_ov002_0206c464->menu, *func_ov002_02062000());
            break;
        case 1:
            PlaySoundEffect(2, 1);
            SetFocusedWidget(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, 0xc));
            data_ov002_0206c464->state = 1;
            break;
        case 2:
            PlaySoundEffect(2, 1);
            SetFocusedWidget(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, 0xb));
            data_ov002_0206c464->state = 1;
            break;
        }
        break;
    case 1:
        data_ov002_0206c464->state = 3;
        break;
    case 3:
        switch (data_ov002_0206c464->selection) {
        case 1:
            func_ov002_02064f6c(1);
            break;
        case 2:
            data_ov002_0206c464->state = 5;
            break;
        }
        break;
    case 5:
        ShowSaveMessage(0);
        menu = data_ov002_0206c464->menu;
        SetEntrySlotsVisible(menu, FindWidgetById(menu, 0xb), 0);
        menu = data_ov002_0206c464->menu;
        SetEntrySlotsVisible(menu, FindWidgetById(menu, 0xc), 0);
        func_ov027_020b90b8(data_ov002_0206c464->menu, 0);
        if (InvokeCallback((*(u32 *)(data_0205fe0c + 0x28c4) & 0x30000000) >> 28) == 0) {
            data_ov002_0206c464->state = 20;
            return;
        }
        IncrementBusyCounter();
        data_ov002_0206c464->state = 10;
        break;
    case 10:
        switch (PollCardThreadState()) {
        case 0:
            DecrementBusyCounterIfPositive();
            SetCardThreadStartTick();
            func_ov002_02066c44();
            ShowSaveMessage(4);
            PlaySoundEffect(2, 1);
            data_ov002_0206c464->state = 50;
            break;
        case 1:
            break;
        default:
            data_ov002_0206c464->state = 20;
            break;
        }
        break;
    case 20:
        ShowSaveMessage(2);
        DecrementBusyCounterIfPositive();
        data_ov002_0206c464->state = 100;
        break;
    case 100:
        break;
    case 50:
        UpdateMenuTouch();
        if (func_ov002_020632ac() || IsButtonBPressed() || GetMenuCursorHeld(0)) {
            func_ov002_020620fc(0);
            PlaySoundEffect(2, 2);
            func_ov002_02064f6c(1);
        }
        break;
    }
}
