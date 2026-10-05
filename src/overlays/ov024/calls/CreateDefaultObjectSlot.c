#include "nitro/types.h"

extern int func_ov024_020b67b4(void *manager, int animation, int resource, int x, int y, int mode,
                                     int priority, int palette, int enabled);

int CreateDefaultObjectSlot(void *manager, int animation, int resource, int x, int y) {
    return func_ov024_020b67b4(manager, animation, resource, x, y, 0, 0, -1, 0);
}
