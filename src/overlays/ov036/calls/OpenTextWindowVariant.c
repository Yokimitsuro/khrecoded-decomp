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

extern void QueueMessageWindowKind1(TextWindowRequest *request);

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
    QueueMessageWindowKind1(&request);
    return TRUE;
}
