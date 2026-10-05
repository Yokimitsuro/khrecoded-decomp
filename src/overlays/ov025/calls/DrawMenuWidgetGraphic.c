#include "nitro/types.h"

typedef struct ScreenGraphic {
    u8 pad_00[8];
    void *screenData;
} ScreenGraphic;

typedef struct MenuWidget {
    u16 unk_0;
    s16 dstX;
    s16 dstY;
    u16 srcX;
    u16 srcY;
    u8 pad_0a[6];
    int type;
    u8 pad_14[4];
    ScreenGraphic *graphic;
} MenuWidget;

extern u32 data_ov025_020b7780;
extern void *G2S_GetBG1ScrPtr(void);
extern void NNS_G2dBGLoadScreenRect(void *screenDst, void *screenData, int srcX, int srcY, int dstX, int dstY,
                                             int dstW, int dstH, int width, int height);
extern void func_ov027_020b9a94(u32 owner, MenuWidget *widget);

void DrawMenuWidgetGraphic(MenuWidget *widget)
{
    switch (widget->type) {
    case 0x19:
        NNS_G2dBGLoadScreenRect(G2S_GetBG1ScrPtr(), widget->graphic->screenData, widget->srcX,
                                         widget->srcY, widget->dstX, widget->dstY, 32, 32, 32, 32);
        break;
    case 0x1a:
    case 0x1b:
        func_ov027_020b9a94(data_ov025_020b7780 + 0x64c8, widget);
        break;
    }
}
