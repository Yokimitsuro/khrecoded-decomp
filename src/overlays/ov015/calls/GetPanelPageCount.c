#include "nitro/types.h"

extern u32 DispatchContextCommand(u32 command, u32 value, u32 extra, void *buffer);

int GetPanelPageCount(void)
{
    int count = DispatchContextCommand(1, 0, 0, NULL);

    return count + (count + (count + 1) / 10 + 1) / 10;
}
