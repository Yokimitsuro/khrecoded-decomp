#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags_b0 : 5;
    u8 hasTextLayer6 : 1;
    u8 flags_b6 : 2;
    u8 pad_11[0xe4 - 0x11];
    u8 textLayer6[4];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void DestroyFndObjectList(void *list);
extern void InitTextLayerDefault(void *list, int mode, void *font, const u16 *layout);

void CreatePanelTextLayer6(void *font)
{
    u16 layout[8];

    if (data_ov002_0206c460->hasTextLayer6) {
        DestroyFndObjectList(data_ov002_0206c460->textLayer6);
    }
    layout[0] = 0;
    layout[1] = 0;
    layout[2] = 0x20;
    layout[3] = 0x18;
    layout[4] = 1;
    layout[5] = 0xf;
    layout[6] = 0;
    layout[7] = 3;
    InitTextLayerDefault(data_ov002_0206c460->textLayer6, 6, font, layout);
    data_ov002_0206c460->hasTextLayer6 = 1;
}
