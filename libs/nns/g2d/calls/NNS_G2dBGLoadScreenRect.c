typedef unsigned short u16;
typedef unsigned int u32;

typedef enum NNSG2dScreenFormat {
    NNS_G2D_SCREENFORMAT_TEXT,
    NNS_G2D_SCREENFORMAT_AFFINE,
    NNS_G2D_SCREENFORMAT_AFFINEEXT
} NNSG2dScreenFormat;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

extern void LoadScreenPartText(void *screenDst,
                               const NNSG2dScreenData *screenData,
                               int srcX, int srcY, int dstX, int dstY,
                               int dstW, int dstH, int width, int height);
extern void LoadScreenPartAffine(void *screenDst,
                                 const NNSG2dScreenData *screenData,
                                 int srcX, int srcY, int dstX, int dstY,
                                 int dstW, int width, int height);
extern void LoadScreenPart256x16Pltt(void *screenDst,
                                     const NNSG2dScreenData *screenData,
                                     int srcX, int srcY, int dstX, int dstY,
                                     int dstW, int width, int height);

void NNS_G2dBGLoadScreenRect(void *screenDst,
                             const NNSG2dScreenData *screenData,
                             int srcX, int srcY, int dstX, int dstY,
                             int dstW, int dstH, int width, int height)
{
    if (dstX < 0) {
        const int adjustment = -dstX;
        srcX += adjustment;
        width -= adjustment;
        dstX = 0;
    }
    if (dstY < 0) {
        const int adjustment = -dstY;
        srcY += adjustment;
        height -= adjustment;
        dstY = 0;
    }
    if (dstX + width > dstW) {
        const int adjustment = dstX + width - dstW;
        width -= adjustment;
    }
    if (dstY + height > dstH) {
        const int adjustment = dstY + height - dstH;
        height -= adjustment;
    }
    if (srcX < 0) {
        const int adjustment = -srcX;
        dstX += adjustment;
        width -= adjustment;
        srcX = 0;
    }
    if (srcY < 0) {
        const int adjustment = -srcY;
        dstY += adjustment;
        height -= adjustment;
        srcY = 0;
    }
    if (srcX + width > screenData->screenWidth / 8) {
        const int adjustment = srcX + width - screenData->screenWidth / 8;
        width -= adjustment;
    }
    if (srcY + height > screenData->screenHeight / 8) {
        const int adjustment = srcY + height - screenData->screenHeight / 8;
        height -= adjustment;
    }

    if (width <= 0 || height <= 0) {
        return;
    }

    switch (screenData->screenFormat) {
    case NNS_G2D_SCREENFORMAT_TEXT:
        LoadScreenPartText(screenDst, screenData,
                           srcX, srcY, dstX, dstY,
                           dstW, dstH, width, height);
        break;
    case NNS_G2D_SCREENFORMAT_AFFINE:
        LoadScreenPartAffine(screenDst, screenData,
                             srcX, srcY, dstX, dstY,
                             dstW, width, height);
        break;
    case NNS_G2D_SCREENFORMAT_AFFINEEXT:
        LoadScreenPart256x16Pltt(screenDst, screenData,
                                 srcX, srcY, dstX, dstY,
                                 dstW, width, height);
        break;
    default:
        break;
    }
}
