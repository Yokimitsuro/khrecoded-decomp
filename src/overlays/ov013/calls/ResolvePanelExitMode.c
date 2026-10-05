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
typedef struct SessionInfo {
    u32 unk_00;
    u16 checksum;
    u16 exitMode : 3;
    u16 exitBit3 : 1;
    u16 retry : 1;
    u16 exitRest : 11;
    u8 pad_08[8];
    s8 base;
    s8 offset;
    s8 slot;
} SessionInfo;

extern SessionInfo data_0206085c;
extern void func_ov002_0206203c(int value);
extern void func_ov002_020620fc(int value);
extern void func_ov013_0206fc74(void);
extern void func_ov013_0206fbbc(void);
extern void RefreshProgressCaption(void);
extern BOOL IsPanelBusy(void);
extern void func_ov013_0206e574(void);
extern void func_ov013_0206eb18(void);
extern void RecordPanelClear(int day);

void ResolvePanelExitMode(void)
{
    func_ov002_0206203c(-1);
    func_ov002_020620fc(-1);
    func_ov013_0206fc74();
    func_ov013_0206fbbc();
    RefreshProgressCaption();
    if (IsPanelBusy()) {
        func_ov013_0206e574();
        data_ov013_02074ce0->step = 0;
        return;
    }
    switch (data_0206085c.exitMode) {
    case 2:
        func_ov013_0206e574();
        data_ov013_02074ce0->step = 0;
        break;
    case 4:
        RecordPanelClear(data_0206085c.offset + data_0206085c.base);
        func_ov013_0206e574();
        data_ov013_02074ce0->step = 0;
        break;
    case 0:
        if (data_0206085c.retry) {
            data_ov013_02074ce0->step = 0x3c;
            return;
        }
        func_ov013_0206e574();
        data_ov013_02074ce0->step = 0;
        break;
    case 1:
        if (data_0206085c.slot == 7) {
            data_ov013_02074ce0->step = 0x3c;
            return;
        }
        func_ov013_0206eb18();
        data_ov013_02074ce0->step = 0x32;
        break;
    case 3:
        data_ov013_02074ce0->step = 0x46;
        break;
    }
}
