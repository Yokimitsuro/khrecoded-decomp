#include "nitro/types.h"

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef struct PanelPageState {
    u8 pad_00[8];
    void *srcDataDefault;
    void *srcDataPage2;
    u8 pad_10[0x4c];
    NNSG2dScreenData *screenData;
} PanelPageState;

extern void *gPanelState;
extern void NNS_G2dBGLoadScreenRect(void *pScreenDst, const NNSG2dScreenData *pScreenData,
                                              int srcX, int srcY, int dstX, int dstY,
                                              int dstW, int dstH, int width, int height);

void func_0202845c(PanelPageState *state, int page) {
    NNSG2dScreenData *screenData = state->screenData;
    void *srcData;
    u8 *rec;

    if (*(s32 *)((u8 *)gPanelState + 0xbc) == 0 && page != 2) {
        return;
    }

    srcData = (page == 2) ? state->srcDataPage2 : state->srcDataDefault;
    rec = (u8 *)state + page * 0x18;

    NNS_G2dBGLoadScreenRect((u8 *)screenData + 0xc, srcData,
        *(s32 *)(rec + 0x10), *(s32 *)(rec + 0x14),
        *(s32 *)(rec + 0x18), *(s32 *)(rec + 0x1c),
        screenData->screenWidth, screenData->screenHeight,
        *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
}
