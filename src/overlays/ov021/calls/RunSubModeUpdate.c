#include "nitro/types.h"

typedef void *(*SubModeUpdateFunc)(void);

typedef struct SubModeState {
    s32 mode;
    void *block;
    SubModeUpdateFunc update;
    void *heap;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

BOOL RunSubModeUpdate(void)
{
    SubModeUpdateFunc next = (SubModeUpdateFunc)data_ov021_020b56c0->update();
    if (next != NULL) {
        data_ov021_020b56c0->update = next;
    }
    return FALSE;
}
