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
    s32 floatSpeeds[0x15];
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
    s32 floatSprites[0x15];
    u8 pad_d258;
    u8 scrollStopped : 1;
    u8 scrollFlags : 7;
} PanelState;

extern PanelState *data_ov013_02074ce0;
typedef struct ScreenPos {
    fx32 x;
    fx32 y;
} ScreenPos;

extern void func_ov027_020b9380(void *panel, int sprite, ScreenPos *pos, int arg);
extern void func_ov027_020b91e8(void *panel, int sprite, ScreenPos *pos, int arg);
extern u32 func_0202a9e4(u32 range);

void UpdateFloatingPanelSprites(void)
{
    int i;
    ScreenPos pos;

    for (i = 0; i < 0x15; i++) {
        func_ov027_020b9380(data_ov013_02074ce0->panel, data_ov013_02074ce0->floatSprites[i], &pos, 0);
        if ((pos.y >> 12) < -16) {
            pos.y = 0x120000;
            pos.x = (func_0202a9e4(0x80) + 0x80) << 12;
            data_ov013_02074ce0->floatSpeeds[i] = func_0202a9e4(2) + 1;
            func_ov027_020b91e8(data_ov013_02074ce0->panel, data_ov013_02074ce0->floatSprites[i], &pos, 0);
        } else {
            pos.y = ((pos.y >> 12) - data_ov013_02074ce0->floatSpeeds[i]) << 12;
            func_ov027_020b91e8(data_ov013_02074ce0->panel, data_ov013_02074ce0->floatSprites[i], &pos, 0);
        }
    }
}
