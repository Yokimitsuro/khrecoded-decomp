#include "nitro/types.h"

typedef struct {
    u8 pad00;
    u8 confirmed;
    s8 selection;
    s8 cursor;
    u8 pad04[4];
    s32 state;
    u8 pad0c[0x16];
    u8 dirty : 1;
    u8 pad23[0x69c5];
    u8 menu[1];
} SaveMenu;

#define REG_SUB_DISPCNT (*(vu32 *)0x04001000)

extern SaveMenu *data_ov002_0206c464;

extern BOOL IsButtonBPressed(void);
extern void PlaySoundEffect(int bank, int id);
extern void func_ov002_02064f6c(int result);
extern u16 *func_ov002_02062000(void);
extern void DrawMenuLabels(void);
extern void ApplyMenuEntryValues(int flag);
extern void UpdateWidgetRootOnly(void *menu, u16 entry);
extern int FindWidgetById(void *menu, int index);
extern void SetFocusedWidget(void *menu, int handle);
extern void func_ov027_020b9640(void *menu, int handle);
extern void SetEntrySlotsVisible(void *menu, int handle, int visible);

void UpdateQuitMenuState(void)
{
    u8 *menu;

    switch (data_ov002_0206c464->state) {
    case 0:
        if (IsButtonBPressed()) {
            REG_SUB_DISPCNT = (REG_SUB_DISPCNT & ~0x1f00) | 0x1e00;
            DrawMenuLabels();
            menu = data_ov002_0206c464->menu;
            SetEntrySlotsVisible(menu, FindWidgetById(menu, 0xb), 0);
            menu = data_ov002_0206c464->menu;
            SetEntrySlotsVisible(menu, FindWidgetById(menu, 0xc), 0);
            ApplyMenuEntryValues(1);
            SetFocusedWidget(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            func_ov027_020b9640(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            PlaySoundEffect(2, 2);
            func_ov002_02064f6c(1);
            return;
        }
        switch (data_ov002_0206c464->selection) {
        case 0:
            UpdateWidgetRootOnly(data_ov002_0206c464->menu, *func_ov002_02062000());
            break;
        case 1:
            SetFocusedWidget(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, 0xc));
            data_ov002_0206c464->state = 5;
            break;
        case 2:
            SetFocusedWidget(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, 0xb));
            data_ov002_0206c464->state = 5;
            break;
        }
        break;
    case 5:
        data_ov002_0206c464->state = 10;
        break;
    case 10:
        switch (data_ov002_0206c464->selection) {
        case 1:
            SetEntrySlotsVisible(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, 0xb), 0);
            SetEntrySlotsVisible(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, 0xc), 0);
            REG_SUB_DISPCNT = (REG_SUB_DISPCNT & ~0x1f00) | 0x1e00;
            DrawMenuLabels();
            ApplyMenuEntryValues(1);
            SetFocusedWidget(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            func_ov027_020b9640(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            PlaySoundEffect(2, 1);
            func_ov002_02064f6c(1);
            break;
        case 2:
            data_ov002_0206c464->dirty = TRUE;
            data_ov002_0206c464->confirmed = 1;
            SetFocusedWidget(data_ov002_0206c464->menu, FindWidgetById(data_ov002_0206c464->menu, 0xb));
            func_ov002_02064f6c(4);
            PlaySoundEffect(2, 1);
            break;
        }
        break;
    }
}
