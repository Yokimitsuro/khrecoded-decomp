#include "nitro/types.h"

typedef struct TextWindowRequest {
    s32 posX;
    s32 posY;
    const s32 *boxSize;
    s32 style;
    const u16 *text;
    s32 optionA;
    s32 optionB;
    s32 unused;
} TextWindowRequest;

extern void func_ov036_020c28b0(TextWindowRequest *request);

BOOL OpenTextWindow(s32 posX, s32 posY, const s32 *boxSize, s32 style)
{
    TextWindowRequest request;

    request.posX = posX;
    request.posY = posY;
    request.boxSize = boxSize;
    request.style = style;
    request.text = NULL;
    request.optionA = 0;
    request.optionB = 0;
    func_ov036_020c28b0(&request);
    return TRUE;
}
