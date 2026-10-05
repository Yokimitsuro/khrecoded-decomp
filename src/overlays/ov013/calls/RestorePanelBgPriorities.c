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
extern PanelObject *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9640(void *panel, PanelObject *object);
extern void RefreshProgressCaption(void);
extern int DispatchContextCommand(u32 kind, int arg1, int arg2, int arg3);

#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)

void RestorePanelBgPriorities(void)
{
    u8 *panel;
    REG_DB_BG0CNT = (REG_DB_BG0CNT & ~3) | 1;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & ~3) | 3;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & ~3) | 2;
    REG_DB_BG3CNT = REG_DB_BG3CNT & ~3;
    panel = data_ov013_02074ce0->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 5));
    data_ov013_02074ce0->confirmed = 0;
    RefreshProgressCaption();
    DispatchContextCommand(0x80000012, 1, 0, 0);
}
