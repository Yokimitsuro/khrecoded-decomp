#include "nitro/types.h"

extern void OpenMessageWindow_0207a504(int mode, int x, int y, int width, int textId, int choiceId, int arg, int flags);

void ShowMessageWindowMode1(int x, int y, int arg, int flags)
{
    OpenMessageWindow_0207a504(1, x, y, 0, -1, -1, arg, flags);
}
