typedef unsigned char u8;
typedef unsigned int u32;

typedef enum NNSG2dCharaColorMode {
    NNS_G2D_CHARA_COLORMODE_16 = 4,
    NNS_G2D_CHARA_COLORMODE_256 = 8
} NNSG2dCharaColorMode;

typedef struct NNSiG2dCharCanvasVTable NNSiG2dCharCanvasVTable;
typedef struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const NNSiG2dCharCanvasVTable *vtable;
} NNSG2dCharCanvas;

void InitCharCanvas(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight,
                    NNSG2dCharaColorMode colorMode, const NNSiG2dCharCanvasVTable *vtable, u32 param)
{
    pCC->areaWidth = areaWidth;
    pCC->areaHeight = areaHeight;
    pCC->dstBpp = colorMode;
    pCC->charBase = charBase;
    pCC->vtable = vtable;
    pCC->param = param;
}
