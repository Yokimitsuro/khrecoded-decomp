#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[0x4];
    int cursorIndex;
} Ov086Menu;

extern s64 _s32_div_f(int numerator, int denominator);
extern void func_ov086_020c082c(Ov086Menu *menu);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void StepCursorBackward(Ov086Menu *menu)
{
    int columnCount;

    switch (menu->pageIndex) {
    case 3:
        columnCount = 4;
        break;
    case 6:
        columnCount = 3;
        break;
    default:
        columnCount = 2;
        break;
    }
    menu->cursorIndex = (int)(_s32_div_f(menu->cursorIndex + columnCount - 1, columnCount) >> 32);
    func_ov086_020c082c(menu);
    PlaySoundEffect(0, 2);
}
