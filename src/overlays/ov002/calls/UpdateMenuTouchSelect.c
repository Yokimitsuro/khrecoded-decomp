#include "nitro/types.h"

typedef struct MenuContext {
    s8 state;
    u8 confirmed;
    u8 pad_02[6];
    int phase;
    u8 pad_0C[0x16];
    u8 unk_22_0 : 4;
    u8 pendingSelect : 1;
    u8 unk_22_5 : 3;
    u8 pad_23[0x69e8 - 0x23];
    u8 panel[0xce2c - 0x69e8];
    u16 touchCursor;
} MenuContext;

extern MenuContext *data_ov002_0206c464;

extern void UpdateMenuTouch(void);
extern u16 GetMenuCursorTouch(int mode);
extern BOOL IsButtonBPressed(void);
extern BOOL func_ov002_02066c58(void);
extern void func_ov002_02064f6c(int nextState);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern u16 *func_ov002_02062000(void);
extern void UpdateWidgetRootOnly(void *panel, u16 value);

void UpdateMenuTouchSelect(void)
{
    UpdateMenuTouch();
    switch (data_ov002_0206c464->phase) {
    case 0:
        data_ov002_0206c464->touchCursor = GetMenuCursorTouch(0);
        data_ov002_0206c464->phase = 5;
        break;
    case 5:
        if (IsButtonBPressed() || data_ov002_0206c464->pendingSelect) {
            data_ov002_0206c464->pendingSelect = 0;
            if (func_ov002_02066c58()) {
                func_ov002_02064f6c(3);
                return;
            }
            PlaySoundEffect(2, 4);
            data_ov002_0206c464->confirmed = 1;
            func_ov002_02064f6c(4);
            return;
        }
        UpdateWidgetRootOnly(data_ov002_0206c464->panel, *func_ov002_02062000());
        break;
    }
}
