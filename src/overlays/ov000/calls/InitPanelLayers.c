#include "nitro/types.h"

typedef struct {
    int offset;
    int size;
} LayerRange;

typedef struct {
    u32 header;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} LayerManagerConfig;

typedef struct {
    u32 sourceIds[4];
} LayerSourceTable;

typedef struct {
    u32 mainVramBase;
    u32 subVramBase;
    u8 pad_08[0x224 - 0x8];
    u8 layerManager[0x6434];
    BOOL layersReady;
    int layerIds[4];
    int overlayLayerId;
    int backLayerId;
} Panel;

extern const LayerSourceTable data_ov000_020637b4;
extern const LayerManagerConfig data_ov000_020637c4;

extern void InitObjManager(void *manager, LayerManagerConfig *config);
extern void PXI_Init_0204f020(void *manager, u32 header);
extern int PXI_Init_0204f0c8(void *manager, u32 source, int enable);
extern void IndexedRecord_SetPair(void *manager, int layerId, LayerRange *range);
extern void IndexedRecord_ClearActive(void *manager, int layerId);
extern void IndexedRecords_SetFlag2(void *manager, int layerId, int flag);
extern void func_0204f18c(void *manager, int layerId, int depth);

void InitPanelLayers(Panel *panel)
{
    LayerSourceTable sources = data_ov000_020637b4;
    LayerManagerConfig config = data_ov000_020637c4;
    LayerRange range;
    int i;

    if (panel->layersReady != 0) {
        return;
    }

    config.header = (((panel->mainVramBase + 0x8000) & 0xfffffc) << 7) | 0x80000002;
    InitObjManager(panel->layerManager, &config);
    PXI_Init_0204f020(panel->layerManager, (((panel->subVramBase + 0x8000) & 0xfffffc) << 7) | 0x80000001);

    range.offset = 0;
    for (i = 0; i < 4; i++) {
        panel->layerIds[i] = PXI_Init_0204f0c8(panel->layerManager, sources.sourceIds[i], 1);
        range.size = i * 0x14000 + 0x68000;
        IndexedRecord_SetPair(panel->layerManager, panel->layerIds[i], &range);
        IndexedRecord_ClearActive(panel->layerManager, panel->layerIds[i]);
        IndexedRecords_SetFlag2(panel->layerManager, panel->layerIds[i], 0);
        func_0204f18c(panel->layerManager, panel->layerIds[i], 0x40);
    }

    panel->backLayerId = PXI_Init_0204f0c8(panel->layerManager, 0, 0);
    range.offset = 0x8000;
    range.size = 0x68000;
    IndexedRecord_SetPair(panel->layerManager, panel->backLayerId, &range);
    IndexedRecords_SetFlag2(panel->layerManager, panel->backLayerId, 0);
    func_0204f18c(panel->layerManager, panel->backLayerId, 0x20);

    panel->overlayLayerId = PXI_Init_0204f0c8(panel->layerManager, 4, 1);
    range.offset = 0x80000;
    range.size = 0xb8000;
    IndexedRecord_SetPair(panel->layerManager, panel->overlayLayerId, &range);
    IndexedRecord_ClearActive(panel->layerManager, panel->overlayLayerId);
    IndexedRecords_SetFlag2(panel->layerManager, panel->overlayLayerId, 0);
    func_0204f18c(panel->layerManager, panel->overlayLayerId, 0x40);

    panel->layersReady = TRUE;
}
