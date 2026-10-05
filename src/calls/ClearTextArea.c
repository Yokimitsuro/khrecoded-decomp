#include "nitro/types.h"
#include "libs/nns/g2d/include/g2d_charcanvas_internal.h"

typedef struct {
    u8 pad_00[0xc];
    NNSG2dCharCanvas canvas;
} TextPage;

typedef struct {
    u8 pad_00[0x20];
    TextPage *currentPage;
} TextLayer;

void ClearTextArea(TextLayer *obj, int color, int x, int y, int width, int height)
{
    NNSG2dCharCanvas *canvas = &obj->currentPage->canvas;

    canvas->vtable->pClearArea(canvas, color, x, y, width, height);
}
