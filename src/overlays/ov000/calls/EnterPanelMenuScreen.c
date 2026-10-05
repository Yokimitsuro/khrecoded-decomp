#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    u32 unk_58;
    u8 pad_5c[0x224 - 0x5c];
    u8 layerManager[0x6434];
    BOOL layersReady;
    int layerIds[4];
    int overlayLayerId;
    u8 pad_6670[0x66d0 - 0x6670];
    u64 startTick;
} Panel;

extern void InitPanelLayers(Panel *panel);
extern void InitPanelScene(Panel *panel);
extern BOOL IsPanelFlagSet(Panel *panel, int bit);
extern void IndexedRecords_SetFlag2(void *manager, int layerId, int flag);
extern void ShowPanelBgScreen(Panel *panel, int screenIndex);
extern BOOL IsSoundStreamActive(int handleIndex);
extern BOOL PrepareAndStartStream(int handleIndex, u16 streamId);
extern u64 OS_GetTick(void);

void EnterPanelMenuScreen(Panel *panel)
{
    int i;

    InitPanelLayers(panel);
    InitPanelScene(panel);
    for (i = 0; i < 4; i++) {
        IndexedRecords_SetFlag2(panel->layerManager, panel->layerIds[i], IsPanelFlagSet(panel, i));
    }
    IndexedRecords_SetFlag2(panel->layerManager, panel->overlayLayerId, 1);
    ShowPanelBgScreen(panel, 4);
    if (!IsSoundStreamActive(0)) {
        PrepareAndStartStream(0, 0);
    }
    panel->unk_58 = 0;
    panel->startTick = OS_GetTick();
}
