#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelObject {
    u8 pad_00[0xc];
    s32 value;
} PanelObject;

typedef struct PanelState {
    u8 pad_00;
    u8 finished;
    s8 slotCount;
    s8 resultMode;
    u8 pad_04[0x99 - 0x4];
    u8 drawFlags;
    u8 flagsLow : 2;
    u8 soundPlayed : 1;
    u8 confirmed : 1;
    u8 flagsHigh : 4;
    u8 pad_9b[0x258 - 0x9b];
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
    u8 pad_cc98[0xd259 - 0xcc98];
    u8 scrollStopped : 1;
    u8 scrollFlags : 7;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern PanelObject *FindWidgetById(void *panel, int id);
extern void ApplySelectedSubitemValues(void *panel, PanelObject *object, s32 useAlt);
extern int DispatchContextCommand(u32 kind, int arg1, int arg2, int arg3);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ResetPanelStepAndNotify(void)
{
    u8 *panel;
    data_ov013_02074ce0->step = 0;
    data_ov013_02074ce0->stepTimer = 0;
    data_ov013_02074ce0->stepValue = 0;
    panel = data_ov013_02074ce0->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 5), 1);
    if (DispatchContextCommand(5, 0, 0, 0) == 0) {
        return;
    }
    if (data_ov013_02074ce0->soundPlayed) {
        return;
    }
    if ((data_ov013_02074ce0->clearCount + 1) % 10 == 0) {
        return;
    }
    PlaySoundEffect(2, 0xd);
    data_ov013_02074ce0->soundPlayed = 1;
}
