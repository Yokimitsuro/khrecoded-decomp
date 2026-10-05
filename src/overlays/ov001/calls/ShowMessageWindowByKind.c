#include "nitro/types.h"

extern void func_ov001_0207a504(int mode, int x, int y, int width, int textId, int choiceId, int arg, int flags);

void ShowMessageWindowByKind(int arg, int kind)
{
    int mode;

    switch (kind) {
    case 1:
        mode = 5;
        break;
    case 2:
        mode = 6;
        break;
    case 3:
        mode = 10;
        break;
    case 4:
        mode = 7;
        break;
    default:
        mode = 4;
        break;
    }
    func_ov001_0207a504(mode, 0, 0, 0, -1, -1, arg, 0);
}
