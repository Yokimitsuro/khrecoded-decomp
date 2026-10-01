#include "src/overlays/ov039/RuntimeState.h"

void RuntimeState_SetMode(int mode) {
    RUNTIME_STATE_TAIL->mode = mode;
}
