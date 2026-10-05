#include "nitro/types.h"

typedef struct BoxSize {
    s32 width;
    s32 height;
} BoxSize;

typedef struct TextWindowRequest {
    s32 posX;
    s32 posY;
    const BoxSize *boxSize;
    s32 style;
    const u16 *text;
    s32 optionA;
    s32 optionB;
    s32 unused;
} TextWindowRequest;

extern const BoxSize data_ov036_020c36c0;
extern void func_ov036_020c28f8(TextWindowRequest *request);

BOOL OpenMessageTextWindow(const u16 *text)
{
    BoxSize box = data_ov036_020c36c0;
    TextWindowRequest request;

    request.posX = 1;
    request.posY = 0;
    request.boxSize = &box;
    request.style = 0;
    request.text = text;
    request.optionA = 0;
    request.optionB = 0;
    func_ov036_020c28f8(&request);
    return TRUE;
}
