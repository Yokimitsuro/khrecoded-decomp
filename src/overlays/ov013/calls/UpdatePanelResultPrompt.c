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
extern BOOL IsButtonBPressed(void);
extern u16 *func_ov002_02062000(void);
extern void UpdateWidgetRootOnly(void *panel, int index);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void RefreshProgressCaption(void);
extern void func_ov013_020716e4(int mode);

void UpdatePanelResultPrompt(void)
{
    PanelState *state = data_ov013_02074ce0;
    switch (state->step) {
    case 0:
        if (IsButtonBPressed()) {
            PlaySoundEffect(2, 2);
            data_ov013_02074ce0->confirmed = 0;
            RefreshProgressCaption();
            func_ov013_020716e4(1);
            return;
        }
        UpdateWidgetRootOnly(data_ov013_02074ce0->panel, *func_ov002_02062000());
        if (data_ov013_02074ce0->resultMode == 1 || data_ov013_02074ce0->resultMode == 2) {
            data_ov013_02074ce0->step = 5;
        }
        break;
    case 5:
        state->step = 10;
        break;
    case 10:
        if (state->resultMode == 1) {
            state->resultMode = 0;
            data_ov013_02074ce0->step = 100;
            func_ov013_020716e4(3);
        } else if (state->resultMode == 2) {
            state->confirmed = 0;
            RefreshProgressCaption();
            func_ov013_020716e4(1);
        }
        break;
    }
}
