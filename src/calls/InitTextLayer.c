#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct {
    u8 pad_00[0xc];
    NNSG2dCharCanvas canvas;
} TextPage;

typedef struct {
    NNSG2dFont *font;
    u8 pageList[0xc];
    NNSG2dTextCanvas txn;
    TextPage *currentPage;
    int mode;
    u32 size;
    u16 charBase;
    u16 width;
    u16 height;
    u8 tileBytes;
    u8 layer;
} TextLayer;

typedef union {
    u16 raw;
    struct {
        u16 priority : 2;
        u16 charBase : 4;
        u16 mosaic : 1;
        u16 colorMode : 1;
        u16 screenBase : 5;
        u16 extPalette : 1;
        u16 screenSize : 2;
    } f;
} BgControl;

typedef struct {
    BgControl copy;
    BgControl value;
} BgControlBackup;

static inline void TextCanvasInit(NNSG2dTextCanvas *txn, NNSG2dCharCanvas *canvas, NNSG2dFont *font, int hSpace, int vSpace)
{
    txn->pCanvas = canvas;
    txn->hSpace = hSpace;
    txn->vSpace = vSpace;
    txn->pFont = font;
}

extern void NNS_FndInitList(void *list, u32 value);
extern u16 *CallIndexedHandler(s32 index);
extern void NNS_G2dMapScrToCharText(u16 *dst, int width, int height, int x, int y, int mapW, int tile, int palette);
extern TextPage *func_02001928(TextLayer *layer, int selectAsCurrent, int alignFromEnd);

BOOL InitTextLayer(TextLayer *obj, int layer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame, BOOL fillMap, int alignFromEnd)
{
    BgControlBackup backup0, backup1, backup2, backup3;
    BgControlBackup backup4, backup5, backup6, backup7;
    BgControl saved0, saved1, saved2, saved3;
    BgControl saved4, saved5, saved6, saved7;
    int screenSize;
    int colorMode;
    int mapW;
    TextPage *page;

    obj->font = font;
    obj->layer = (u8)layer;
    NNS_FndInitList(obj->pageList, 0);

    switch (layer) {
    case 0:
        obj->mode = 4;
        saved0.raw = *(volatile u16 *)0x4000008;
        backup0.value = saved0;
        screenSize = backup0.value.f.screenSize;
        backup0.copy = backup0.value;
        colorMode = backup0.copy.f.colorMode;
        break;
    case 1:
        obj->mode = 5;
        saved1.raw = *(volatile u16 *)0x400000a;
        backup1.value = saved1;
        screenSize = backup1.value.f.screenSize;
        backup1.copy = backup1.value;
        colorMode = backup1.copy.f.colorMode;
        break;
    case 2:
        obj->mode = 6;
        saved2.raw = *(volatile u16 *)0x400000c;
        backup2.value = saved2;
        screenSize = backup2.value.f.screenSize;
        backup2.copy = backup2.value;
        colorMode = backup2.copy.f.colorMode;
        break;
    case 3:
        obj->mode = 7;
        saved3.raw = *(volatile u16 *)0x400000e;
        backup3.value = saved3;
        screenSize = backup3.value.f.screenSize;
        backup3.copy = backup3.value;
        colorMode = backup3.copy.f.colorMode;
        break;
    case 4:
        obj->mode = 0x14;
        saved4.raw = *(volatile u16 *)0x4001008;
        backup4.value = saved4;
        screenSize = backup4.value.f.screenSize;
        backup4.copy = backup4.value;
        colorMode = backup4.copy.f.colorMode;
        break;
    case 5:
        obj->mode = 0x15;
        saved5.raw = *(volatile u16 *)0x400100a;
        backup5.value = saved5;
        screenSize = backup5.value.f.screenSize;
        backup5.copy = backup5.value;
        colorMode = backup5.copy.f.colorMode;
        break;
    case 6:
        obj->mode = 0x16;
        saved6.raw = *(volatile u16 *)0x400100c;
        backup6.value = saved6;
        screenSize = backup6.value.f.screenSize;
        backup6.copy = backup6.value;
        colorMode = backup6.copy.f.colorMode;
        break;
    case 7:
        obj->mode = 0x17;
        saved7.raw = *(volatile u16 *)0x400100c;
        backup7.value = saved7;
        screenSize = backup7.value.f.screenSize;
        backup7.copy = backup7.value;
        colorMode = backup7.copy.f.colorMode;
        break;
    }

    obj->charBase = frame->charBase;
    if (screenBase == NULL) {
        screenBase = CallIndexedHandler(layer);
    }
    if (fillMap) {
        if (screenSize == 0 || screenSize == 2) {
            mapW = 0x20;
        } else {
            mapW = 0x40;
        }
        NNS_G2dMapScrToCharText(screenBase, frame->width, frame->height, frame->x, frame->y, mapW, frame->charBase, frame->palette);
    }

    if (colorMode == 0) {
        obj->tileBytes = 0x20;
    } else {
        obj->tileBytes = 0x40;
    }
    obj->width = frame->width;
    obj->height = frame->height;
    obj->size = obj->tileBytes * frame->width * frame->height;

    page = func_02001928(obj, 0, alignFromEnd);
    obj->currentPage = page;
    TextCanvasInit(&obj->txn, &page->canvas, obj->font, frame->hSpace, frame->vSpace);
    return TRUE;
}
