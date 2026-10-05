#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags_b0 : 4;
    u8 hasTextLayer : 1;
    u8 flags_b5 : 3;
    u8 pad_11[0xb0 - 0x11];
    u8 textLayer[4];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void DestroyFndObjectList(void *list);
extern void InitTextLayerDefault(void *list, int mode, void *font, const u16 *layout);

void CreatePanelTextLayer(void *font)
{
    u16 layout[8];

    if (data_ov002_0206c460->hasTextLayer) {
        DestroyFndObjectList(data_ov002_0206c460->textLayer);
    }
    layout[0] = 1;
    layout[1] = 0;
    layout[2] = 0x1f;
    layout[3] = 0xf;
    layout[4] = 1;
    layout[5] = 0xf;
    layout[6] = 0;
    layout[7] = 3;
    InitTextLayerDefault(data_ov002_0206c460->textLayer, 7, font, layout);
    data_ov002_0206c460->hasTextLayer = 1;
}
