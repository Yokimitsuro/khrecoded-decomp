#include "nitro/types.h"

extern unsigned int random_next_scaled(unsigned int upperBound);

void InitPanelSwayA(int *params)
{
    params[0] = random_next_scaled(0x6488);
    params[1] = 0x4cd;
    params[2] = 0x666;
    params[3] = (random_next_scaled(2) ? 1 : -1) * 0x14000;
    params[4] = 0x14000;
}
