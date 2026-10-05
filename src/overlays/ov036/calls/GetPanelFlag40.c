#include "nitro/types.h"

typedef struct PanelState {
    u8 unknown_00[0x24];
    u16 flags;
} PanelState;

typedef struct SceneWork {
    u8 unknown_0000[0x1098];
    PanelState *panel;
} SceneWork;

typedef struct SceneGlobals {
    void *unknown_00;
    SceneWork *work;
} SceneGlobals;

extern SceneGlobals data_ov036_020c3940;

u16 GetPanelFlag40(void) {
    return data_ov036_020c3940.work->panel->flags & 0x40;
}
