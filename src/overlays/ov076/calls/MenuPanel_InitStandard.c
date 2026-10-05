#include "nitro/types.h"

extern void MenuPanel_Setup(void *panel, int owner, int x, int y, u16 width, u16 height, int priority, int arg7, int arg8);

void MenuPanel_InitStandard(void *panel, int owner, int x, int y, u16 width, u16 height, int arg7)
{
    MenuPanel_Setup(panel, owner, x, y, width, height, 0x96, arg7, 0x412);
}
