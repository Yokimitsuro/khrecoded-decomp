#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int (*callback)(int);
} CallbackHolder_0205fe00;

extern CallbackHolder_0205fe00 data_0205fe00;

int InvokeCallback(int value)
{
    return data_0205fe00.callback(value);
}
