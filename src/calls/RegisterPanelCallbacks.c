#include "nitro/types.h"

typedef int (*PanelCallback)(void *arg);

extern void setDualArrayEntry(int slot, PanelCallback callback, void *arg);
extern int func_020285b4(void *arg);
extern int func_02028690(void *arg);
extern int func_02028760(void *arg);

void RegisterPanelCallbacks(void)
{
    setDualArrayEntry(0, func_020285b4, NULL);
    setDualArrayEntry(1, func_02028690, NULL);
    setDualArrayEntry(2, func_02028760, NULL);
}
