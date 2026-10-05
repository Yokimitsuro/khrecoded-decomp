#include "nitro/types.h"

extern void *func_0202a45c(void *descriptor, void *userData);

extern u8 data_ov001_0209eb0c[];
extern void *data_ov001_0209eb08;

void CreateOverlayTask(u32 firstArg, ...)
{
    data_ov001_0209eb08 = func_0202a45c(data_ov001_0209eb0c, &firstArg);
}
