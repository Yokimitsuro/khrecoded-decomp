#include "nitro/types.h"

typedef int (*Callback)(void *arg);

extern Callback data_0205fdd4[];
extern void *data_0205fdc8[];

int InvokeCallbackSlot(int index)
{
    Callback callback = data_0205fdd4[index];

    if (callback == 0) {
        return 0;
    }
    return callback(data_0205fdc8[index]);
}
