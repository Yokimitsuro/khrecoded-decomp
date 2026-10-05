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
extern void UpdateWidgetRootOnly(void *panel, int index);
extern BOOL AreAllWidgetMovesFinished(void *panel);
extern int DispatchContextCommand(u32 kind, int arg1, int arg2, int arg3);
extern void func_ov013_0206fc74(void);

BOOL LoadPanelSlotCount(void)
{
    s8 count;
    s8 separators;
    UpdateWidgetRootOnly(data_ov013_02074ce0->panel, 0);
    if (!AreAllWidgetMovesFinished(data_ov013_02074ce0->panel)) {
        return FALSE;
    }
    data_ov013_02074ce0->slotCount = DispatchContextCommand(1, 0, 0, 0);
    count = data_ov013_02074ce0->slotCount;
    separators = (count + (count + 1) / 10 + 1) / 10;
    data_ov013_02074ce0->slotCount = count + separators;
    func_ov013_0206fc74();
    return TRUE;
}
