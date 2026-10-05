#include "nitro/types.h"

typedef struct {
    u8 pad[0x1110c];
    int mode;
    int timer;
    int step;
} PanelWork;

void SetPanelMode_020c1210(int mode, PanelWork *work) {
    work->mode = mode;
    work->timer = 0;
    work->step = 0;
}
