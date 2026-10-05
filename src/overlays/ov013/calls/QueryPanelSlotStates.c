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
    u8 flagsLow : 3;
    u8 confirmed : 1;
    u8 flagsHigh : 4;
    u8 pad_9b[0x258 - 0x9b];
    u8 slotResults[0x2bc - 0x258];
    s32 step;
    u8 pad_2c0[0x2e8 - 0x2c0];
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
extern int DispatchContextCommand(u32 kind, int arg1, int arg2, int arg3);

void QueryPanelSlotStates(void)
{
    int i;
    for (i = 0; i < data_ov013_02074ce0->slotCount; i++) {
        int number = i + 1;
        if (number % 10 != 0) {
            data_ov013_02074ce0->slotResults[i] = DispatchContextCommand(0xb, i - number / 10, 0, 0);
        } else {
            data_ov013_02074ce0->slotResults[i] = DispatchContextCommand(9, number, 0, 0);
        }
    }
}
