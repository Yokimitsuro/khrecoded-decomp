typedef unsigned char u8;

struct NNSG2dCharCanvas;
struct NNSG2dFont;
struct NNSG2dGlyph;

typedef void (*NNSiG2dDrawGlyphFunc)(const struct NNSG2dCharCanvas *pCC,
                                     const struct NNSG2dFont *pFont,
                                     int x, int y, int cl,
                                     const struct NNSG2dGlyph *pGlyph);
typedef void (*NNSiG2dClearFunc)(const struct NNSG2dCharCanvas *pCC, int cl);
typedef void (*NNSiG2dClearAreaFunc)(const struct NNSG2dCharCanvas *pCC,
                                     int cl, int x, int y, int w, int h);

typedef struct NNSiG2dCharCanvasVTable {
    NNSiG2dDrawGlyphFunc pDrawGlyph;
    NNSiG2dClearFunc pClear;
    NNSiG2dClearAreaFunc pClearArea;
} NNSiG2dCharCanvasVTable;

typedef struct ObjectSize {
    u8 widthShift;
    u8 heightShift;
} ObjectSize;

extern void DrawGlyphLine(const struct NNSG2dCharCanvas *pCC,
                          const struct NNSG2dFont *pFont,
                          int x, int y, int cl,
                          const struct NNSG2dGlyph *pGlyph);
extern void DrawGlyph1D(const struct NNSG2dCharCanvas *pCC,
                        const struct NNSG2dFont *pFont,
                        int x, int y, int cl,
                        const struct NNSG2dGlyph *pGlyph);
extern void ClearContinuous(const struct NNSG2dCharCanvas *pCC, int cl);
extern void ClearAreaLine(const struct NNSG2dCharCanvas *pCC,
                          int cl, int x, int y, int w, int h);
extern void ClearArea1D(const struct NNSG2dCharCanvas *pCC,
                        int cl, int x, int y, int w, int h);

const NNSiG2dCharCanvasVTable VTABLE_BG = {
    DrawGlyphLine,
    ClearContinuous,
    ClearAreaLine
};

const NNSiG2dCharCanvasVTable VTABLE_OBJ1D = {
    DrawGlyph1D,
    ClearContinuous,
    ClearArea1D
};

const ObjectSize sMaxObjectSizeTable[4][4] = {
    { {0, 0}, {1, 0}, {2, 0}, {2, 0} },
    { {0, 1}, {1, 1}, {2, 1}, {2, 1} },
    { {0, 2}, {1, 2}, {2, 2}, {3, 2} },
    { {0, 2}, {1, 2}, {2, 3}, {3, 3} }
};
