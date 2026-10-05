#include "nitro/types.h"

typedef struct PanelObject {
    u8 pad_00[0xc];
    s32 value;
} PanelObject;

typedef struct PanelState {
    u8 pad_00;
    u8 finished;
    u8 pad_02;
    s8 resultMode;
    u8 pad_04[0x99 - 0x4];
    u8 drawFlags;
    u8 flagsLow : 3;
    u8 confirmed : 1;
    u8 flagsHigh : 4;
    u8 pad_9b[0x2bc - 0x9b];
    s32 step;
    u8 pad_2c0[0x2e8 - 0x2c0];
    s32 selection;
    s8 dirty;
    u8 pad_2ed[3];
    s8 clearCount;
    u8 pad_2f1[0x39c - 0x2f1];
    u8 list[0x6818 - 0x39c];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void RefreshProgressCaption(void);
extern PanelObject *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9640(void *panel, PanelObject *object);
extern int DispatchContextCommand(u32 kind, int arg1, int arg2, int arg3);

void CancelPanelConfirm(void)
{
    data_ov013_02074ce0->confirmed = 0;
    if (data_ov013_02074ce0->dirty != 0) {
        u8 *panel;
        RefreshProgressCaption();
        panel = data_ov013_02074ce0->panel;
        func_ov027_020b9640(panel, FindWidgetById(panel, 5));
        data_ov013_02074ce0->drawFlags |= 8;
    }
    DispatchContextCommand(0x80000009, 0, 0, 0);
    data_ov013_02074ce0->selection = -1;
}
