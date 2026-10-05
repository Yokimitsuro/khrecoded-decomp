#include "nitro/types.h"

extern void RegisterChannelEntry(u32 arg0, u32 arg1, int arg2, int channel);

void InvokeForChannelOrBoth(u32 arg0, u32 arg1, int arg2, int channel)
{
    if (channel < 0) {
        int i;

        for (i = 0; i < 2; i++) {
            RegisterChannelEntry(arg0, arg1, arg2, i);
        }
        return;
    }
    RegisterChannelEntry(arg0, arg1, arg2, channel);
}
