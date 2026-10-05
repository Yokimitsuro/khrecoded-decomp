#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelObject {
    u8 pad_00[0xc];
    s32 value;
} PanelObject;

typedef struct PanelColor {
    u16 red : 5;
    u16 green : 5;
    u16 blue : 5;
    u16 unused : 1;
} PanelColor;

typedef struct PanelState {
    u8 pad_00;
    u8 finished;
    s8 slotCount;
    s8 resultMode;
    u8 pad_04[6];
    PanelColor limitColor;
    PanelColor color;
    u8 pad_0e[0x98 - 0xe];
    u8 pad98Bits : 7;
    u8 brightening : 1;
    u8 drawFlags;
    u8 flagsLow : 2;
    u8 soundPlayed : 1;
    u8 confirmed : 1;
    u8 flagsHigh : 4;
    u8 pad_9b[0x204 - 0x9b];
    s32 fallSpeeds[0x15];
    u8 slotResults[0x2bc - 0x258];
    s32 step;
    s32 stepTimer;
    s32 stepValue;
    u8 pad_2c8[0x2e8 - 0x2c8];
    s32 selection;
    s8 dirty;
    u8 pad_2ed[3];
    s8 clearCount;
    u8 pad_2f1[0x39c - 0x2f1];
    u8 list[0x6818 - 0x39c];
    u8 panel[0xcc94 - 0x6818];
    fx32 scroll;
    u8 pad_cc98[0xd204 - 0xcc98];
    s32 fallSprites[0x15];
    u8 pad_d258;
    u8 scrollStopped : 1;
    u8 scrollFlags : 7;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void UpdateMenuTouch(void);
extern BOOL func_ov002_020632ac(void);
extern BOOL IsButtonBPressed(void);
extern BOOL GetMenuCursorHeld(int index);
extern BOOL GetMenuCursorTouch(int index);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov002_020620fc(int value);
extern void func_ov013_02070aa0(void);
extern void RefreshProgressCaption(void);
extern PanelObject *FindWidgetById(void *panel, int id);
extern void SetEntrySlotsVisible(void *panel, PanelObject *object, BOOL visible);
extern void func_ov027_020b9640(void *panel, PanelObject *object);
extern void func_ov013_020716e4(int mode);

void UpdatePanelDismissPrompt(void)
{
    u8 *panel;
    UpdateMenuTouch();
    switch (data_ov013_02074ce0->step) {
    case 0:
        data_ov013_02074ce0->step = 5;
        break;
    case 5:
        if (func_ov002_020632ac() || IsButtonBPressed() || GetMenuCursorHeld(0)) {
            if (func_ov002_020632ac() || GetMenuCursorTouch(0)) {
                PlaySoundEffect(2, 1);
            } else if (IsButtonBPressed()) {
                PlaySoundEffect(2, 2);
            }
            data_ov013_02074ce0->step = 10;
        }
        break;
    case 10:
        func_ov002_020620fc(1);
        func_ov013_02070aa0();
        RefreshProgressCaption();
        panel = data_ov013_02074ce0->panel;
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 4), FALSE);
        panel = data_ov013_02074ce0->panel;
        func_ov027_020b9640(panel, FindWidgetById(panel, 0));
        func_ov013_020716e4(1);
        break;
    }
}
