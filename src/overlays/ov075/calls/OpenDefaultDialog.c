#include "nitro/types.h"

extern void InitMessageWindow(void *dialog, void *owner, s16 x, u16 y, u16 width, u16 height, int duration,
                                void *text, int flags);

void OpenDefaultDialog(void *dialog, void *owner, s16 x, u16 y, u16 width, u16 height, void *text)
{
    InitMessageWindow(dialog, owner, x, y, width, height, 0x96, text, 0x412);
}