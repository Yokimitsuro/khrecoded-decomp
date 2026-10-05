#include "nitro/types.h"

extern void *gPanelState;
extern void *func_02029f5c(void);
extern int abs(void *value);

BOOL func_0202858c(void) {
    void *value = func_02029f5c();
    *(void **)((u8 *)gPanelState + 0x9c) = value;
    if (abs(*(void **)((u8 *)gPanelState + 0x9c)) == 0) {
        return 1;
    }
    return 0;
}
