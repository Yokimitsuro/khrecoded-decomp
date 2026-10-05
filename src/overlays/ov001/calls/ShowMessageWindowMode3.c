#include "nitro/types.h"

extern void func_ov001_0207a504(int mode, int x, int y, int width, int textId, int choiceId, int arg, int flags);

void ShowMessageWindowMode3(int arg)
{
    func_ov001_0207a504(3, 0, 0, 0, -1, -1, arg, 0);
}
