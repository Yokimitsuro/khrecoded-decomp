#include "nitro/types.h"

extern int CreateObjectSlot(void *manager, int animation, int resource, int x, int y, int mode,
                                     int priority, int palette, int enabled);

int CreateDefaultObjectSlot(void *manager, int animation, int resource, int x, int y) {
    return CreateObjectSlot(manager, animation, resource, x, y, 0, 0, -1, 0);
}
