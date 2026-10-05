#include "nitro/types.h"

extern u8 data_ov001_0209ea20[];
extern void *data_ov001_0209ea1c;
extern void *func_0202a45c(void *descriptor, void *userData);

void CreateSubScene9Task(void)
{
    data_ov001_0209ea1c = func_0202a45c(data_ov001_0209ea20, NULL);
}
