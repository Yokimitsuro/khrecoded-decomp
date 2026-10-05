#include "nitro/types.h"

typedef struct SceneWork {
    u8 unknown_0000[0x10e0];
    int cursorX;
    int cursorY;
} SceneWork;

typedef struct SceneGlobals {
    void *unknown_00;
    SceneWork *work;
} SceneGlobals;

extern SceneGlobals data_ov036_020c3940;

void SetSceneCursor(int x, int y) {
    data_ov036_020c3940.work->cursorX = x;
    data_ov036_020c3940.work->cursorY = y;
}
