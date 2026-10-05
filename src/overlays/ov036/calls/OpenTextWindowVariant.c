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

extern void func_ov036_020c28dc(TextWindowRequest *request);

BOOL OpenTextWindowVariant(const s32 *boxSize, const u16 *text, s32 optionA, s32 optionB)
{
    TextWindowRequest request;

    request.posX = 1;
    request.posY = 0;
    request.boxSize = boxSize;
    request.style = 0;
    request.text = text;
    request.optionA = optionA;
    request.optionB = optionB;
    func_ov036_020c28dc(&request);
    return TRUE;
}
