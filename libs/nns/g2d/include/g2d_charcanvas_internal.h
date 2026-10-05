#ifndef NNS_G2D_CHARCANVAS_INTERNAL_H
#define NNS_G2D_CHARCANVAS_INTERNAL_H

#include "nitro/types.h"

typedef struct NNSG2dFont NNSG2dFont;
typedef struct NNSG2dGlyph NNSG2dGlyph;
typedef struct NNSG2dCharCanvas NNSG2dCharCanvas;

typedef void (*NNSiG2dDrawGlyphFunc)(const NNSG2dCharCanvas *canvas,
                                     const NNSG2dFont *font, int x, int y,
                                     int color, const NNSG2dGlyph *glyph);
typedef void (*NNSiG2dClearFunc)(const NNSG2dCharCanvas *canvas, int color);
typedef void (*NNSiG2dClearAreaFunc)(const NNSG2dCharCanvas *canvas, int color,
                                    int x, int y, int width, int height);

typedef struct NNSiG2dCharCanvasVTable {
    NNSiG2dDrawGlyphFunc pDrawGlyph;
    NNSiG2dClearFunc pClear;
    NNSiG2dClearAreaFunc pClearArea;
} NNSiG2dCharCanvasVTable;

struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const NNSiG2dCharCanvasVTable *vtable;
};

#endif
