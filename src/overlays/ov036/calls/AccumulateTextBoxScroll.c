#include "nitro/types.h"

typedef struct TextBoxSize {
    s32 width;
    s32 height;
} TextBoxSize;

extern void MeasureScriptTextBox(TextBoxSize *outSize, void *vm, void *operand);
extern void MeasureScriptOperandText(TextBoxSize *outSize, void *vm, void *operand);
extern int ComputePageScrollOffset(int from, int to, BOOL forward);

void AccumulateTextBoxScroll(void *vm, void *operand, int kind, int direction, s32 *scroll)
{
    BOOL downward = FALSE;
    BOOL forward = FALSE;
    TextBoxSize current;
    TextBoxSize target;
    int deltaY;

    if (kind == 0xe) {
        return;
    }
    if (direction <= 3) {
        downward = TRUE;
        forward = TRUE;
    } else if (direction <= 7) {
        downward = TRUE;
    } else if (direction <= 0xb) {
        forward = TRUE;
    }
    MeasureScriptTextBox(&current, vm, operand);
    MeasureScriptOperandText(&target, vm, operand);
    deltaY = target.height - current.height;
    if (target.width - current.width != 0) {
        scroll[0] += ComputePageScrollOffset(current.width, target.width, forward);
    }
    if (kind == 0xf) {
        deltaY -= deltaY % 2;
    }
    if (deltaY != 0) {
        scroll[1] += downward ? deltaY * 8 / 2 : -(deltaY * 8 / 2);
    }
}
