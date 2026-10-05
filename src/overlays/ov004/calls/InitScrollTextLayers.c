#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u8 opaque[0x34];
} TextLayer;

typedef struct {
    TextLayer textLayer;
    TextLayer markerLayer;
    u16 textScreen[0x400];
    u16 markerScreen[0x400];
    u8 pad_1068[0x10940 - 0x1068];
} ScrollPanel;

typedef struct {
    u8 pad_00[0x30];
    ScrollPanel panels[2];
    u8 pad_212b0[0x23a94 - 0x212b0];
    NNSG2dFont mainFont;
    void *mainFontFile;
    NNSG2dFont subFont;
    void *subFontFile;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;

extern void NNS_G2dFontInitUTF16(NNSG2dFont *font, void *fontFile);
extern void InitScrollTextLayer(TextLayer *layer, int columns, u16 *screen, int bgSlot);

void InitScrollTextLayers(void)
{
    NNS_G2dFontInitUTF16(&data_ov004_020645a0.work->mainFont, data_ov004_020645a0.work->mainFontFile);
    NNS_G2dFontInitUTF16(&data_ov004_020645a0.work->subFont, data_ov004_020645a0.work->subFontFile);
    InitScrollTextLayer(&data_ov004_020645a0.work->panels[0].textLayer, 0x20, data_ov004_020645a0.work->panels[0].textScreen, 5);
    InitScrollTextLayer(&data_ov004_020645a0.work->panels[0].markerLayer, 3, data_ov004_020645a0.work->panels[0].markerScreen, 5);
    InitScrollTextLayer(&data_ov004_020645a0.work->panels[1].textLayer, 0x20, data_ov004_020645a0.work->panels[1].textScreen, 0x15);
    InitScrollTextLayer(&data_ov004_020645a0.work->panels[1].markerLayer, 3, data_ov004_020645a0.work->panels[1].markerScreen, 0x15);
}
