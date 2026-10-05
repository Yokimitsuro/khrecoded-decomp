#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)
#define REG_DB_BG2PA (*(vu32 *)0x04001018)
#define REG_DB_BG2PC (*(vu32 *)0x0400101c)

typedef struct StatusScreen {
    u8 pad00[0x28];
    u32 areaId;
    u8 pad2c[0xdc0 - 0x2c];
    u8 layerA[0x34];
    u8 layerB[0x34];
    u8 layerC[0x34];
    u8 pade5c[0x10e0 - 0xe5c];
    void *sprites;
} StatusScreen;

extern void *func_ov039_020bc1ec(void);
extern void *FindWidgetById(void *root, int id);
extern void SetEntrySlotsVisible(void *menu, void *widget, int visible);
extern void AlarmCallback_0204f140(void *sprites);
extern void ReleaseStatusPage(StatusScreen *screen, void *page);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, int size);
extern void LoadSlotSubBgImage(int a, int b, int c, u16 area);
extern void FlushBufferAndRunCallback(void *layer);
extern u16 *UpdateScreenWidgetLayer(int layer);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void SetScreenLayerDirty(int layer);

void CloseStatusScreen(StatusScreen *screen, void *page)
{
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1000;
    SetEntrySlotsVisible(func_ov039_020bc1ec(), FindWidgetById(func_ov039_020bc1ec(), 0xe), 0);
    SetEntrySlotsVisible(func_ov039_020bc1ec(), FindWidgetById(func_ov039_020bc1ec(), 0x3b), 0);
    AlarmCallback_0204f140(screen->sprites);
    ReleaseStatusPage(screen, page);
    REG_DB_BG0CNT = (REG_DB_BG0CNT & 0x43) | 0x0c00;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & 0x43) | 0x0d00;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & 0x43) | 0x0e00;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & 0x43) | 0x0f00;
    REG_DB_BG0CNT = REG_DB_BG0CNT & ~3;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & ~3) | 1;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & ~3) | 2;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & ~3) | 3;
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);
    LoadSlotSubBgImage(0, 3, 0, screen->areaId);
    FlushBufferAndRunCallback(screen->layerA);
    FlushBufferAndRunCallback(screen->layerB);
    FlushBufferAndRunCallback(screen->layerC);
    FillBackgroundLayerRect(screen->layerA, UpdateScreenWidgetLayer(0x19), 3, 0, 0xf);
    FillBackgroundLayerRect(screen->layerB, UpdateScreenWidgetLayer(0x19), 3, 3, 0xf);
    FillBackgroundLayerRect(screen->layerC, UpdateScreenWidgetLayer(0x19), 0, 0x13, 0xf);
    SetScreenLayerDirty(0x19);
    REG_DB_BG2PA = 0;
    REG_DB_BG2PC = 0;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1e00;
}
