#include "nitro/types.h"

extern unsigned int random_next_scaled(unsigned int upperBound);

void InitPanelSwayB(int *params)
{
    params[0] = random_next_scaled(0x6488);
    params[1] = 0x1ec;
    params[2] = 0x333;
    params[3] = (random_next_scaled(2) ? 1 : -1) * 0xf000;
    params[4] = 0xa000;
}
