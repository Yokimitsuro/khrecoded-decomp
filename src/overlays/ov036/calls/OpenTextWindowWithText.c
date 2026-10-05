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

extern void QueueTypedMessageWindow(TextWindowRequest *request);

BOOL OpenTextWindowWithText(s32 posX, s32 posY, const s32 *boxSize, s32 style, const u16 *text)
{
    TextWindowRequest request;

    request.posX = posX;
    request.posY = posY;
    request.boxSize = boxSize;
    request.style = style;
    request.text = text;
    request.optionA = 0;
    request.optionB = 0;
    QueueTypedMessageWindow(&request);
    return TRUE;
}
