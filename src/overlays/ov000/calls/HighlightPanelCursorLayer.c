#include "nitro/types.h"

typedef struct LayerRange {
    int offset;
    int size;
} LayerRange;

typedef struct Panel {
    u8 pad_00[0x50];
    s32 cursorIndex;
    u8 pad_54[0x224 - 0x54];
    u8 layerManager[0x6434];
    BOOL layersReady;
    int layerIds[4];
    int overlayLayerId;
    int backLayerId;
} Panel;

extern const LayerRange data_ov000_0206379c;

extern void IndexedRecord_SetPair(void *manager, int layerId, LayerRange *range);
extern void IndexedRecords_SetFlag2(void *manager, int layerId, int flag);
extern void func_0204f218(void *manager, int layerId, u16 visible);

void HighlightPanelCursorLayer(Panel *panel)
{
    LayerRange range = data_ov000_0206379c;
    int i;

    range.size = panel->cursorIndex * 0x14000 + 0x68000;
    IndexedRecord_SetPair(panel->layerManager, panel->backLayerId, &range);
    IndexedRecords_SetFlag2(panel->layerManager, panel->backLayerId, 1);

    for (i = 0; i < 4; i++) {
        func_0204f218(panel->layerManager, panel->layerIds[i], i == panel->cursorIndex);
    }
}
